#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QTextBlock>
#include <QTextCursor>
#include "frmmain.h"
#include "ui_frmmain.h"

frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain)
{
    m_status = {"Idle", "Alarm", "Run", "Home", "Hold", "Queue", "Check"};
    m_statusCaptions = {tr("Idle"), tr("Alarm"), tr("Run"), tr("Home"), tr("Hold"), tr("Queue"), tr("Check")};
    m_statusBackColors = {"palette(button)", "red", "lime", "lime", "yellow", "yellow", "palette(button)"};
    m_statusForeColors = {"palette(text)", "white", "black", "black", "black", "black", "palette(text)"};

    ui->setupUi(this);

    ui->txtJogStep->setLocale(QLocale::C);
    m_frmSettings.layout()->setSizeConstraint(QLayout::SetFixedSize);

    m_settingsFileName = qApp->applicationDirPath() + "/settings.ini";
    loadSettings();

    m_codeDrawer = new GcodeDrawer(this);
    m_codeDrawer->setViewParser(&m_viewParser);
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 10));
//    m_toolDrawer.setToolDiameter(m_frmSettings.toolDiameter());
//    m_toolDrawer.setToolLength(m_frmSettings.toolLength());

    ui->glwVisualizator->addDrawable(m_codeDrawer);
    ui->glwVisualizator->addDrawable(&m_toolDrawer);
    ui->glwVisualizator->fitDrawables();
//    ui->glwVisualizator->setAntialiasing(m_frmSettings.antialiasing());
    ui->cmdFit->setParent(ui->glwVisualizator);
    ui->cmdIsometric->setParent(ui->glwVisualizator);

    connect(ui->glwVisualizator, SIGNAL(rotationChanged()), this, SLOT(onVisualizatorRotationChanged()));
    connect(&m_tableModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(on_tblProgram_cellChanged(QModelIndex,QModelIndex)));

    ui->tblProgram->setModel(&m_tableModel);

//    ui->tblProgram->setColumnWidth(0, 40);
    ui->tblProgram->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
//    ui->tblProgram->setColumnWidth(2, 150);
//    ui->tblProgram->setColumnWidth(3, 150);
    ui->tblProgram->hideColumn(4);
//    ui->tblProgram->showColumn(4);

    m_programLoading = false;
    clearTable();

    ui->cmdXMinus->setBackColor(QColor(153, 180, 209));
    ui->cmdXPlus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYMinus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYPlus->setBackColor(ui->cmdXMinus->backColor());

//    ui->splitter->setStretchFactor(0, 1);
//    ui->splitter->setStretchFactor(1, 0);

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
    applySettings();

    m_timerConnection.start(1000);
    m_timerStateQuery.start(33);
}

frmMain::~frmMain()
{
    if (m_serialPort.isOpen()) m_serialPort.close();
    saveSettings();

    delete ui;
}

double frmMain::toolZPosition()
{
    return m_toolDrawer.toolPosition().z();
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
    m_programSpeed = true;
    ui->sliSpindleSpeed->setValue(set.value("spindleSpeed", 0).toInt());
    m_programSpeed = false;
    m_frmSettings.setLineWidth(set.value("lineWidth", 1).toDouble());
    m_frmSettings.setArcPrecision(set.value("arcPrecision", 0).toDouble());
    m_frmSettings.setShowAllCommands(set.value("showAllCommands", 0).toBool());
    m_frmSettings.setSafeZ(set.value("safeZ", 0).toDouble());
    ui->chkAutoScroll->setChecked(set.value("autoScroll", false).toBool());
    ui->tblProgram->horizontalHeader()->restoreState(set.value("header", QByteArray()).toByteArray());

    QByteArray splitterState = set.value("splitter", QByteArray()).toByteArray();

    if (splitterState.length() == 0) {
        ui->splitter->setStretchFactor(0, 1);
        ui->splitter->setStretchFactor(1, 0);
    } else ui->splitter->restoreState(splitterState);
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
    set.setValue("spindleSpeed", ui->txtSpindleSpeed->text());
    set.setValue("lineWidth", m_frmSettings.lineWidth());
    set.setValue("arcPrecision", m_frmSettings.arcPrecision());
    set.setValue("showAllCommands", m_frmSettings.showAllCommands());
    set.setValue("safeZ", m_frmSettings.safeZ());
    set.setValue("autoScroll", ui->chkAutoScroll->isChecked());
    set.setValue("header", ui->tblProgram->horizontalHeader()->saveState());
    set.setValue("splitter", ui->splitter->saveState());
}

