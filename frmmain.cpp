// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QTextBlock>
#include <QTextCursor>
#include <QMessageBox>
#include <QComboBox>
#include <QScrollBar>
#include "frmmain.h"
#include "ui_frmmain.h"

frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain)
{
    m_status << "Idle" << "Alarm" << "Run" << "Home" << "Hold" << "Queue" << "Check";
    m_statusCaptions << tr("Idle") << tr("Alarm") << tr("Run") << tr("Home") << tr("Hold") << tr("Queue") << tr("Check");
    m_statusBackColors << "palette(button)" << "red" << "lime" << "lime" << "yellow" << "yellow" << "palette(button)";
    m_statusForeColors << "palette(text)" << "white" << "black" << "black" << "black" << "black" << "palette(text)";

    ui->setupUi(this);

    ui->txtJogStep->setLocale(QLocale::C);

    ui->cmdXMinus->setBackColor(QColor(153, 180, 209));
    ui->cmdXPlus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYMinus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYPlus->setBackColor(ui->cmdXMinus->backColor());

    //    ui->cmdReset->setBackColor(QColor(255, 228, 181));

    ui->cmdFit->setParent(ui->glwVisualizator);
    ui->cmdIsometric->setParent(ui->glwVisualizator);
    ui->cmdTop->setParent(ui->glwVisualizator);
    ui->cmdFront->setParent(ui->glwVisualizator);
    ui->cmdLeft->setParent(ui->glwVisualizator);

    connect(ui->tblProgram->verticalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(onScroolBarAction(int)));

    m_frmSettings.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    m_settingsFileName = qApp->applicationDirPath() + "/settings.ini";
    loadSettings();

    foreach (StyledToolButton* button, ui->grpJog->findChildren<StyledToolButton*>(QRegExp("cmdJogStep\\d")))
    {
        connect(button, SIGNAL(clicked(bool)), this, SLOT(onCmdJogStepClicked()));
        button->setChecked(button->text().toDouble() == ui->txtJogStep->value());
    }

    m_codeDrawer = new GcodeDrawer(this);
    m_codeDrawer->setViewParser(&m_viewParser);
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 0));

    ui->glwVisualizator->addDrawable(m_codeDrawer);
    ui->glwVisualizator->addDrawable(&m_toolDrawer);
    ui->glwVisualizator->fitDrawables();

    connect(ui->glwVisualizator, SIGNAL(rotationChanged()), this, SLOT(onVisualizatorRotationChanged()));
    connect(&m_tableModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(on_tblProgram_cellChanged(QModelIndex,QModelIndex)));

    ui->tblProgram->setModel(&m_tableModel);

    ui->tblProgram->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tblProgram->hideColumn(4);
//    ui->tblProgram->showColumn(4);

    m_programLoading = false;
    clearTable();

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

    updateControlsState();
    applySettings();

    m_lastDrawnLineIndex = 0;
    m_fileProcessedCommandIndex = 0;

    m_timerConnection.start(1000);
    m_timerStateQuery.start();

    this->installEventFilter(this);
//    ui->txtConsole->installEventFilter(this);
//    ui->txtSpindleSpeed->installEventFilter(this);
//    ui->tblProgram->installEventFilter(this);
}

