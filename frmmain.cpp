#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include "frmmain.h"
#include "ui_frmmain.h"

frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    ui->txtJogStep->setLocale(QLocale::C);
    m_frmSettings.layout()->setSizeConstraint(QLayout::SetFixedSize);

    m_settingsFileName = qApp->applicationDirPath() + "/settings.ini";
    loadSettings();

    m_codeDrawer.setViewParser(&m_viewParser);
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 10));
    m_toolDrawer.setToolDiameter(m_frmSettings.toolDiameter());
    m_toolDrawer.setToolLength(m_frmSettings.toolLength());

    ui->glwVisualizator->addDrawable(&m_codeDrawer);
    ui->glwVisualizator->addDrawable(&m_toolDrawer);
    ui->glwVisualizator->fitDrawables();
    ui->glwVisualizator->setAntialiasing(m_frmSettings.antialiasing());
    ui->cmdFit->setParent(ui->glwVisualizator);

    connect(&m_tableModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(on_tblProgram_cellChanged(QModelIndex,QModelIndex)));

    ui->tblProgram->setModel(&m_tableModel);

    ui->tblProgram->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tblProgram->setColumnWidth(1, 150);
    ui->tblProgram->setColumnWidth(2, 150);

    m_programLoading = false;
    clearTable();

    ui->cmdXMinus->setBackColor(QColor(153, 180, 209));
    ui->cmdXPlus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYMinus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYPlus->setBackColor(ui->cmdXMinus->backColor());

//    ui->cmdReset->setBackColor(QColor(255, 228, 181));

    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort.setStopBits(QSerialPort::OneStop);

    if (m_frmSettings.port() != "") {
        m_serialPort.setPortName(m_frmSettings.port());
        m_serialPort.setBaudRate(m_frmSettings.baud());
    }

    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(onSerialPortReadyRead()));
    connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onSerialPortError(QSerialPort::SerialPortError)));

    connect(&m_timerConnection, SIGNAL(timeout()), this, SLOT(onTimerConnection()));
    connect(&m_timerStateQuery, SIGNAL(timeout()), this, SLOT(onTimerStateQuery()));

    foreach (StyledToolButton* button, ui->grpJog->findChildren<StyledToolButton*>(QRegExp("cmdJogStep\\d")))
    {
        connect(button, SIGNAL(clicked(bool)), this, SLOT(onCmdJogStepClicked()));
        button->setChecked(button->text().toDouble() == ui->txtJogStep->value());
    }

    updateControlsState();

    m_lineTransferState = processing;
    m_timerConnection.start(1000);
    m_timerStateQuery.start(250);
}

frmMain::~frmMain()
{
    if (m_serialPort.isOpen()) m_serialPort.close();
    saveSettings();

    delete ui;
}

