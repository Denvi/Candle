#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include "frmmain.h"
#include "ui_frmmain.h"

frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    m_frmSettings.layout()->setSizeConstraint(QLayout::SetFixedSize);

    m_settingsFileName = qApp->applicationDirPath() + "/settings.ini";
    loadSettings();

    m_codeDrawer.setViewParser(&m_viewParser);
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 10));
    ui->glwVisualizator->addDrawable(&m_codeDrawer);
    ui->glwVisualizator->addDrawable(&m_toolDrawer);
    ui->glwVisualizator->fitDrawables();
    ui->cmdFit->setParent(ui->glwVisualizator);

    connect(&m_tableModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(on_tblProgram_cellChanged(QModelIndex,QModelIndex)));

    ui->tblProgram->setModel(&m_tableModel);
    ui->tblProgram->setColumnWidth(0, 400);
    ui->tblProgram->setColumnWidth(1, 150);
    ui->tblProgram->horizontalHeader()->setStretchLastSection(true);

    m_programLoading = false;
    clearTable();

    ui->cmdXMinus->setBackColor(QColor(153, 180, 209));
    ui->cmdXPlus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYMinus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYPlus->setBackColor(ui->cmdXMinus->backColor());

    ui->cmdReset->setBackColor(QColor(255, 228, 181));

    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort.setStopBits(QSerialPort::OneStop);

    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(onSerialPortReadyRead()));
    connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onSerialPortError(QSerialPort::SerialPortError)));

    connect(&m_timerConnection, SIGNAL(timeout()), this, SLOT(onTimerConnection()));
    m_timerConnection.start(1000);
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
}

void frmMain::saveSettings()
{
    QSettings set(m_settingsFileName, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    set.setValue("port", m_frmSettings.port());
    set.setValue("baud", m_frmSettings.baud());
}

void frmMain::onSerialPortReadyRead()
{
    while (m_serialPort.canReadLine()) {
        QString data = m_serialPort.readLine();

        ui->txtConsole->appendPlainText(data.left(data.length() - 2));
        qDebug() << data;
    }
}

void frmMain::onSerialPortError(QSerialPort::SerialPortError error)
{
    static QSerialPort::SerialPortError previousError;

    if (error != QSerialPort::NoError && error != previousError) {
        ui->txtConsole->appendPlainText("Serial port error " + QString::number(error) + ": " + m_serialPort.errorString());
        if (m_serialPort.isOpen()) m_serialPort.close();
        previousError = error;
    }
//    if (error == QSerialPort::ResourceError) m_serialPort.close();
}

void frmMain::onTimerConnection()
{
    if (!m_serialPort.isOpen()) {
        ui->txtStatus->setText("Не подключен");
        m_serialPort.setPortName(m_frmSettings.port());
        if (m_serialPort.open(QIODevice::ReadWrite)) {
            if (m_serialPort.setBaudRate(m_frmSettings.baud())) {
                ui->txtStatus->setText("Подключен");
            }
        }
    }
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

        if (m_frmSettings.port() != "") {
            if (m_serialPort.isOpen()) m_serialPort.close();
            m_serialPort.setPortName(m_frmSettings.port());
            qDebug() << "Settings baud rate:" << m_serialPort.setBaudRate(m_frmSettings.baud());
            qDebug() << "Try to open port:" << m_serialPort.open(QIODevice::ReadWrite);
//            qDebug() << "Test connection:" << m_serialPort.write("G0X10\r\n");
        }
    }
}

void frmMain::on_cmdCommandSend_clicked()
{
    m_serialPort.write(QString(ui->txtCommand->text() + "\r").toLocal8Bit());
    ui->txtCommand->clear();
}

void frmMain::on_txtCommand_returnPressed()
{
    this->on_cmdCommandSend_clicked();
}