frmMain::~frmMain()
{    
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
    m_frmSettings.setZBuffer(set.value("zBuffer", false).toBool());
    ui->txtJogStep->setValue(set.value("jogStep", 1).toDouble());
    m_programSpeed = true;
    ui->sliSpindleSpeed->setValue(set.value("spindleSpeed", 0).toInt());
    m_programSpeed = false;
    m_frmSettings.setLineWidth(set.value("lineWidth", 1).toDouble());
    m_frmSettings.setArcPrecision(set.value("arcPrecision", 0).toDouble());
    m_frmSettings.setShowAllCommands(set.value("showAllCommands", 0).toBool());
    m_frmSettings.setSafeZ(set.value("safeZ", 0).toDouble());
    m_frmSettings.setSpindleSpeedMin(set.value("spindleSpeedMin", 0).toInt());
    m_frmSettings.setSpindleSpeedMax(set.value("spindleSpeedMax", 100).toInt());
    m_frmSettings.setRapidSpeed(set.value("rapidSpeed", 0).toInt());
    m_frmSettings.setAcceleration(set.value("acceleration", 10).toInt());
    m_frmSettings.setToolAngle(set.value("toolAngle", 0).toDouble());
    m_frmSettings.setToolType(set.value("toolType", 0).toInt());
    m_frmSettings.setFps(set.value("fps", 60).toInt());
    m_frmSettings.setQueryStateTime(set.value("queryStateTime", 250).toInt());
    ui->chkAutoScroll->setChecked(set.value("autoScroll", false).toBool());
    ui->tblProgram->horizontalHeader()->restoreState(set.value("header", QByteArray()).toByteArray());
    ui->sliSpindleSpeed->setValue(set.value("spindleSpeed", 100).toInt() / 100);
    ui->txtSpindleSpeed->setValue(set.value("spindleSpeed", 100).toInt());
    ui->chkFeedOverride->setChecked(set.value("feedOverride", false).toBool());
    ui->sliFeed->setValue(set.value("feed", 100).toInt());

    QByteArray splitterState = set.value("splitter", QByteArray()).toByteArray();

    if (splitterState.length() == 0) {
        ui->splitter->setStretchFactor(0, 1);
        ui->splitter->setStretchFactor(1, 0);
    } else ui->splitter->restoreState(splitterState);

    ui->grpSpindle->setChecked(set.value("spindlePanel", true).toBool());
    ui->grpFeed->setChecked(set.value("feedPanel", true).toBool());
    ui->grpJog->setChecked(set.value("jogPanel", true).toBool());

    this->restoreGeometry(set.value("formGeometry", QByteArray()).toByteArray());
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
    set.setValue("zBuffer", m_frmSettings.zBuffer());
    set.setValue("jogStep", ui->txtJogStep->value());
    set.setValue("spindleSpeed", ui->txtSpindleSpeed->text());
    set.setValue("lineWidth", m_frmSettings.lineWidth());
    set.setValue("arcPrecision", m_frmSettings.arcPrecision());
    set.setValue("showAllCommands", m_frmSettings.showAllCommands());
    set.setValue("safeZ", m_frmSettings.safeZ());
    set.setValue("spindleSpeedMin", m_frmSettings.spindleSpeedMin());
    set.setValue("spindleSpeedMax", m_frmSettings.spindleSpeedMax());
    set.setValue("rapidSpeed", m_frmSettings.rapidSpeed());
    set.setValue("acceleration", m_frmSettings.acceleration());
    set.setValue("toolAngle", m_frmSettings.toolAngle());
    set.setValue("toolType", m_frmSettings.toolType());
    set.setValue("fps", m_frmSettings.fps());
    set.setValue("queryStateTime", m_frmSettings.queryStateTime());
    set.setValue("autoScroll", ui->chkAutoScroll->isChecked());
    set.setValue("header", ui->tblProgram->horizontalHeader()->saveState());
    set.setValue("splitter", ui->splitter->saveState());
    set.setValue("formGeometry", this->saveGeometry());
    set.setValue("spindleSpeed", ui->txtSpindleSpeed->value());
    set.setValue("feedOverride", ui->chkFeedOverride->isChecked());
    set.setValue("feed", ui->txtFeed->value());
    set.setValue("spindlePanel", ui->grpSpindle->isChecked());
    set.setValue("feedPanel", ui->grpFeed->isChecked());
    set.setValue("jogPanel", ui->grpJog->isChecked());
}

void frmMain::updateControlsState() {
    bool portOpened = m_serialPort.isOpen();

    ui->grpState->setEnabled(portOpened);
    ui->grpControl->setEnabled(portOpened);
    ui->widgetSpindle->setEnabled(portOpened);
    ui->widgetJog->setEnabled(portOpened && !m_transferringFile);
//    ui->grpConsole->setEnabled(portOpened);
    ui->txtCommand->setEnabled(portOpened);
    ui->cmdCommandSend->setEnabled(portOpened);
    ui->widgetFeed->setEnabled(!m_transferringFile);

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
    ui->cmdFileReset->setEnabled(!m_transferringFile && m_tableModel.rowCount() > 1);
    ui->cmdFileSend->setEnabled(portOpened && !m_transferringFile && m_tableModel.rowCount() > 1);    
    ui->cmdFilePause->setEnabled(m_transferringFile);
    ui->actFileOpen->setEnabled(!m_transferringFile);
    ui->actFileSave->setEnabled(m_tableModel.rowCount() > 1);
    ui->actFileSaveAs->setEnabled(m_tableModel.rowCount() > 1);

    ui->tblProgram->setEditTriggers(m_transferringFile ? QAbstractItemView::NoEditTriggers :
                                                         QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked
                                                         | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);

    if (!portOpened) ui->txtStatus->setText(tr("Not connected"));

    this->setWindowTitle(m_programFileName.isEmpty() ? "grblControl"
                                                     : m_programFileName.mid(m_programFileName.lastIndexOf("/") + 1) + " - grblControl");

//    QRegExp rx("([^/]*)$");

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
    if (!m_serialPort.isOpen()) return;

    // Feed override
    if (ui->chkFeedOverride->isChecked()) command = GcodePreprocessorUtils::overrideSpeed(command, ui->txtFeed->value());

    // Commands queue
    if ((bufferLength() + command.length() + 1) > BUFFERLENGTH || m_queue.length() > 0) {

//        qDebug() << "queue:" << command;

        CommandQueue cq;

        cq.command = command;
        cq.tableIndex = tableIndex;

        m_queue.append(cq);

        while ((bufferLength() + m_queue[0].command.length() + 1) > BUFFERLENGTH) {
            qApp->processEvents();
        }

        cq = m_queue.takeFirst();
        command = cq.command;
        tableIndex = cq.tableIndex;

        if (!m_serialPort.isOpen() || m_reseting) return;

//        qDebug() << "get queue:" << cq.command;
    }

    CommandAttributes ca;

    if (!(command == "$G" && tableIndex < -1)
            && (!m_transferringFile || (m_transferringFile && m_showAllCommands) || tableIndex < 0)) {
        ui->txtConsole->appendPlainText(command);
        ca.consoleIndex = ui->txtConsole->blockCount() - 1;
    } else {
        ca.consoleIndex = -1;
    }

    ca.command = command;
    ca.length = command.length() + 1;
    ca.tableIndex = tableIndex;

    m_commands.append(ca);

    // Processing spindle speed only from g-code program
    QRegExp s("[Ss]0*(\\d+)");
    if (s.indexIn(command) != -1 && ca.tableIndex > -2) {
        int speed = s.cap(1).toInt();
        if (ui->sliSpindleSpeed->value() != speed / 100) {
            m_programSpeed = true;
            ui->sliSpindleSpeed->setValue(speed / 100);
            m_programSpeed = false;
            ui->txtSpindleSpeed->setValue(speed);
        }
    }

    m_serialPort.write((command + "\r").toLatin1());
}