void frmMain::loadSettings()
{
    QSettings set(m_settingsFileName, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    m_frmSettings.setPort(set.value("port").toString());
    m_frmSettings.setBaud(set.value("baud").toInt());
    m_frmSettings.setToolDiameter(set.value("toolDiameter", 3).toDouble());
    m_frmSettings.setToolLength(set.value("toolLength", 15).toDouble());
    m_frmSettings.setAntialiasing(set.value("antialiasing", true).toBool());
    ui->txtJogStep->setValue(set.value("jogStep", 1).toDouble());
}

void frmMain::saveSettings()
{
    QSettings set(m_settingsFileName, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    set.setValue("port", m_frmSettings.port());
    set.setValue("baud", m_frmSettings.baud());
    set.setValue("toolDiameter", m_frmSettings.toolDiameter());
    set.setValue("toolLength", m_frmSettings.toolLength());
    set.setValue("antialiasing", m_frmSettings.antialiasing());
    set.setValue("jogStep", ui->txtJogStep->value());
}

void frmMain::updateControlsState() {
    bool portOpened = m_serialPort.isOpen();

    ui->grpState->setEnabled(portOpened);
    ui->grpControl->setEnabled(portOpened);
    ui->grpSpindle->setEnabled(portOpened);
    ui->grpJog->setEnabled(portOpened);
    ui->grpConsole->setEnabled(portOpened);

    if (!portOpened) ui->txtStatus->setText("Не подключен");
}

void frmMain::openPort()
{
    if (m_serialPort.open(QIODevice::ReadWrite)) {
        ui->txtStatus->setText("Подключен");
        updateControlsState();
        grblReset();
    }
}

void frmMain::sendCommand(QString command)
{
    if (m_lineTransferState == ready) {
        m_lineTransferState = processing;
        ui->txtConsole->appendPlainText(command);
        m_serialPort.write((command + "\r").toLatin1());
    } else {
        ui->txtConsole->appendPlainText("Устройство не готово");
    }
}

void frmMain::grblReset()
{
    ui->txtConsole->appendPlainText("[CTRL+X]");
    m_serialPort.write(QByteArray(1, (char)24));
}

void frmMain::onSerialPortReadyRead()
{
    while (m_serialPort.canReadLine()) {
        QString data = m_serialPort.readLine().trimmed();

        if (data.contains("Grbl")) {
            m_lineTransferState = ready;
        }

        if (data.toUpper() == "OK") {
            m_lineTransferState = ready;
        }

        if (data[0] == '<') {
            QRegExp rx("<([^,]*),MPos:([^,]*),([^,]*),([^,]*),WPos:([^,]*),([^,]*),([^,]*)>");

            if (rx.indexIn(data) != -1) {

                int i = m_status.indexOf(rx.cap(1));

                ui->txtStatus->setText(m_statusCaptions[i]);
                ui->txtStatus->setStyleSheet(QString("background-color: %1; color: %2;")
                                             .arg(m_statusBackColors[i]).arg(m_statusForeColors[i]));

                ui->txtWPosX->setText(rx.cap(5));
                ui->txtWPosY->setText(rx.cap(6));
                ui->txtWPosZ->setText(rx.cap(7));

                ui->txtMPosX->setText(rx.cap(2));
                ui->txtMPosY->setText(rx.cap(3));
                ui->txtMPosZ->setText(rx.cap(4));

                if (i == 0) {
                    if (m_settingZeroXY) {
                        m_settingZeroXY = false;
                        m_storedX = ui->txtMPosX->text().toDouble();
                        m_storedY = ui->txtMPosY->text().toDouble();
                    } else if (m_homing) {
                        m_homing = false;
                        m_storedZ = ui->txtMPosZ->text().toDouble();
                    }
                }

                m_toolDrawer.setToolPosition(QVector3D(ui->txtWPosX->text().toDouble(),
                                                       ui->txtWPosY->text().toDouble(),
                                                       ui->txtWPosZ->text().toDouble()));
                ui->glwVisualizator->update();
            }
        } else {
            ui->txtConsole->appendPlainText(data);
        }
    }
}

void frmMain::onSerialPortError(QSerialPort::SerialPortError error)
{
    static QSerialPort::SerialPortError previousError;

    if (error != QSerialPort::NoError && error != previousError) {
        ui->txtConsole->appendPlainText("Serial port error " + QString::number(error) + ": " + m_serialPort.errorString());
        if (m_serialPort.isOpen()) {
            m_serialPort.close();
            updateControlsState();
        }
        previousError = error;
    }
//    if (error == QSerialPort::ResourceError) m_serialPort.close();
}

void frmMain::onTimerConnection()
{    
    if (!m_serialPort.isOpen()) {
        openPort();
    }
}

void frmMain::onTimerStateQuery()
{
    if (m_serialPort.isOpen() && m_lineTransferState == ready) {
        m_serialPort.write(QByteArray(1, '?'));
    }
}

void frmMain::onCmdJogStepClicked()
{
    ui->txtJogStep->setValue(static_cast<QPushButton*>(sender())->text().toDouble());

    foreach (StyledToolButton* button, ui->grpJog->findChildren<StyledToolButton*>(QRegExp("cmdJogStep\\d")))
    {
        button->setChecked(false);
    }
    static_cast<QPushButton*>(sender())->setChecked(true);
}

void frmMain::showEvent(QShowEvent *se)
{
    QList<int> sizes;
    sizes.append(ui->grpProgram->height() - 100);
    sizes.append(100);
    ui->splitter->setSizes(sizes);
    ui->cmdFit->move(ui->glwVisualizator->width() - ui->cmdFit->width() - 10, 10);
}

void frmMain::resizeEvent(QResizeEvent *re)
{
    ui->cmdFit->move(ui->glwVisualizator->width() - ui->cmdFit->width() - 10, 10);
}

void frmMain::on_actFileExit_triggered()
{
    close();
}

void frmMain::on_cmdFileOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть", "", "Файлы G-Code (*.nc;*.ncc;*.tap)");

    if (fileName != "") processFile(fileName);
}

void frmMain::processFile(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) return;
    QTextStream textStream(&file);  
    QList<QString> commands;

    clearTable();
    m_programLoading = true;
    ui->tblProgram->setModel(NULL);

    while (!textStream.atEnd())
    {
        commands.append(textStream.readLine());

        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 1, 0), commands.last());
        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 2, 1), "В очереди");
    }

    m_programLoading = false;

    ui->tblProgram->setModel(&m_tableModel);
    ui->tblProgram->setColumnWidth(0, 400);
    ui->tblProgram->setColumnWidth(1, 150);
    ui->tblProgram->horizontalHeader()->setStretchLastSection(true);

    m_viewParser.reset();
    m_viewParser.toObjRedux(commands, 1);

    ui->glwVisualizator->fitDrawables();
}