void frmMain::updateControlsState() {
    bool portOpened = m_serialPort.isOpen();

    ui->grpState->setEnabled(portOpened);
    ui->grpControl->setEnabled(portOpened);
    ui->grpSpindle->setEnabled(portOpened);
    ui->grpJog->setEnabled(portOpened && !m_transferringFile);
    ui->grpConsole->setEnabled(portOpened);   

    ui->chkTestMode->setEnabled(portOpened && !m_transferringFile);
    ui->cmdHome->setEnabled(!m_transferringFile);
    ui->cmdTouch->setEnabled(!m_transferringFile);
    ui->cmdZeroXY->setEnabled(!m_transferringFile);
    ui->cmdZeroZ->setEnabled(!m_transferringFile);
    ui->cmdReturnXY->setEnabled(!m_transferringFile);
    ui->cmdTopZ->setEnabled(!m_transferringFile);
    ui->cmdUnlock->setEnabled(!m_transferringFile);
    ui->cmdSpindle->setEnabled(!m_transferringFile);

    ui->actFileNew->setEnabled(!m_transferringFile);
    ui->actFileOpen->setEnabled(!m_transferringFile);
    ui->cmdFileOpen->setEnabled(!m_transferringFile);
    ui->cmdFileReset->setEnabled(!m_transferringFile);
    ui->cmdFileSend->setEnabled(portOpened && !m_transferringFile);
    ui->cmdFilePause->setEnabled(m_transferringFile);
    ui->actFileOpen->setEnabled(!m_transferringFile);

    ui->tblProgram->setEditTriggers(m_transferringFile ? QAbstractItemView::NoEditTriggers :
                                                         QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked
                                                         | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);

    if (!portOpened) ui->txtStatus->setText(tr("Not connected"));

    qApp->processEvents();
    this->update();
}

void frmMain::openPort()
{
    if (m_serialPort.open(QIODevice::ReadWrite)) {
        ui->txtStatus->setText(tr("Connected"));
        updateControlsState();
        grblReset();
    }
}

void frmMain::sendCommand(QString command, int tableIndex)
{
    // Commands queue
    if ((bufferLength() + command.length() + 1) > BUFFERLENGTH) {
        m_queue.append(command);
    }

    while ((bufferLength() + command.length() + 1) > BUFFERLENGTH) {
        qApp->processEvents();
    }

    if (m_queue.length() > 0) {
        command = m_queue.takeFirst();
    }

    CommandAttributes ca;

    if (!(command == "$G" && tableIndex == 0)
            && (!m_transferringFile || (m_transferringFile && m_showAllCommands) || tableIndex == -1)) {
        ca.consoleIndex = ui->txtConsole->blockCount();
        ui->txtConsole->appendPlainText(command);
    } else {
        ca.consoleIndex = -1;
    }

    // Hide parser state query command
//    if (command == "$G" && tableIndex == 0) ca.consoleIndex = -1;

    ca.command = command;
    ca.length = command.length() + 1;
    ca.tableIndex = tableIndex;

    m_commands.append(ca);

    // Processing
    QRegExp s("[Ss]0*(\\d+)");
    if (s.indexIn(command) != -1) {
        int speed = s.cap(1).toInt();
        if (ui->sliSpindleSpeed->value() != speed) {
            m_programSpeed = true;
            ui->sliSpindleSpeed->setValue(speed);
            m_programSpeed = false;
        }
    }

    m_serialPort.write((command + "\r").toLatin1());
}