void frmMain::grblReset()
{
    qDebug() << "reset begin";

    m_serialPort.write(QByteArray(1, (char)24));
    m_serialPort.flush();

    m_transferringFile = false;
    m_fileCommandIndex = 0;

    ui->cmdSpindle->setChecked(false);
    m_timerToolAnimation.stop();

//    m_timerConnection.stop();
    m_reseting = true;
    m_homing = false;

    m_commands.clear();
    ui->txtConsole->appendPlainText("[CTRL+X]");

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

        // Filter prereset responses
        if (m_reseting) {
            qDebug() << "reseting:" << data;
            if (data[0] == '[' || data[0] == '<' || dataIsEnd(data)) continue;
            else {
                m_commands.clear();
                m_reseting = false;
            }
        }

        // Status answer
        if (data[0] == '<') {
//            QRegExp rx("<([^,]*),MPos:([^,]*),([^,]*),([^,]*),WPos:([^,]*),([^,]*),([^,]*)>");

            int statusIndex = -1;

            // Status
            QRegExp stx("<([^,^>]*)");
            if (stx.indexIn(data) != -1) {
                statusIndex = m_status.indexOf(stx.cap(1));

                ui->txtStatus->setText(m_statusCaptions[statusIndex]);
                ui->txtStatus->setStyleSheet(QString("background-color: %1; color: %2;")
                                             .arg(m_statusBackColors[statusIndex]).arg(m_statusForeColors[statusIndex]));

                // Update controls
                ui->cmdReturnXY->setEnabled(statusIndex == 0);
                ui->cmdTopZ->setEnabled(statusIndex == 0);
                ui->chkTestMode->setChecked(statusIndex == 6);
                ui->cmdFilePause->setChecked(statusIndex == 4 || statusIndex == 5);

                // Store work origin
                if (statusIndex == 0) {
                    if (m_settingZeroXY) {
                        m_settingZeroXY = false;
                        m_storedX = ui->txtMPosX->text().toDouble();
                        m_storedY = ui->txtMPosY->text().toDouble();
                    } else if (m_settingZeroZ) {
                        m_settingZeroZ = false;
                        m_storedZ = ui->txtMPosZ->text().toDouble();
                    }
                }

                // Update "elapsed time" timer
                if (m_transferringFile) {
                    QTime time(0, 0, 0);
                    int elapsed = m_startTime.elapsed();
                    ui->glwVisualizator->setSpendTime(time.addMSecs(elapsed));
                }

                // Test for job complete
                if (m_transferCompleted && (statusIndex == 0 || statusIndex == 6) && m_fileCommandIndex == m_tableModel.rowCount() - 1 && m_transferringFile) {
                    m_transferringFile = false;
                    m_fileProcessedCommandIndex = 0;
                    m_lastDrawnLineIndex = 0;

                    QList<LineSegment*> list = m_viewParser.getLineSegmentList();

                    for (int i = m_lastDrawnLineIndex; i < list.length(); i++) {
                        list[i]->setDrawn(true);
                    }

                    updateControlsState();

                    qApp->beep();

                    m_timerStateQuery.stop();
                    m_timerConnection.stop();

                    QMessageBox::information(this, "grblControl", tr("Job done.\nTime elapsed: %1")
                                             .arg(ui->glwVisualizator->spendTime().toString("hh:mm:ss")));

                    m_timerConnection.start();
                    m_timerStateQuery.start();
                }
            }

            QRegExp wpx("WPos:([^,]*),([^,]*),([^,^>]*)");
            if (wpx.indexIn(data) != -1)
            {
                ui->txtWPosX->setText(wpx.cap(1));
                ui->txtWPosY->setText(wpx.cap(2));
                ui->txtWPosZ->setText(wpx.cap(3));

                // Update tool position                
                if (!(statusIndex == 6 && m_fileProcessedCommandIndex < m_tableModel.rowCount() - 1)) {
                    m_toolDrawer.setToolPosition(QVector3D(ui->txtWPosX->text().toDouble(),
                                                           ui->txtWPosY->text().toDouble(),
                                                           ui->txtWPosZ->text().toDouble()));
                }

                // Trajectory shadowing
                if (m_transferringFile && statusIndex != 6) {
                    bool toolOnTrajectory = false;

                    QList<int> drawnLines;
                    QList<LineSegment*> list = m_viewParser.getLineSegmentList();

                    for (int i = m_lastDrawnLineIndex; i < list.count()
                         && list[i]->getLineNumber()
                         <= (m_tableModel.data(m_tableModel.index(m_fileProcessedCommandIndex, 4)).toInt() + 1); i++) {
                        if (list[i]->contains(m_toolDrawer.toolPosition())) {
                            toolOnTrajectory = true;
                            m_lastDrawnLineIndex = i;
                            break;
                        }
                        drawnLines << i;
                    }

                    if (toolOnTrajectory) {
                        foreach (int i, drawnLines) {
                            list[i]->setDrawn(true);
                        }
                    } else if (m_lastDrawnLineIndex < list.count()) {
                        qDebug() << "tool missed:" << list[m_lastDrawnLineIndex]->getLineNumber()
                                 << m_tableModel.data(m_tableModel.index(m_fileProcessedCommandIndex, 4)).toInt()
                                 << m_fileProcessedCommandIndex;
                    }
                }
            }

            QRegExp mpx("MPos:([^,]*),([^,]*),([^,^>]*)");
            if (mpx.indexIn(data) != -1) {
                ui->txtMPosX->setText(mpx.cap(1));
                ui->txtMPosY->setText(mpx.cap(2));
                ui->txtMPosZ->setText(mpx.cap(3));
            }
        } else if (data.length() > 0) {

            // Processed commands
            if (m_commands.length() > 0) {

                static QString answer; // Full answer string

                if (dataIsEnd(data)) {

                    answer.append(data);

                    // Take command from buffer
                    CommandAttributes ca = m_commands.takeFirst();
                    QTextBlock tb = ui->txtConsole->document()->findBlockByNumber(ca.consoleIndex);
                    QTextCursor tc(tb);

                    // Restore absolute/relative coordinate system after jog
                    if (ca.command.toUpper() == "$G" && ca.tableIndex == -2 && answer.contains("G90")) {
                        if (ui->chkKeyboardControl->isChecked()) m_absoluteCoordinates = answer.contains("G90"); else sendCommand("G90");
                    }

                    // Print parser status
                    if (ca.command.toUpper() == "$G" && ca.tableIndex == -3) {
                        ui->glwVisualizator->setParserStatus(answer.left(answer.indexOf("; ")));
                    }

                    // Homing responce
                    if ((ca.command.toUpper() == "$H" || ca.command.toUpper() == "$T") && m_homing) m_homing = false;

                    // Add answer to console
                    if (tb.isValid() && tb.text() == ca.command) {

                        bool scrolledDown = ui->txtConsole->verticalScrollBar()->value() == ui->txtConsole->verticalScrollBar()->maximum();

                        // Update text block numbers
                        int blocksAdded = answer.count("; ");

                        if (blocksAdded > 0) for (int i = 0; i < m_commands.count(); i++) {
                            if (m_commands[i].consoleIndex != -1) m_commands[i].consoleIndex += blocksAdded;
                        }

                        tc.beginEditBlock();
                        tc.movePosition(QTextCursor::EndOfBlock);

                        tc.insertText(" < " + QString(answer).replace("; ", "\r\n"));
                        tc.endEditBlock();

                        if (scrolledDown) ui->txtConsole->verticalScrollBar()->setValue(ui->txtConsole->verticalScrollBar()->maximum());
                    }

                    // Add answer to table, send next program commands
                    if (m_transferringFile) {

                        // Only if command from table
                        if (ca.tableIndex > -1) {
                            m_tableModel.setData(m_tableModel.index(ca.tableIndex, 2), tr("Processed"));
                            m_tableModel.setData(m_tableModel.index(ca.tableIndex, 3), answer);

                            m_fileProcessedCommandIndex = ca.tableIndex;

                            if (ui->chkAutoScroll->isChecked() && ca.tableIndex != -1) {
                                ui->tblProgram->scrollTo(m_tableModel.index(ca.tableIndex + 1, 0));
                                ui->tblProgram->setCurrentIndex(m_tableModel.index(ca.tableIndex, 1));
                            }
                        }

                        // Send next program commands
                        if (m_fileCommandIndex < m_tableModel.rowCount()) {
                            sendNextFileCommands();
                        }
                    }

                    // Check transfer complete (last row always blank, last command row = rowcount - 2)
                    if (m_fileProcessedCommandIndex == m_tableModel.rowCount() - 2) m_transferCompleted = true;

                    // Trajectory shadowing on check mode
                    if (m_statusCaptions.indexOf(ui->txtStatus->text()) == 6 && m_fileProcessedCommandIndex < m_tableModel.rowCount() - 1) {
                        int i;
                        QList<int> drawnLines;
                        QList<LineSegment*> list = m_viewParser.getLineSegmentList();

                        for (i = m_lastDrawnLineIndex; i < list.count()
                             && list[i]->getLineNumber()
                             <= (m_tableModel.data(m_tableModel.index(m_fileProcessedCommandIndex, 4)).toInt() + 1); i++) {
                            drawnLines << i;
                        }

                        if (i < list.count()) {
                            m_lastDrawnLineIndex = i;
                            QVector3D vec = list[i]->getEnd();
                            m_toolDrawer.setToolPosition(vec);
                        }

                        foreach (int i, drawnLines) {
                            list[i]->setDrawn(true);
                        }
                    }

                    // Process spindle control commands
                    QRegExp m("[Mm]0*(\\d+)");
                    if (m.indexIn(ca.command) != -1) {
                        if (m.cap(1).toInt() == 3) {
                            m_timerToolAnimation.start(25, this);
                            ui->cmdSpindle->setChecked(true);
                        }
                        else if (m.cap(1).toInt() == 5 || m.cap(1).toInt() == 2) {
                            m_timerToolAnimation.stop();
                            ui->cmdSpindle->setChecked(false);
                        }
                    }
                    answer.clear();
                } else {
                    answer.append(data + "; ");
                }

            } else {
                ui->txtConsole->appendPlainText(data);
                qDebug() << "test:" << m_commands.length() << data;
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
    } else if (!m_homing && !m_reseting) {
        sendCommand("$G", -3);
    }
}

void frmMain::onTimerStateQuery()
{
    if (m_serialPort.isOpen()) {
        m_serialPort.write(QByteArray(1, '?'));
    }

    ui->glwVisualizator->setBufferState(QString(tr("Buffer: %1 / %2")).arg(bufferLength()).arg(m_queue.length()));

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

void frmMain::onScroolBarAction(int action)
{
    if (m_transferringFile) ui->chkAutoScroll->setChecked(false);
}

void frmMain::onJogTimer()
{
    m_jogBlock = false;
}

void frmMain::placeVisualizerButtons()
{
    ui->cmdIsometric->move(ui->glwVisualizator->width() - ui->cmdIsometric->width() - 8, 8);
    ui->cmdTop->move(ui->cmdIsometric->geometry().left() - ui->cmdTop->width() - 8, 8);
    ui->cmdLeft->move(ui->glwVisualizator->width() - ui->cmdLeft->width() - 8, ui->cmdIsometric->geometry().bottom() + 8);
    ui->cmdFront->move(ui->cmdLeft->geometry().left() - ui->cmdFront->width() - 8, ui->cmdIsometric->geometry().bottom() + 8);
//    ui->cmdFit->move(ui->cmdTop->geometry().left() - ui->cmdFit->width() - 10, 10);
    ui->cmdFit->move(ui->glwVisualizator->width() - ui->cmdFit->width() - 8, ui->cmdLeft->geometry().bottom() + 8);
}

void frmMain::showEvent(QShowEvent *se)
{
    placeVisualizerButtons();
}

void frmMain::resizeEvent(QResizeEvent *re)
{
    placeVisualizerButtons();
}

void frmMain::timerEvent(QTimerEvent *te)
{
    if (te->timerId() == m_timerToolAnimation.timerId()) {
        m_toolDrawer.rotate(-40 * (double)(ui->txtSpindleSpeed->value())
                            / (ui->txtSpindleSpeed->maximum() - ui->txtSpindleSpeed->minimum()));
//        ui->glwVisualizator->update();
    } else {
        QMainWindow::timerEvent(te);
    }
}

void frmMain::closeEvent(QCloseEvent *ce)
{
    if (m_serialPort.isOpen()) m_serialPort.close();
    if (m_queue.length() > 0) m_commands.clear();
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

    clearTable();
    m_programLoading = true;
    m_programFileName = fileName;

    QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();

    ui->tblProgram->setModel(NULL);

    GcodeParser gp;
    gp.setTraverseSpeed(m_rapidSpeed);

    QTime time;
    time.start();

    QString command;

    while (!textStream.atEnd())
    {
        command = textStream.readLine();

        gp.addCommand(command);

        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 1, 1), command);
        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 2, 2), tr("In queue"));
        m_tableModel.setData(m_tableModel.index(m_tableModel.rowCount() - 2, 4), gp.getCommandNumber());
    }

    qDebug() << "model filled:" << time.elapsed();

    time.start();

    m_programLoading = false;

    ui->tblProgram->setModel(&m_tableModel);
    ui->tblProgram->horizontalHeader()->restoreState(headerState);

    m_viewParser.reset();    
    updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_arcPrecision));

    qDebug() << "view parser filled:" << time.elapsed();

    for (int i = 0; i < 10 && i < gp.getPointSegmentList().count(); i++) {
        qDebug() << gp.getPointSegmentList().at(i)->point()->x()
                 << gp.getPointSegmentList().at(i)->point()->y()
                 << gp.getPointSegmentList().at(i)->point()->z();
    }

    ui->glwVisualizator->fitDrawables();
    updateControlsState();
}