void frmMain::clearTable()
{
    m_tableModel.clear();
    m_tableModel.insertRow(0);
}

void frmMain::on_cmdFit_clicked()
{
    ui->glwVisualizator->fitDrawables();
}

void frmMain::on_cmdFileSend_clicked()
{
}

void frmMain::on_tblProgram_cellChanged(QModelIndex i1, QModelIndex i2)
{
    if (i1.column() != 0) return;
    if (i1.row() == (m_tableModel.rowCount() - 1) && m_tableModel.data(m_tableModel.index(i1.row(), 0)).toString() != "") {
        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 1, 1), "В очереди");
        m_tableModel.insertRow(m_tableModel.rowCount());
        if (!m_programLoading) ui->tblProgram->setCurrentIndex(m_tableModel.index(i1.row() + 1, 0));
    } else if (i1.row() != (m_tableModel.rowCount() - 1) && m_tableModel.data(m_tableModel.index(i1.row(), 0)).toString() == "") {
        ui->tblProgram->setCurrentIndex(m_tableModel.index(i1.row() + 1, 0));
        m_tableModel.removeRow(i1.row());
    }

    if (!m_programLoading) {
        QList<QString> commands;

        for (int i = 0; i < m_tableModel.rowCount(); i++) {
            commands.append(m_tableModel.data(m_tableModel.index(i, 0)).toString());
        }

        m_viewParser.reset();
        m_viewParser.toObjRedux(commands, 1);
        //ui->glwVisualizator->fitDrawables();
        ui->glwVisualizator->update();
    }
}

void frmMain::on_cmdFileNew_clicked()
{
    clearTable();
    m_viewParser.reset();
    ui->glwVisualizator->fitDrawables();
}