void frmMain::grblReset()
{
    m_transferringFile = false;
    m_fileCommandIndex = 0;
    ui->cmdSpindle->setChecked(false);
    m_timerToolAnimation.stop();

    ui->txtConsole->appendPlainText("[CTRL+X]");
    m_serialPort.write(QByteArray(1, (char)24));

    updateControlsState();
}

int frmMain::bufferLength()
{
    int length = 0;

    foreach (CommandAttributes ca, m_commands) {
        length += ca.length;
    }

    return length;
}

void frmMain::onSerialPortReadyRead()
{
    while (m_serialPort.canReadLine()) {
        QString data = m_serialPort.readLine().trimmed();

        if (data.contains("Grbl")) {
            m_commands.clear();
//            m_lineTransferState = ready;
        }

        if (data.toUpper() == "OK") {
//            m_commands.takeFirst();
//            m_lineTransferState = ready;
        }

        // Parser state
        if (data[0] == '[') {
            if (data.contains("G90")) sendCommand("G90");
        }

        // Status
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

                // Store work origin
                if (i == 0) {
                    if (m_settingZeroXY) {
                        m_settingZeroXY = false;
                        m_storedX = ui->txtMPosX->text().toDouble();
                        m_storedY = ui->txtMPosY->text().toDouble();
                    } else if (m_settingZeroZ) {
                        m_settingZeroZ = false;
                        m_storedZ = ui->txtMPosZ->text().toDouble();
                    }
                }

                // Update controls
                ui->cmdReturnXY->setEnabled(i == 0);
                ui->cmdTopZ->setEnabled(i == 0);
                ui->chkTestMode->setChecked(i == 6);
                ui->cmdFilePause->setChecked(i == 4 || i == 5);

                // Update tool position
                m_toolDrawer.setToolPosition(QVector3D(ui->txtWPosX->text().toDouble(),
                                                       ui->txtWPosY->text().toDouble(),
                                                       ui->txtWPosZ->text().toDouble()));

                // Trajectory shadowing
                if (m_transferringFile) {
                    bool toolOnTrajectory = false;

                    QList<int> drawnLines;

                    for (int i = m_lastDrawnLineIndex; i < m_viewParser.getLineSegmentList().count()
                         && m_viewParser.getLineSegmentList()[i]->getLineNumber()
                         <= (m_tableModel.data(m_tableModel.index(m_fileProcessedCommandIndex, 4)).toInt() + 1); i++) {
                        if (m_viewParser.getLineSegmentList()[i]->contains(m_toolDrawer.toolPosition())) {
                            toolOnTrajectory = true;
                            m_lastDrawnLineIndex = i;
                            break;
                        }
                        drawnLines << i;
                    }

                    if (toolOnTrajectory) {
                        foreach (int i, drawnLines) {
                            m_viewParser.getLineSegmentList()[i]->setDrawn(true);
                        }
                    } else if (m_lastDrawnLineIndex < m_viewParser.getLineSegmentList().count()) {
                        qDebug() << m_viewParser.getLineSegmentList()[m_lastDrawnLineIndex]->getLineNumber()
                                 << m_tableModel.data(m_tableModel.index(m_fileProcessedCommandIndex, 4)).toInt();
                    }
                }

                // Update timer
                if (m_transferringFile) {
                    QTime time(0, 0, 0);
                    int elapsed = m_startTime.elapsed();
                    ui->glwVisualizator->setSpendTime(time.addMSecs(elapsed));
                }

                ui->glwVisualizator->update();

                // Test for job complete
                if (m_transferCompleted && i == 0 && m_fileCommandIndex == m_tableModel.rowCount() - 1) {
                    m_transferringFile = false;

                    for (int i = m_lastDrawnLineIndex; i < m_viewParser.getLineSegmentList().length(); i++) {
                        m_viewParser.getLineSegmentList()[i]->setDrawn(true);
                    }

                    updateControlsState();
                }
            }
        } else if (data.length() > 0) {

            // Processed commands
            if (m_commands.length() > 0) {

                // Find command in console
                CommandAttributes ca = m_commands.takeFirst();
                QTextBlock tb = ui->txtConsole->document()->findBlockByNumber(ca.consoleIndex);
                QTextCursor tc(tb);

                // Add answer to console
                if (ca.consoleIndex != -1) {
                    tc.beginEditBlock();
                    tc.movePosition(QTextCursor::EndOfBlock);
                    tc.insertText(" > " + data);
                    tc.endEditBlock();
                }

                // Update file table
                if (m_transferringFile) {

                    m_tableModel.setData(m_tableModel.index(ca.tableIndex, 2), tr("Processed"));
                    m_tableModel.setData(m_tableModel.index(ca.tableIndex, 3), data);

                    m_fileProcessedCommandIndex = ca.tableIndex;

                    if (ui->chkAutoScroll->isChecked() && ca.tableIndex != -1) {
                        ui->tblProgram->scrollTo(m_tableModel.index(ca.tableIndex + 1, 0));
                        ui->tblProgram->setCurrentIndex(m_tableModel.index(ca.tableIndex, 1));
                    }

                    if (m_fileCommandIndex < m_tableModel.rowCount()) {
                        sendNextFileCommands();
                    }
                }

                // Update transferring state
                if (m_fileCommandIndex == m_tableModel.rowCount() - 1) m_transferCompleted = true;

                // Process spindle control commands
                QRegExp m("[Mm]0*(\\d+)");
                if (m.indexIn(ca.command) != -1) {
                    if (m.cap(1).toInt() == 3) {
                        m_timerToolAnimation.start(33, this);
                        ui->cmdSpindle->setChecked(true);
                    }
                    else if (m.cap(1).toInt() == 5 || m.cap(1).toInt() == 2) {
                        m_timerToolAnimation.stop();
                        ui->cmdSpindle->setChecked(false);
                    }
                }

            } else {
                ui->txtConsole->appendPlainText(data);
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
        ui->txtConsole->appendPlainText(tr("Serial port error ") + QString::number(error) + ": " + m_serialPort.errorString());
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
    if (m_serialPort.isOpen()) {
        m_serialPort.write(QByteArray(1, '?'));
    }

//    ui->statusBar->showMessage(QString("Буфер: %1    Очередь: %2").arg(bufferLength()).arg(m_queue.length()));
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

void frmMain::onVisualizatorRotationChanged()
{
    ui->cmdIsometric->setChecked(false);
}

void frmMain::showEvent(QShowEvent *se)
{
    ui->cmdFit->move(ui->glwVisualizator->width() - ui->cmdFit->width() - 10, 10);
    ui->cmdIsometric->move(ui->cmdFit->geometry().left() - ui->cmdIsometric->width() - 10, 10);
}

void frmMain::resizeEvent(QResizeEvent *re)
{
    ui->cmdFit->move(ui->glwVisualizator->width() - ui->cmdFit->width() - 10, 10);
    ui->cmdIsometric->move(ui->cmdFit->geometry().left() - ui->cmdIsometric->width() - 10, 10);
}

void frmMain::timerEvent(QTimerEvent *te)
{
    if (te->timerId() == m_timerToolAnimation.timerId()) {
        m_toolDrawer.rotate(-20 * (double)ui->txtSpindleSpeed->value() / 100);
        ui->glwVisualizator->update();
    } else {
        QMainWindow::timerEvent(te);
    }
}

void frmMain::on_actFileExit_triggered()
{
    close();
}

void frmMain::on_cmdFileOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("G-Code files (*.nc;*.ncc;*.tap)"));

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

    QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();

    ui->tblProgram->setModel(NULL);

    GcodeParser gp;

    while (!textStream.atEnd())
    {
        QString command = textStream.readLine();

        gp.addCommand(command);

        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 1, 1), command);
        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 2, 2), tr("In queue"));
        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 2, 4), gp.getCommandNumber());
    }

    m_programLoading = false;

    ui->tblProgram->setModel(&m_tableModel);
    ui->tblProgram->horizontalHeader()->restoreState(headerState);

    m_viewParser.reset();
    updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_frmSettings.arcPrecision()));

    ui->glwVisualizator->fitDrawables();
}