QTime frmMain::updateProgramEstimatedTime(QList<LineSegment*> lines)
{
    double time = 0;
    foreach (LineSegment *ls, lines) {
        double length = (ls->getEnd() - ls->getStart()).length();

        if (!std::isnan(length) && !std::isnan(ls->getSpeed())) time +=
                length / ((ui->chkFeedOverride->isChecked() && !ls->isFastTraverse())
                          ? (ls->getSpeed() * ui->txtFeed->value() / 100) : ls->getSpeed());

//        if (std::isnan(length)) qDebug() << "length nan:" << ls->getStart() << ls->getEnd();
//        if (std::isnan(ls->getSpeed())) qDebug() << "speed nan:" << ls->getSpeed();
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
        GcodeParser gp;
        gp.setTraverseSpeed(m_rapidSpeed);

        for (int i = 0; i < m_tableModel.rowCount() - 1; i++) {
            gp.addCommand(m_tableModel.data(m_tableModel.index(i, 1)).toString());
            m_tableModel.setData(m_tableModel.index(i, 4), gp.getCommandNumber());
        }

        m_viewParser.reset();

        updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_arcPrecision));
        updateControlsState();
    }
}

void frmMain::on_actServiceSettings_triggered()
{
    QList<double> storedValues;
    QList<bool> storedChecks;
    QList<QString> storedCombos;

    foreach (QAbstractSpinBox* sb, m_frmSettings.findChildren<QAbstractSpinBox*>())
    {
        storedValues.append(sb->property("value").toDouble());
    }

    foreach (QCheckBox* cb, m_frmSettings.findChildren<QCheckBox*>())
    {
        storedChecks.append(cb->isChecked());
    }

    foreach (QComboBox* cb, m_frmSettings.findChildren<QComboBox*>())
    {
        storedCombos.append(cb->currentText());
    }

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
    } else {
        foreach (QAbstractSpinBox* sb, m_frmSettings.findChildren<QAbstractSpinBox*>())
        {
            sb->setProperty("value", storedValues.takeFirst());
        }

        foreach (QCheckBox* cb, m_frmSettings.findChildren<QCheckBox*>())
        {
            cb->setChecked(storedChecks.takeFirst());
        }
        foreach (QComboBox* cb, m_frmSettings.findChildren<QComboBox*>())
        {
            cb->setCurrentText(storedCombos.takeFirst());
        }
    }
}