void frmMain::on_actServiceSettings_triggered()
{
    if (m_frmSettings.exec()) {
        qDebug() << "Applying settings";
        qDebug() << "Port:" << m_frmSettings.port() << "Baud:" << m_frmSettings.baud();

        if (m_frmSettings.port() != "" && (m_frmSettings.port() != m_serialPort.portName() ||
                                           m_frmSettings.baud() != m_serialPort.baudRate())) {
            if (m_serialPort.isOpen()) m_serialPort.close();
            m_serialPort.setPortName(m_frmSettings.port());
            m_serialPort.setBaudRate(m_frmSettings.baud());
            openPort();
        }

        m_toolDrawer.setToolDiameter(m_frmSettings.toolDiameter());
        m_toolDrawer.setToolLength(m_frmSettings.toolLength());
        ui->glwVisualizator->setAntialiasing(m_frmSettings.antialiasing());
    }
}

void frmMain::on_cmdCommandSend_clicked()
{
    sendCommand(ui->txtCommand->text());
    ui->txtCommand->clear();
}

void frmMain::on_txtCommand_returnPressed()
{
    this->on_cmdCommandSend_clicked();
}

void frmMain::on_actFileOpen_triggered()
{
    on_cmdFileOpen_clicked();
}

void frmMain::on_cmdHome_clicked()
{
    m_homing = true;
    sendCommand("$H");
}

void frmMain::on_cmdTouch_clicked()
{
    m_homing = true;
    sendCommand("$T");
}

void frmMain::on_cmdZeroXY_clicked()
{
    m_settingZeroXY = true;
    sendCommand("G92X0Y0");
}

void frmMain::on_cmdZeroZ_clicked()
{
    sendCommand("G92Z0");
}

void frmMain::on_cmdReturnXY_clicked()
{
    sendCommand(QString("G92.1 G90 G0X%1Y%2").arg(m_storedX).arg(m_storedY));
}

void frmMain::on_cmdReset_clicked()
{
    grblReset();
}

void frmMain::on_cmdUnlock_clicked()
{
    sendCommand("$X");
}

void frmMain::on_cmdTopZ_clicked()
{
    sendCommand(QString("G92.1 G90 G0Z%1").arg(m_storedZ));
}

void frmMain::on_cmdSpindle_clicked(bool checked)
{
    if (m_lineTransferState != ready) ui->cmdSpindle->setChecked(!checked); else
        sendCommand(checked ? QString("M3 S%1").arg(ui->txtSpindleSpeed->text()) : "M5");
}

void frmMain::on_txtSpindleSpeed_valueChanged(const QString &arg1)
{
}

void frmMain::on_txtSpindleSpeed_editingFinished()
{
    ui->sliSpindleSpeed->setValue(ui->txtSpindleSpeed->value());
    sendCommand("S" + ui->txtSpindleSpeed->text());
}

void frmMain::on_sliSpindleSpeed_valueChanged(int value)
{
    qDebug() << "value" << ui->sliSpindleSpeed->value();
    while (m_lineTransferState != ready) qApp->processEvents(QEventLoop::AllEvents, 500);
    if (m_lineTransferState == ready) sendCommand(QString("S%1").arg(ui->sliSpindleSpeed->value()));
}

void frmMain::on_cmdYPlus_clicked()
{
    if (ui->txtMPosY->text().toDouble() + ui->txtJogStep->value() <= 0)
        sendCommand("G91 G0 Y" + ui->txtJogStep->text());
}

void frmMain::on_cmdYMinus_clicked()
{
    sendCommand("G91 G0 Y-" + ui->txtJogStep->text());
}

void frmMain::on_cmdXPlus_clicked()
{
    sendCommand("G91 G0 X" + ui->txtJogStep->text());
}

void frmMain::on_cmdXMinus_clicked()
{
    if (ui->txtMPosX->text().toDouble() - ui->txtJogStep->value() >= 0)
    sendCommand("G91 G0 X-" + ui->txtJogStep->text());
}

void frmMain::on_cmdZPlus_clicked()
{
    sendCommand("G91 G0 Z" + ui->txtJogStep->text());
}

void frmMain::on_cmdZMinus_clicked()
{
    sendCommand("G91 G0 Z-" + ui->txtJogStep->text());
}