QTime frmMain::updateProgramEstimatedTime(QList<LineSegment*> lines)
{
    double time = 0;
    foreach (LineSegment *ls, lines) {
        double length = (ls->getEnd() - ls->getStart()).length();

        if (!std::isnan(length) && !std::isnan(ls->getSpeed())) time +=  length / ls->getSpeed();

        if (std::isnan(length)) qDebug() << "length nan:" << ls->getStart() << ls->getEnd();
        if (std::isnan(ls->getSpeed())) qDebug() << "speed nan:" << ls->getSpeed();
    }

    time *= 60;

    QTime t;

    t.setHMS(0, 0, 0);
    t = t.addSecs(time);

    ui->glwVisualizator->setSpendTime(QTime(0, 0, 0));
    ui->glwVisualizator->setEstimatedTime(t);

    return t;
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
    if (m_tableModel.rowCount() == 1) return;

    on_cmdFileReset_clicked();

    m_startTime.start();

    m_transferCompleted = false;
    m_transferringFile = true;
    updateControlsState();
    sendNextFileCommands();
}

void frmMain::sendNextFileCommands() {

    if (m_queue.length() > 0) return;

    QString command = m_tableModel.data(m_tableModel.index(m_fileCommandIndex, 1)).toString();
    while ((bufferLength() + command.length() + 1) <= BUFFERLENGTH && m_fileCommandIndex < m_tableModel.rowCount() - 1) {
        m_tableModel.setData(m_tableModel.index(m_fileCommandIndex, 2), tr("Sended"));
        sendCommand(command, m_fileCommandIndex);
        m_fileCommandIndex++;
        command = m_tableModel.data(m_tableModel.index(m_fileCommandIndex, 1)).toString();
    }
}