void frmMain::applySettings() {
    m_toolDrawer.setToolDiameter(m_frmSettings.toolDiameter());
    m_toolDrawer.setToolLength(m_frmSettings.toolLength());
    m_toolDrawer.setLineWidth(m_frmSettings.lineWidth());
    m_codeDrawer->setLineWidth(m_frmSettings.lineWidth());
    m_arcPrecision = m_frmSettings.arcPrecision();
    ui->glwVisualizator->setLineWidth(m_frmSettings.lineWidth());
    m_showAllCommands = m_frmSettings.showAllCommands();
    m_safeZ = m_frmSettings.safeZ();
    m_rapidSpeed = m_frmSettings.rapidSpeed();
    m_timerStateQuery.setInterval(m_frmSettings.queryStateTime());
    m_toolDrawer.setToolAngle(m_frmSettings.toolType() == 0 ? 180 : m_frmSettings.toolAngle());
    ui->glwVisualizator->setAntialiasing(m_frmSettings.antialiasing());
    ui->glwVisualizator->setZBuffer(m_frmSettings.zBuffer());
    ui->glwVisualizator->setFps(m_frmSettings.fps());
    ui->txtSpindleSpeed->setMinimum(m_frmSettings.spindleSpeedMin());
    ui->txtSpindleSpeed->setMaximum(m_frmSettings.spindleSpeedMax());
    ui->sliSpindleSpeed->setMinimum(ui->txtSpindleSpeed->minimum() / 100);
    ui->sliSpindleSpeed->setMaximum(ui->txtSpindleSpeed->maximum() / 100);
//    ui->glwVisualizator->update();
}

void frmMain::on_cmdCommandSend_clicked()
{
    if (ui->txtCommand->text().isEmpty()) return;

    QString command = ui->txtCommand->text();

    ui->txtCommand->clear();
    sendCommand(command, -1);
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
    sendCommand(QString("G53G90G0X%1Y%2").arg(m_storedX).arg(m_storedY));
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
    sendCommand(QString("G53G90G0Z%1").arg(m_safeZ));
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
    m_programSpeed = true;
    ui->sliSpindleSpeed->setValue(ui->txtSpindleSpeed->value() / 100);
    m_programSpeed = false;
    sendCommand(QString("S%1").arg(ui->txtSpindleSpeed->value()), -2);
}

void frmMain::on_sliSpindleSpeed_valueChanged(int value)
{
    if (!m_programSpeed) {
        ui->txtSpindleSpeed->setValue(ui->sliSpindleSpeed->value() * 100);
        sendCommand(QString("S%1").arg(ui->sliSpindleSpeed->value() * 100), -2);
    }
}

void frmMain::on_cmdYPlus_clicked()
{
    if (m_jogBlock) return;
    // Query parser state to restore coordinate system, hide from table and console
    if (!ui->chkKeyboardControl->isChecked()) sendCommand("$G", -2);
    blockJogForRapidMovement();
    sendCommand("G91G0Y" + ui->txtJogStep->text());
}