void frmMain::on_tblProgram_cellChanged(QModelIndex i1, QModelIndex i2)
{
    if (i1.column() != 1) return;
    if (i1.row() == (m_tableModel.rowCount() - 1) && m_tableModel.data(m_tableModel.index(i1.row(), 1)).toString() != "") {
        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 1, 2), tr("In queue"));
        m_tableModel.insertRow(m_tableModel.rowCount());
        if (!m_programLoading) ui->tblProgram->setCurrentIndex(m_tableModel.index(i1.row() + 1, 1));
    } else if (i1.row() != (m_tableModel.rowCount() - 1) && m_tableModel.data(m_tableModel.index(i1.row(), 1)).toString() == "") {
        ui->tblProgram->setCurrentIndex(m_tableModel.index(i1.row() + 1, 1));
        m_tableModel.removeRow(i1.row());
    }

    if (!m_programLoading) {
//        QList<QString> commands;

        GcodeParser gp;

        for (int i = 0; i < m_tableModel.rowCount() - 1; i++) {
            gp.addCommand(m_tableModel.data(m_tableModel.index(i, 1)).toString());
            m_tableModel.setData(m_tableModel.index(i, 4), gp.getCommandNumber());
        }

        m_viewParser.reset();

        updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_frmSettings.arcPrecision()));
//        m_viewParser.toObjRedux(commands, m_frmSettings.arcPrecision());
        //ui->glwVisualizator->fitDrawables();
        ui->glwVisualizator->update();
    }
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

        updateControlsState();
        applySettings();
    }
}

void frmMain::applySettings() {
    m_toolDrawer.setToolDiameter(m_frmSettings.toolDiameter());
    m_toolDrawer.setToolLength(m_frmSettings.toolLength());
    m_toolDrawer.setLineWidth(m_frmSettings.lineWidth());
    m_codeDrawer->setLineWidth(m_frmSettings.lineWidth());
    ui->glwVisualizator->setLineWidth(m_frmSettings.lineWidth());
    m_showAllCommands = m_frmSettings.showAllCommands();
    m_safeZ = m_frmSettings.safeZ();
    ui->glwVisualizator->setAntialiasing(m_frmSettings.antialiasing());
    ui->glwVisualizator->update();
}