void frmMain::on_cmdYMinus_clicked()
{
    if (m_jogBlock) return;
    if (!ui->chkKeyboardControl->isChecked()) sendCommand("$G", -2);
    blockJogForRapidMovement();
    sendCommand("G91G0Y-" + ui->txtJogStep->text());
}

void frmMain::on_cmdXPlus_clicked()
{
    if (m_jogBlock) return;
    if (!ui->chkKeyboardControl->isChecked()) sendCommand("$G", -2);
    blockJogForRapidMovement();
    sendCommand("G91G0X" + ui->txtJogStep->text());
}

void frmMain::on_cmdXMinus_clicked()
{    
    if (m_jogBlock) return;
    if (!ui->chkKeyboardControl->isChecked()) sendCommand("$G", -2);
    blockJogForRapidMovement();
    sendCommand("G91G0X-" + ui->txtJogStep->text());
}

void frmMain::on_cmdZPlus_clicked()
{
    if (m_jogBlock) return;
    if (!ui->chkKeyboardControl->isChecked()) sendCommand("$G", -2);
    blockJogForRapidMovement();
    sendCommand("G91G0Z" + ui->txtJogStep->text());
}

void frmMain::on_cmdZMinus_clicked()
{
    if (m_jogBlock) return;
    if (!ui->chkKeyboardControl->isChecked()) sendCommand("$G", -2);
    blockJogForRapidMovement();
    sendCommand("G91G0Z-" + ui->txtJogStep->text());
}

void frmMain::on_chkTestMode_clicked()
{
    sendCommand("$C");
}

void frmMain::on_cmdFilePause_clicked(bool checked)
{
    m_serialPort.write(checked ? "!" : "~");
}

void frmMain::on_cmdFileReset_clicked()
{
    m_fileCommandIndex = 0;
    m_fileProcessedCommandIndex = 0;
    m_lastDrawnLineIndex = 0;

    QTime time;

    time.start();

    int n = m_viewParser.getLineSegmentList().length();
    QList<LineSegment*> list = m_viewParser.getLineSegmentList();

    for (int i = m_lastDrawnLineIndex; i < list.count(); i++) {
        list[i]->setDrawn(false);

        if (i < 10) qDebug() << i << list[i]->getStart() << list[i]->getEnd();
    }      

    qDebug() << "drawn false:" << time.elapsed();

    time.start();

    ui->tblProgram->setUpdatesEnabled(false);
    for (int i = 0; i < m_tableModel.rowCount() - 1; i++) {
        m_tableModel.setData(m_tableModel.index(i, 2), tr("In queue"));
        m_tableModel.setData(m_tableModel.index(i, 3), "");
    }
    ui->tblProgram->setUpdatesEnabled(true);

    qDebug() << "table updated:" << time.elapsed();

    ui->tblProgram->scrollTo(m_tableModel.index(0, 0));
    ui->tblProgram->clearSelection();

    ui->glwVisualizator->setSpendTime(QTime(0, 0, 0));
}

void frmMain::on_actFileNew_triggered()
{
    clearTable();
    m_viewParser.reset();
    ui->glwVisualizator->fitDrawables();
    m_programFileName = "";

    updateControlsState();
}

void frmMain::on_cmdClearConsole_clicked()
{
    ui->txtConsole->clear();
}

bool frmMain::saveProgramToFile(QString fileName)
{
    QFile file(fileName);
    QDir dir;

    qDebug() << "Saving program";

    if (file.exists()) dir.remove(file.fileName());

    if (!file.open(QIODevice::WriteOnly)) return false;

    QTextStream textStream(&file);

    for (int i = 0; i < m_tableModel.rowCount() - 1; i++) {
        textStream << m_tableModel.data(m_tableModel.index(i, 1)).toString() << "\r\n";
    }

    return true;
}