void frmMain::on_cmdCommandSend_clicked()
{
    sendCommand(ui->txtCommand->text(), -1);
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
    m_settingZeroZ = true;
    sendCommand("G92Z0");
}

void frmMain::on_cmdReturnXY_clicked()
{    
    sendCommand(QString("G21"));
    sendCommand(QString("G92.1"));
    sendCommand(QString("G90G0X%1Y%2").arg(m_storedX).arg(m_storedY));
    sendCommand(QString("G92X0Y0Z%1").arg(ui->txtMPosZ->text().toDouble() - m_storedZ));
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

    sendCommand(QString("G21"));
    sendCommand(QString("G90 G0Z%1").arg(m_safeZ - ui->txtMPosZ->text().toDouble()
                                         + ui->txtWPosZ->text().toDouble()));
}

void frmMain::on_cmdSpindle_clicked(bool checked)
{
    sendCommand(checked ? QString("M3 S%1").arg(ui->txtSpindleSpeed->text()) : "M5");
}

void frmMain::on_txtSpindleSpeed_valueChanged(const QString &arg1)
{
}

void frmMain::on_txtSpindleSpeed_editingFinished()
{
    ui->sliSpindleSpeed->setValue(ui->txtSpindleSpeed->value());
}

void frmMain::on_sliSpindleSpeed_valueChanged(int value)
{
    if (!m_programSpeed) {
        sendCommand(QString("S%1").arg(ui->sliSpindleSpeed->value()), -1);
    }
}

void frmMain::on_cmdYPlus_clicked()
{
    sendCommand("$G");
    sendCommand("G91 G0 Y" + ui->txtJogStep->text());
}

void frmMain::on_cmdYMinus_clicked()
{
    sendCommand("$G");
    sendCommand("G91 G0 Y-" + ui->txtJogStep->text());
}

void frmMain::on_cmdXPlus_clicked()
{
    sendCommand("$G");
    sendCommand("G91 G0 X" + ui->txtJogStep->text());
}

void frmMain::on_cmdXMinus_clicked()
{    
    sendCommand("$G");
    sendCommand("G91 G0 X-" + ui->txtJogStep->text());
}

void frmMain::on_cmdZPlus_clicked()
{
    sendCommand("$G");
    sendCommand("G91 G0 Z" + ui->txtJogStep->text());
}

void frmMain::on_cmdZMinus_clicked()
{
    sendCommand("$G");
    sendCommand("G91 G0 Z-" + ui->txtJogStep->text());
}

void frmMain::on_chkTestMode_clicked()
{
    sendCommand("$C");
}

void frmMain::on_cmdFilePause_clicked(bool checked)
{
    m_serialPort.write(checked ? "!" : "~");
//    sendCommand(checked ? "!" : "~");
}

void frmMain::on_cmdFileReset_clicked()
{
    m_fileCommandIndex = 0;
    m_fileProcessedCommandIndex = 0;
    m_lastDrawnLineIndex = 0;

    for (int i = m_lastDrawnLineIndex; i < m_viewParser.getLineSegmentList().length(); i++) {
        m_viewParser.getLineSegmentList()[i]->setDrawn(false);
    }   

    for (int i = 0; i < m_tableModel.rowCount() - 1; i++) {
        m_tableModel.setData(m_tableModel.index(i, 2), tr("In queue"));
        m_tableModel.setData(m_tableModel.index(i, 3), "");
    }

    ui->tblProgram->scrollTo(m_tableModel.index(0, 0));
    ui->tblProgram->clearSelection();

    ui->glwVisualizator->setSpendTime(QTime(0, 0, 0));
}

void frmMain::on_actFileNew_triggered()
{
    clearTable();
    m_viewParser.reset();
    ui->glwVisualizator->fitDrawables();
}

void frmMain::on_cmdIsometric_clicked(bool checked)
{
    if (checked) ui->glwVisualizator->setIsometricView(); else ui->glwVisualizator->setTopView();
}