void frmMain::on_actFileSaveAs_triggered()
{
    QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), "", tr("G-Code files (*.nc;*.ncc;*.tap)")));

    if (!fileName.isEmpty()) if (saveProgramToFile(fileName)) {
        m_programFileName = fileName;
        updateControlsState();
    }
}

void frmMain::on_actFileSave_triggered()
{
    if (m_programFileName.isEmpty()) on_actFileSaveAs_triggered(); else saveProgramToFile(m_programFileName);
}

void frmMain::on_cmdTop_clicked()
{
    ui->glwVisualizator->setTopView();
}

void frmMain::on_cmdFront_clicked()
{
    ui->glwVisualizator->setFrontView();
}

void frmMain::on_cmdLeft_clicked()
{
    ui->glwVisualizator->setLeftView();
}

void frmMain::on_cmdIsometric_clicked()
{
    ui->glwVisualizator->setIsometricView();
}

void frmMain::on_actAbout_triggered()
{
    m_frmAbout.exec();
}

bool frmMain::dataIsEnd(QString data) {
    QStringList ends;

    ends << "ok";
    ends << "error";
    ends << "Reset to continue";
//    ends << "'$' for help";
//    ends << "'$H'|'$X' to unlock";
//    ends << "Caution: Unlocked";
//    ends << "Enabled";
//    ends << "Disabled";
//    ends << "Check Door";
//    ends << "Pgm End";

    foreach (QString str, ends) {
        if (data.contains(str)) return true;
    }

    return false;
}

void frmMain::on_txtFeed_editingFinished()
{
    ui->sliFeed->setValue(ui->txtFeed->value());
}

void frmMain::on_sliFeed_valueChanged(int value)
{
    ui->txtFeed->setValue(value);
    updateProgramEstimatedTime(m_viewParser.getLineSegmentList());
}

void frmMain::on_chkFeedOverride_toggled(bool checked)
{
    ui->grpFeed->setProperty("overrided", checked);
    style()->unpolish(ui->grpFeed);
    ui->grpFeed->ensurePolished();
    updateProgramEstimatedTime(m_viewParser.getLineSegmentList());
}

void frmMain::on_grpFeed_toggled(bool checked)
{
    ui->widgetFeed->setVisible(checked);
}

void frmMain::on_grpSpindle_toggled(bool checked)
{
    ui->widgetSpindle->setVisible(checked);
}

void frmMain::on_grpJog_toggled(bool checked)
{
    ui->widgetJog->setVisible(checked);
}

bool buttonLessThan(StyledToolButton *b1, StyledToolButton *b2)
{
    return b1->text().toDouble() < b2->text().toDouble();
}

void frmMain::blockJogForRapidMovement() {
    m_jogBlock = true;

    const double acc = m_frmSettings.acceleration();    // Acceleration mm/sec^2
    double v = m_frmSettings.rapidSpeed() / 60;         // Rapid speed mm/sec
    double at = v / acc;                                // Acceleration time
    double s = acc * at * at / 2;                       // Distance on acceleration
    double time = (ui->txtJogStep->text().toDouble() - 2 * s) / v + at;

//                qDebug() << QString("acc: %1; v: %2; at: %3; s: %4; time: %5").arg(acc).arg(v).arg(at).arg(s).arg(time);
    QTimer::singleShot(time * 1000, Qt::PreciseTimer, this, SLOT(onJogTimer()));
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (ui->widgetJog->isEnabled() && ui->chkKeyboardControl->isChecked()) {
            if (keyEvent->key() == Qt::Key_4) {
                on_cmdXMinus_clicked();
            }
            else if (keyEvent->key() == Qt::Key_6) {
                on_cmdXPlus_clicked();
            }
            else if (keyEvent->key() == Qt::Key_8) {
                on_cmdYPlus_clicked();
            }
            else if (keyEvent->key() == Qt::Key_2) {
                on_cmdYMinus_clicked();
            }
            else if (keyEvent->key() == Qt::Key_9) {
                on_cmdZPlus_clicked();
            }
            else if (keyEvent->key() == Qt::Key_3) {
                on_cmdZMinus_clicked();
            }
            else if (keyEvent->key() == Qt::Key_5) {
                QList<StyledToolButton*> stepButtons = ui->grpJog->findChildren<StyledToolButton*>(QRegExp("cmdJogStep\\d"));
                std::sort(stepButtons.begin(), stepButtons.end(), buttonLessThan);

                for (int i = 0; i < stepButtons.count(); i++) {
                    if (stepButtons[i]->isChecked()) {
                        stepButtons[i == stepButtons.length() - 1 ? 0 : i + 1]->click();
                        break;
                    }
                }
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void frmMain::on_chkKeyboardControl_toggled(bool checked)
{
    ui->grpJog->setProperty("overrided", checked);
    style()->unpolish(ui->grpJog);
    ui->grpJog->ensurePolished();

    // Store/restore coordinate system
    if (checked) sendCommand("$G", -2); else if (m_absoluteCoordinates) sendCommand("G90");
}
