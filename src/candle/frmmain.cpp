// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#define UNKNOWN 0
#define IDLE 1
#define ALARM 2
#define RUN 3
#define HOME 4
#define HOLD0 5
#define HOLD1 6
#define QUEUE 7
#define CHECK 8
#define DOOR 9
#define JOG 10

#define PROGRESSMINLINES 10000
#define PROGRESSSTEP     1000

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QTextBlock>
#include <QTextCursor>
#include <QMessageBox>
#include <QComboBox>
#include <QScrollBar>
#include <QShortcut>
#include <QAction>
#include <QLayout>
#include <QMimeData>
#include "frmmain.h"
#include "ui_frmmain.h"
#include "ui_frmsettings.h"
#include "widgets/widgetmimedata.h"
#include "widgets/uiloader.h"

frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain)
{
    // Initializing variables
    m_status << "Unknown"
             << "Idle"
             << "Alarm"
             << "Run"
             << "Home"
             << "Hold:0"
             << "Hold:1"
             << "Queue"
             << "Check"
             << "Door"                     // TODO: Update "Door" state
             << "Jog";
    m_statusCaptions << tr("Unknown")
                     << tr("Idle")
                     << tr("Alarm")
                     << tr("Run")
                     << tr("Home")
                     << tr("Hold")
                     << tr("Hold")
                     << tr("Queue")
                     << tr("Check")
                     << tr("Door")
                     << tr("Jog");
    m_statusBackColors << "red"
                       << "palette(button)"
                       << "red"
                       << "lime"
                       << "lime"
                       << "yellow"
                       << "yellow"
                       << "yellow"
                       << "palette(button)"
                       << "red"
                       << "lime";
    m_statusForeColors << "white"
                       << "palette(text)"
                       << "white"
                       << "black"
                       << "black"
                       << "black"
                       << "black"
                       << "black"
                       << "palette(text)"
                       << "white"
                       << "black";

    m_fileChanged = false;
    m_heightMapChanged = false;
   
    m_storedX = 0;
    m_storedY = 0;
    m_storedZ = 0;
   
    m_homing = false;
    m_updateSpindleSpeed = false;
    m_updateParserStatus = false;
    m_updateFeed = false;

    m_reseting = false;
    m_resetCompleted = true;
    m_aborting = false;
    m_statusReceived = false;

    m_processingFile = false;
    m_transferCompleted = false;
    m_fileEndSent = false;

    m_keyPressed = false;
    m_jogBlock = false;

    m_spindleCW = true;
    m_spindleCommandSpeed = false;

    // Loading settings
    m_settingsFileName = qApp->applicationDirPath() + "/settings.ini";
    preloadSettings();

    m_settings = new frmSettings(this);
    ui->setupUi(this);

    // Drop frames
    ui->fraDropDevice->setVisible(false);
    ui->fraDropModification->setVisible(false);
    ui->fraDropUser->setVisible(false);

#ifdef WINDOWS
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
        m_taskBarButton = NULL;
        m_taskBarProgress = NULL;
    }
#endif

#ifndef UNIX
    ui->cboCommand->setStyleSheet("QComboBox {padding: 2;} QComboBox::drop-down {width: 0; border-style: none;} QComboBox::down-arrow {image: url(noimg);	border-width: 0;}");
#endif
//    ui->scrollArea->updateMinimumWidth();

    m_heightMapMode = false;
    m_lastDrawnLineIndex = 0;
    m_fileProcessedCommandIndex = 0;
    m_cellChanged = false;
    m_programLoading = false;
    m_currentModel = &m_programModel;
    m_transferCompleted = true;

    // Dock widgets
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    ui->widgetHeightmapSettings->setVisible(false);

    ui->cmdXMinus->setBackColor(QColor(153, 180, 209));
    ui->cmdXPlus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYMinus->setBackColor(ui->cmdXMinus->backColor());
    ui->cmdYPlus->setBackColor(ui->cmdXMinus->backColor());

    ui->cmdFit->setParent(ui->glwVisualizer);
    ui->cmdIsometric->setParent(ui->glwVisualizer);
    ui->cmdTop->setParent(ui->glwVisualizer);
    ui->cmdFront->setParent(ui->glwVisualizer);
    ui->cmdLeft->setParent(ui->glwVisualizer);

    ui->cmdHeightMapBorderAuto->setMinimumHeight(ui->chkHeightMapBorderShow->sizeHint().height());
    ui->cmdHeightMapCreate->setMinimumHeight(ui->cmdFileOpen->sizeHint().height());
    ui->cmdHeightMapLoad->setMinimumHeight(ui->cmdFileOpen->sizeHint().height());
    ui->cmdHeightMapMode->setMinimumHeight(ui->cmdFileOpen->sizeHint().height());

    ui->cboJogStep->setValidator(new QDoubleValidator(0, 10000, 2));
    ui->cboJogFeed->setValidator(new QIntValidator(0, 100000));
    connect(ui->cboJogStep, &ComboBoxKey::currentTextChanged, this, &frmMain::updateJogTitle);
    connect(ui->cboJogFeed, &ComboBoxKey::currentTextChanged, this, &frmMain::updateJogTitle);

    // Prepare "Send"-button
    ui->cmdFileSend->setMinimumWidth(qMax(ui->cmdFileSend->width(), ui->cmdFileOpen->width()));
    QMenu *menuSend = new QMenu();
    menuSend->addAction(tr("Send from current line"), this, SLOT(onActSendFromLineTriggered()));
    ui->cmdFileSend->setMenu(menuSend);

    connect(ui->cboCommand, SIGNAL(returnPressed()), this, SLOT(onCboCommandReturnPressed()));

    foreach (StyledToolButton* button, this->findChildren<StyledToolButton*>(QRegExp("cmdUser\\d"))) {
        connect(button, SIGNAL(clicked(bool)), this, SLOT(onCmdUserClicked(bool)));
    }

    // Setting up slider boxes
    ui->slbFeedOverride->setRatio(1);
    ui->slbFeedOverride->setMinimum(10);
    ui->slbFeedOverride->setMaximum(200);
    ui->slbFeedOverride->setCurrentValue(100);
    ui->slbFeedOverride->setTitle(tr("Feed rate:"));
    ui->slbFeedOverride->setSuffix("%");
    connect(ui->slbFeedOverride, SIGNAL(toggled(bool)), this, SLOT(onOverridingToggled(bool)));
    connect(ui->slbFeedOverride, &SliderBox::toggled, this, &frmMain::onOverrideChanged);
    connect(ui->slbFeedOverride, &SliderBox::valueChanged, this, &frmMain::onOverrideChanged);

    ui->slbRapidOverride->setRatio(50);
    ui->slbRapidOverride->setMinimum(25);
    ui->slbRapidOverride->setMaximum(100);
    ui->slbRapidOverride->setCurrentValue(100);
    ui->slbRapidOverride->setTitle(tr("Rapid speed:"));
    ui->slbRapidOverride->setSuffix("%");
    connect(ui->slbRapidOverride, SIGNAL(toggled(bool)), this, SLOT(onOverridingToggled(bool)));
    connect(ui->slbRapidOverride, &SliderBox::toggled, this, &frmMain::onOverrideChanged);
    connect(ui->slbRapidOverride, &SliderBox::valueChanged, this, &frmMain::onOverrideChanged);   

    ui->slbSpindleOverride->setRatio(1);
    ui->slbSpindleOverride->setMinimum(50);
    ui->slbSpindleOverride->setMaximum(200);
    ui->slbSpindleOverride->setCurrentValue(100);
    ui->slbSpindleOverride->setTitle(tr("Spindle speed:"));
    ui->slbSpindleOverride->setSuffix("%");
    connect(ui->slbSpindleOverride, SIGNAL(toggled(bool)), this, SLOT(onOverridingToggled(bool)));

    m_originDrawer = new OriginDrawer();
    m_codeDrawer = new GcodeDrawer();
    m_codeDrawer->setViewParser(&m_viewParser);
    m_probeDrawer = new GcodeDrawer();
    m_probeDrawer->setViewParser(&m_probeParser);
    m_probeDrawer->setVisible(false);
    m_heightMapGridDrawer.setModel(&m_heightMapModel);
    m_currentDrawer = m_codeDrawer;
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 0));

    QShortcut *insertShortcut = new QShortcut(QKeySequence(Qt::Key_Insert), ui->tblProgram);
    QShortcut *deleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->tblProgram);

    connect(insertShortcut, SIGNAL(activated()), this, SLOT(onTableInsertLine()));
    connect(deleteShortcut, SIGNAL(activated()), this, SLOT(onTableDeleteLines()));

    m_tableMenu = new QMenu(this);
    m_tableMenu->addAction(tr("&Insert line"), this, SLOT(onTableInsertLine()), insertShortcut->key());
    m_tableMenu->addAction(tr("&Delete lines"), this, SLOT(onTableDeleteLines()), deleteShortcut->key());

    ui->glwVisualizer->addDrawable(m_originDrawer);
    ui->glwVisualizer->addDrawable(m_codeDrawer);
    ui->glwVisualizer->addDrawable(m_probeDrawer);
    ui->glwVisualizer->addDrawable(&m_toolDrawer);
    ui->glwVisualizer->addDrawable(&m_heightMapBorderDrawer);
    ui->glwVisualizer->addDrawable(&m_heightMapGridDrawer);
    ui->glwVisualizer->addDrawable(&m_heightMapInterpolationDrawer);
    ui->glwVisualizer->addDrawable(&m_selectionDrawer);
    ui->glwVisualizer->fitDrawable();

    connect(ui->glwVisualizer, SIGNAL(rotationChanged()), this, SLOT(onVisualizatorRotationChanged()));
    connect(ui->glwVisualizer, SIGNAL(resized()), this, SLOT(placeVisualizerButtons()));
    connect(&m_programModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCellChanged(QModelIndex,QModelIndex)));
    connect(&m_programHeightmapModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCellChanged(QModelIndex,QModelIndex)));
    connect(&m_probeModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCellChanged(QModelIndex,QModelIndex)));
    connect(&m_heightMapModel, SIGNAL(dataChangedByUserInput()), this, SLOT(updateHeightMapInterpolationDrawer()));

    ui->tblProgram->setModel(&m_programModel);
    ui->tblProgram->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    connect(ui->tblProgram->verticalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(onScroolBarAction(int)));
    connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));    
    clearTable();

    m_senderErrorBox = new QMessageBox(QMessageBox::Warning, qApp->applicationDisplayName(), QString(),
                                       QMessageBox::Ignore | QMessageBox::Abort, this);
    m_senderErrorBox->setCheckBox(new QCheckBox(tr("Don't show again")));

    // Loading settings
    loadSettings();
    ui->tblProgram->hideColumn(4);
    ui->tblProgram->hideColumn(5);
    updateControlsState();

    // Prepare jog buttons
    foreach (StyledToolButton* button, ui->grpJog->findChildren<StyledToolButton*>(QRegExp("cmdJogFeed\\d")))
    {
        connect(button, SIGNAL(clicked(bool)), this, SLOT(onCmdJogFeedClicked()));
    }

    // Setting up spindle slider box
    ui->slbSpindle->setTitle(tr("Speed:"));
    ui->slbSpindle->setCheckable(false);
    ui->slbSpindle->setChecked(true);
    connect(ui->slbSpindle, &SliderBox::valueUserChanged, this, &frmMain::onSlbSpindleValueUserChanged);
    connect(ui->slbSpindle, &SliderBox::valueChanged, this, &frmMain::onSlbSpindleValueChanged);

    // Setup serial port
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort.setStopBits(QSerialPort::OneStop);

    if (m_settings->port() != "") {
        m_serialPort.setPortName(m_settings->port());
        m_serialPort.setBaudRate(m_settings->baud());
    }

    // Setup actions
    addAction(ui->actControlHome);
    addAction(ui->actControlTouch);
    addAction(ui->actControlZeroXY);
    addAction(ui->actControlZeroZ);
    addAction(ui->actControlRestoreOrigin);
    addAction(ui->actControlSafePosition);
    addAction(ui->actControlReset);
    addAction(ui->actControlUnlock);
    addAction(ui->actUserCommand1);
    addAction(ui->actUserCommand2);
    addAction(ui->actUserCommand3);
    addAction(ui->actUserCommand4);

    addAction(ui->actVisualizerFit);
    addAction(ui->actVisualizerIsometric);
    addAction(ui->actVisualizerTop);
    addAction(ui->actVisualizerFront);
    addAction(ui->actVisualizerLeft);
    
    addAction(ui->actProgramCheck);
    addAction(ui->actProgramScroll);
    addAction(ui->actProgramReset);
    addAction(ui->actProgramSend);
    addAction(ui->actProgramPause);
    addAction(ui->actProgramAbort);

    addAction(ui->actHeightmapUse);
    addAction(ui->actHeightmapCreate);
    addAction(ui->actHeightmapOpen);
    addAction(ui->actHeightmapEdit);
    addAction(ui->actHeightmapShowBorder);
    addAction(ui->actHeightmapShowProbeGrid);
    addAction(ui->actHeightmapShowInterpolationGrid);
    
    addAction(ui->actJogStop);
    addAction(ui->actJogStepNext);
    addAction(ui->actJogStepPrevious);
    addAction(ui->actJogFeedNext);
    addAction(ui->actJogFeedPrevious);
    addAction(ui->actJogKeyboardControl);
    addAction(ui->actSpindleSpeedPlus);
    addAction(ui->actSpindleSpeedMinus);
    addAction(ui->actSpindleOnOff);
    addAction(ui->actOverrideFeed);
    addAction(ui->actOverrideFeedPlus);
    addAction(ui->actOverrideFeedMinus);
    addAction(ui->actOverrideRapid);
    addAction(ui->actOverrideRapidPlus);
    addAction(ui->actOverrideRapidMinus);
    addAction(ui->actOverrideSpindle);
    addAction(ui->actOverrideSpindlePlus);
    addAction(ui->actOverrideSpindleMinus);

    addAction(ui->actConsoleClear);    

    // Handle file drop
    if (qApp->arguments().count() > 1 && isGCodeFile(qApp->arguments().last())) {
        loadFile(qApp->arguments().last());
    }
    
    // Delegate vars to script engine
    QScriptValue vars = m_scriptEngine.newQObject(&m_storedVars);
    m_scriptEngine.globalObject().setProperty("vars", vars);

    // Signals/slots
    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(onSerialPortReadyRead()), Qt::QueuedConnection);
    connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onSerialPortError(QSerialPort::SerialPortError)));
    connect(&m_timerConnection, SIGNAL(timeout()), this, SLOT(onTimerConnection()));
    connect(&m_timerStateQuery, SIGNAL(timeout()), this, SLOT(onTimerStateQuery()));

    // Event filter
    qApp->installEventFilter(this);

    // Start timers
    m_timerConnection.start(1000);
    m_timerStateQuery.start();
}

frmMain::~frmMain()
{    
    delete m_senderErrorBox;
    delete ui;
}

bool frmMain::isGCodeFile(QString fileName)
{
    return fileName.endsWith(".txt", Qt::CaseInsensitive)
          || fileName.endsWith(".nc", Qt::CaseInsensitive)
          || fileName.endsWith(".ncc", Qt::CaseInsensitive)
          || fileName.endsWith(".ngc", Qt::CaseInsensitive)
          || fileName.endsWith(".tap", Qt::CaseInsensitive);
}

bool frmMain::isHeightmapFile(QString fileName)
{
    return fileName.endsWith(".map", Qt::CaseInsensitive);
}

double frmMain::toolZPosition()
{
    return m_toolDrawer.toolPosition().z();
}

void frmMain::preloadSettings()
{
    QSettings set(m_settingsFileName, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    qApp->setStyleSheet(QString(qApp->styleSheet()).replace(QRegExp("font-size:\\s*\\d+"), "font-size: " + set.value("fontSize", "8").toString()));

    // Update v-sync in glformat
    QGLFormat fmt = QGLFormat::defaultFormat();
    fmt.setSwapInterval(set.value("vsync", false).toBool() ? 1 : 0);
    QGLFormat::setDefaultFormat(fmt);
}

void frmMain::loadSettings()
{
    QSettings set(m_settingsFileName, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    m_settingsLoading = true;

    m_settings->setFontSize(set.value("fontSize", 8).toInt());
    m_settings->setPort(set.value("port").toString());
    m_settings->setBaud(set.value("baud").toInt());
    m_settings->setIgnoreErrors(set.value("ignoreErrors", false).toBool());
    m_settings->setAutoLine(set.value("autoLine", true).toBool());
    m_settings->setToolDiameter(set.value("toolDiameter", 3).toDouble());
    m_settings->setToolLength(set.value("toolLength", 15).toDouble());
    m_settings->setAntialiasing(set.value("antialiasing", true).toBool());
    m_settings->setMsaa(set.value("msaa", true).toBool());
    m_settings->setVsync(set.value("vsync", false).toBool());
    m_settings->setZBuffer(set.value("zBuffer", false).toBool());
    m_settings->setSimplify(set.value("simplify", false).toBool());
    m_settings->setSimplifyPrecision(set.value("simplifyPrecision", 0).toDouble());
    m_settings->setGrayscaleSegments(set.value("grayscaleSegments", false).toBool());
    m_settings->setGrayscaleSCode(set.value("grayscaleSCode", true).toBool());
    m_settings->setDrawModeVectors(set.value("drawModeVectors", true).toBool());    
    m_settings->setMoveOnRestore(set.value("moveOnRestore", false).toBool());
    m_settings->setRestoreMode(set.value("restoreMode", 0).toInt());
    m_settings->setLineWidth(set.value("lineWidth", 1).toDouble());
    m_settings->setArcLength(set.value("arcLength", 0).toDouble());
    m_settings->setArcDegree(set.value("arcDegree", 0).toDouble());
    m_settings->setArcDegreeMode(set.value("arcDegreeMode", true).toBool());
    m_settings->setShowProgramCommands(set.value("showProgramCommands", 0).toBool());
    m_settings->setShowUICommands(set.value("showUICommands", 0).toBool());
    m_settings->setSpindleSpeedMin(set.value("spindleSpeedMin", 0).toInt());
    m_settings->setSpindleSpeedMax(set.value("spindleSpeedMax", 100).toInt());
    m_settings->setLaserPowerMin(set.value("laserPowerMin", 0).toInt());
    m_settings->setLaserPowerMax(set.value("laserPowerMax", 100).toInt());
    m_settings->setRapidSpeed(set.value("rapidSpeed", 0).toInt());
    m_settings->setHeightmapProbingFeed(set.value("heightmapProbingFeed", 0).toInt());
    m_settings->setAcceleration(set.value("acceleration", 10).toInt());
    m_settings->setToolAngle(set.value("toolAngle", 0).toDouble());
    m_settings->setToolType(set.value("toolType", 0).toInt());
    m_settings->setFps(set.value("fps", 60).toInt());
    m_settings->setQueryStateTime(set.value("queryStateTime", 250).toInt());

    ui->chkAutoScroll->setChecked(set.value("autoScroll", false).toBool());

    ui->slbSpindle->setRatio(100);
    ui->slbSpindle->setMinimum(m_settings->spindleSpeedMin());
    ui->slbSpindle->setMaximum(m_settings->spindleSpeedMax());
    ui->slbSpindle->setValue(set.value("spindleSpeed", 100).toInt());

    ui->slbFeedOverride->setChecked(set.value("feedOverride", false).toBool());
    ui->slbFeedOverride->setValue(set.value("feedOverrideValue", 100).toInt());

    ui->slbRapidOverride->setChecked(set.value("rapidOverride", false).toBool());
    ui->slbRapidOverride->setValue(set.value("rapidOverrideValue", 100).toInt());

    ui->slbSpindleOverride->setChecked(set.value("spindleOverride", false).toBool());
    ui->slbSpindleOverride->setValue(set.value("spindleOverrideValue", 100).toInt());

    m_settings->setUnits(set.value("units", 0).toInt());
    m_storedX = set.value("storedX", 0).toDouble();
    m_storedY = set.value("storedY", 0).toDouble();
    m_storedZ = set.value("storedZ", 0).toDouble();
    m_storedCS = set.value("storedCS", "G54").toString();

    ui->cmdRestoreOrigin->setToolTip(QString(tr("Restore origin:\n%1, %2, %3")).arg(m_storedX).arg(m_storedY).arg(m_storedZ));

    m_recentFiles = set.value("recentFiles", QStringList()).toStringList();
    m_recentHeightmaps = set.value("recentHeightmaps", QStringList()).toStringList();
    m_lastFolder = set.value("lastFolder", QDir::homePath()).toString();

    this->restoreGeometry(set.value("formGeometry", QByteArray()).toByteArray());

    ui->cboCommand->setMinimumHeight(ui->cboCommand->height());
    ui->cmdClearConsole->setFixedHeight(ui->cboCommand->height());
    ui->cmdCommandSend->setFixedHeight(ui->cboCommand->height());

    m_storedKeyboardControl = set.value("keyboardControl", false).toBool();

    m_settings->setAutoCompletion(set.value("autoCompletion", true).toBool());
    m_settings->setTouchCommand(set.value("touchCommand").toString());
    m_settings->setSafePositionCommand(set.value("safePositionCommand").toString());

    foreach (StyledToolButton* button, this->findChildren<StyledToolButton*>(QRegExp("cmdUser\\d"))) {
        int i = button->objectName().right(1).toInt();
        m_settings->setUserCommands(i, set.value(QString("userCommands%1").arg(i)).toString());
    }

    ui->cboJogStep->setItems(set.value("jogSteps").toStringList());
    ui->cboJogStep->setCurrentIndex(ui->cboJogStep->findText(set.value("jogStep").toString()));
    ui->cboJogFeed->setItems(set.value("jogFeeds").toStringList());
    ui->cboJogFeed->setCurrentIndex(ui->cboJogFeed->findText(set.value("jogFeed").toString()));

    ui->txtHeightMapBorderX->setValue(set.value("heightmapBorderX", 0).toDouble());
    ui->txtHeightMapBorderY->setValue(set.value("heightmapBorderY", 0).toDouble());
    ui->txtHeightMapBorderWidth->setValue(set.value("heightmapBorderWidth", 1).toDouble());
    ui->txtHeightMapBorderHeight->setValue(set.value("heightmapBorderHeight", 1).toDouble());
    ui->chkHeightMapBorderShow->setChecked(set.value("heightmapBorderShow", false).toBool());

    ui->txtHeightMapGridX->setValue(set.value("heightmapGridX", 1).toDouble());
    ui->txtHeightMapGridY->setValue(set.value("heightmapGridY", 1).toDouble());
    ui->txtHeightMapGridZTop->setValue(set.value("heightmapGridZTop", 1).toDouble());
    ui->txtHeightMapGridZBottom->setValue(set.value("heightmapGridZBottom", -1).toDouble());
    ui->chkHeightMapGridShow->setChecked(set.value("heightmapGridShow", false).toBool());

    ui->txtHeightMapInterpolationStepX->setValue(set.value("heightmapInterpolationStepX", 1).toDouble());
    ui->txtHeightMapInterpolationStepY->setValue(set.value("heightmapInterpolationStepY", 1).toDouble());
    ui->cboHeightMapInterpolationType->setCurrentIndex(set.value("heightmapInterpolationType", 0).toInt());
    ui->chkHeightMapInterpolationShow->setChecked(set.value("heightmapInterpolationShow", false).toBool());

    foreach (ColorPicker* pick, m_settings->colors()) {
        pick->setColor(QColor(set.value(pick->objectName().mid(3), "black").toString()));
    }

    updateRecentFilesMenu();

    ui->tblProgram->horizontalHeader()->restoreState(set.value("header", QByteArray()).toByteArray());

    // Apply settings
    applySettings();

    // Restore last commands list
    ui->cboCommand->addItems(set.value("recentCommands", QStringList()).toStringList());
    ui->cboCommand->setCurrentIndex(-1);

    // Load plugins
    loadPlugins();

    // Adjust docks width 
    int w = qMax(ui->dockDevice->widget()->sizeHint().width(), 
        ui->dockModification->widget()->sizeHint().width());
    ui->dockDevice->setMinimumWidth(w);
    ui->dockDevice->setMaximumWidth(w + ui->scrollArea->verticalScrollBar()->width());
    ui->dockModification->setMinimumWidth(w);
    ui->dockModification->setMaximumWidth(w + ui->scrollArea->verticalScrollBar()->width());
    ui->dockUser->setMinimumWidth(w);
    ui->dockUser->setMaximumWidth(w + ui->scrollArea->verticalScrollBar()->width());

        // Buttons
    int b = (w - ui->grpControl->layout()->margin() * 2 - ui->grpControl->layout()->spacing() * 3) / 4 * 0.8;
    int c = b * 0.8;
    setStyleSheet(styleSheet() + QString("\nStyledToolButton[adjustSize='true'] {\n\
	    min-width: %1px;\n\
	    min-height: %1px;\n\
	    qproperty-iconSize: %2px;\n\
        }").arg(b).arg(c));
    ensurePolished();

    foreach (QDockWidget *w, findChildren<QDockWidget*>()) w->setStyleSheet("");

    // Restore docks
        // Signals/slots
    foreach (QDockWidget *w, findChildren<QDockWidget*>())
        connect(w, &QDockWidget::topLevelChanged, this, &frmMain::onDockTopLevelChanged);

        // Panels
    ui->scrollContentsDevice->restoreState(this, set.value("panelsDevice").toStringList());
    ui->scrollContentsModification->restoreState(this, set.value("panelsModification").toStringList());
    ui->scrollContentsUser->restoreState(this, set.value("panelsUser").toStringList());

    QStringList hiddenPanels = set.value("hiddenPanels").toStringList();
    foreach (QString s, hiddenPanels) {
        QGroupBox *b = findChild<QGroupBox*>(s);
        if (b) b->setHidden(true);
    }    

    QStringList collapsedPanels = set.value("collapsedPanels").toStringList();
    foreach (QString s, collapsedPanels) {
        QGroupBox *b = findChild<QGroupBox*>(s);
        if (b) b->setChecked(false);
    }

        // Normal window state
    restoreState(set.value("formMainState").toByteArray());

        // Maximized window state
    show();
    qApp->processEvents();    
    restoreState(set.value("formMainState").toByteArray());

    // Setup coords textboxes
    setupCoordsTextboxes();

    // Settings form geometry
    // m_settings->restoreGeometry(set.value("formSettingsGeometry").toByteArray());
    m_settings->ui->splitMain->restoreState(set.value("settingsSplitMain").toByteArray());

    // Shortcuts
    qRegisterMetaTypeStreamOperators<ShortcutsMap>("ShortcutsMap");
    
    ShortcutsMap m;
    QByteArray ba = set .value("shortcuts").toByteArray();
    QDataStream s(&ba, QIODevice::ReadOnly);
    
    s >> m;
    for (int i = 0; i < m.count(); i++) {
        QAction *a = findChild<QAction*>(m.keys().at(i));
        if (a) a->setShortcuts(m.values().at(i));
    }

    // Menu
    ui->actViewLockWindows->setChecked(set.value("lockWindows").toBool());
    ui->actViewLockPanels->setChecked(set.value("lockPanels").toBool());

    // Load custom settings
    m_settings->loadCustomSettings(set);
    emit settingsLoaded();

    m_settingsLoading = false;
}

void frmMain::saveSettings()
{
    QSettings set(m_settingsFileName, QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    set.setValue("port", m_settings->port());
    set.setValue("baud", m_settings->baud());
    set.setValue("ignoreErrors", m_settings->ignoreErrors());
    set.setValue("autoLine", m_settings->autoLine());
    set.setValue("toolDiameter", m_settings->toolDiameter());
    set.setValue("toolLength", m_settings->toolLength());
    set.setValue("antialiasing", m_settings->antialiasing());
    set.setValue("msaa", m_settings->msaa());
    set.setValue("vsync", m_settings->vsync());
    set.setValue("zBuffer", m_settings->zBuffer());
    set.setValue("simplify", m_settings->simplify());
    set.setValue("simplifyPrecision", m_settings->simplifyPrecision());
    set.setValue("grayscaleSegments", m_settings->grayscaleSegments());
    set.setValue("grayscaleSCode", m_settings->grayscaleSCode());
    set.setValue("drawModeVectors", m_settings->drawModeVectors());

    set.setValue("spindleSpeed", ui->slbSpindle->value());
    set.setValue("lineWidth", m_settings->lineWidth());
    set.setValue("arcLength", m_settings->arcLength());
    set.setValue("arcDegree", m_settings->arcDegree());
    set.setValue("arcDegreeMode", m_settings->arcDegreeMode());
    set.setValue("showProgramCommands", m_settings->showProgramCommands());
    set.setValue("showUICommands", m_settings->showUICommands());
    set.setValue("spindleSpeedMin", m_settings->spindleSpeedMin());
    set.setValue("spindleSpeedMax", m_settings->spindleSpeedMax());
    set.setValue("laserPowerMin", m_settings->laserPowerMin());
    set.setValue("laserPowerMax", m_settings->laserPowerMax());
    set.setValue("moveOnRestore", m_settings->moveOnRestore());
    set.setValue("restoreMode", m_settings->restoreMode());
    set.setValue("rapidSpeed", m_settings->rapidSpeed());
    set.setValue("heightmapProbingFeed", m_settings->heightmapProbingFeed());
    set.setValue("acceleration", m_settings->acceleration());
    set.setValue("toolAngle", m_settings->toolAngle());
    set.setValue("toolType", m_settings->toolType());
    set.setValue("fps", m_settings->fps());
    set.setValue("queryStateTime", m_settings->queryStateTime());
    set.setValue("autoScroll", ui->chkAutoScroll->isChecked());
    set.setValue("header", ui->tblProgram->horizontalHeader()->saveState());
    set.setValue("settingsSplitMain", m_settings->ui->splitMain->saveState());
    set.setValue("formGeometry", this->saveGeometry());
    set.setValue("formSettingsGeometry", m_settings->saveGeometry()); 

    set.setValue("autoCompletion", m_settings->autoCompletion());
    set.setValue("units", m_settings->units());
    set.setValue("storedX", m_storedX);
    set.setValue("storedY", m_storedY);
    set.setValue("storedZ", m_storedZ);
    set.setValue("storedCS", m_storedCS);
    set.setValue("recentFiles", m_recentFiles);
    set.setValue("recentHeightmaps", m_recentHeightmaps);
    set.setValue("lastFolder", m_lastFolder);
    set.setValue("touchCommand", m_settings->touchCommand());
    set.setValue("safePositionCommand", m_settings->safePositionCommand());
    set.setValue("fontSize", m_settings->fontSize());

    set.setValue("feedOverride", ui->slbFeedOverride->isChecked());
    set.setValue("feedOverrideValue", ui->slbFeedOverride->value());
    set.setValue("rapidOverride", ui->slbRapidOverride->isChecked());
    set.setValue("rapidOverrideValue", ui->slbRapidOverride->value());
    set.setValue("spindleOverride", ui->slbSpindleOverride->isChecked());
    set.setValue("spindleOverrideValue", ui->slbSpindleOverride->value());

    foreach (StyledToolButton* button, this->findChildren<StyledToolButton*>(QRegExp("cmdUser\\d"))) {
        int i = button->objectName().right(1).toInt();
        set.setValue(QString("userCommands%1").arg(i), m_settings->userCommands(i));
    }

    set.setValue("jogSteps", ui->cboJogStep->items());
    set.setValue("jogStep", ui->cboJogStep->currentText());
    set.setValue("jogFeeds", ui->cboJogFeed->items());
    set.setValue("jogFeed", ui->cboJogFeed->currentText());

    set.setValue("heightmapBorderX", ui->txtHeightMapBorderX->value());
    set.setValue("heightmapBorderY", ui->txtHeightMapBorderY->value());
    set.setValue("heightmapBorderWidth", ui->txtHeightMapBorderWidth->value());
    set.setValue("heightmapBorderHeight", ui->txtHeightMapBorderHeight->value());
    set.setValue("heightmapBorderShow", ui->chkHeightMapBorderShow->isChecked());

    set.setValue("heightmapGridX", ui->txtHeightMapGridX->value());
    set.setValue("heightmapGridY", ui->txtHeightMapGridY->value());
    set.setValue("heightmapGridZTop", ui->txtHeightMapGridZTop->value());
    set.setValue("heightmapGridZBottom", ui->txtHeightMapGridZBottom->value());
    set.setValue("heightmapGridShow", ui->chkHeightMapGridShow->isChecked());

    set.setValue("heightmapInterpolationStepX", ui->txtHeightMapInterpolationStepX->value());
    set.setValue("heightmapInterpolationStepY", ui->txtHeightMapInterpolationStepY->value());
    set.setValue("heightmapInterpolationType", ui->cboHeightMapInterpolationType->currentIndex());
    set.setValue("heightmapInterpolationShow", ui->chkHeightMapInterpolationShow->isChecked());

    foreach (ColorPicker* pick, m_settings->colors()) {
        set.setValue(pick->objectName().mid(3), pick->color().name());
    }

    QStringList list;

    for (int i = 0; i < ui->cboCommand->count(); i++) list.append(ui->cboCommand->itemText(i));
    set.setValue("recentCommands", list);

    // Docks
    set.setValue("formMainState", saveState());

    // Shortcuts
    ShortcutsMap m;
    QByteArray ba;
    QDataStream s(&ba, QIODevice::WriteOnly);
    QList<QAction*> acts = findChildren<QAction*>(QRegExp("act.*"));

    foreach (QAction *a, acts) m[a->objectName()] = a->shortcuts();
    s << m;
    set.setValue("shortcuts", ba);

    // Panels
    set.setValue("panelsDevice", QVariant::fromValue(ui->scrollContentsDevice->saveState()));
    set.setValue("panelsModification", QVariant::fromValue(ui->scrollContentsModification->saveState()));
    set.setValue("panelsUser", QVariant::fromValue(ui->scrollContentsUser->saveState()));

    QStringList panels;
    QStringList hiddenPanels;
    QStringList collapsedPanels;
    if (ui->scrollContentsDevice->isVisible()) panels << ui->scrollContentsDevice->saveState();
    if (ui->scrollContentsModification->isVisible()) panels << ui->scrollContentsModification->saveState();
    if (ui->scrollContentsUser->isVisible()) panels << ui->scrollContentsUser->saveState();
    foreach (QString s, panels) {
        QGroupBox *b = findChild<QGroupBox*>(s);
        if (b && b->isHidden()) hiddenPanels << s;
        if (b && b->isCheckable() && !b->isChecked()) collapsedPanels << s;
    }    
    set.setValue("hiddenPanels", hiddenPanels);
    set.setValue("collapsedPanels", collapsedPanels);

    // Menu
    set.setValue("lockWindows", ui->actViewLockWindows->isChecked());
    set.setValue("lockPanels", ui->actViewLockPanels->isChecked());

    // Custom settings
    emit settingsAboutToSave();
    m_settings->saveCustomSettings(set);
}

bool frmMain::saveChanges(bool heightMapMode)
{
    if ((!heightMapMode && m_fileChanged)) {
        int res = QMessageBox::warning(this, this->windowTitle(), tr("G-code program file was changed. Save?"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (res == QMessageBox::Cancel) return false;
        else if (res == QMessageBox::Yes) on_actFileSave_triggered();
        m_fileChanged = false;
    }

    if (m_heightMapChanged) {
        int res = QMessageBox::warning(this, this->windowTitle(), tr("Heightmap file was changed. Save?"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (res == QMessageBox::Cancel) return false;
        else if (res == QMessageBox::Yes) {
            m_heightMapMode = true;
            on_actFileSave_triggered();
            m_heightMapMode = heightMapMode;
            updateRecentFilesMenu(); // Restore g-code files recent menu
        }

        m_fileChanged = false;
    }

    return true;
}

void frmMain::updateControlsState() {
    bool portOpened = m_serialPort.isOpen();

    ui->grpState->setEnabled(portOpened);
    ui->grpControl->setEnabled(portOpened);
    ui->widgetUserCommands->setEnabled(portOpened && !m_processingFile);
    ui->widgetSpindle->setEnabled(portOpened);
    ui->widgetJog->setEnabled(portOpened && !m_processingFile);
    ui->cboCommand->setEnabled(portOpened && (!ui->chkKeyboardControl->isChecked()));
    ui->cmdCommandSend->setEnabled(portOpened);

    ui->chkTestMode->setEnabled(portOpened && !m_processingFile);
    ui->cmdHome->setEnabled(!m_processingFile);
    ui->cmdTouch->setEnabled(!m_processingFile);
    ui->cmdZeroXY->setEnabled(!m_processingFile);
    ui->cmdZeroZ->setEnabled(!m_processingFile);
    ui->cmdRestoreOrigin->setEnabled(!m_processingFile);
    ui->cmdSafePosition->setEnabled(!m_processingFile);
    ui->cmdUnlock->setEnabled(!m_processingFile);
    ui->cmdSpindle->setEnabled(!m_processingFile);

    ui->actFileNew->setEnabled(!m_processingFile);
    ui->actFileOpen->setEnabled(!m_processingFile);
    ui->cmdFileOpen->setEnabled(!m_processingFile);
    ui->cmdFileReset->setEnabled(!m_processingFile && m_programModel.rowCount() > 1);
    ui->cmdFileSend->setEnabled(portOpened && !m_processingFile && m_programModel.rowCount() > 1);
    ui->cmdFilePause->setEnabled(m_processingFile && !ui->chkTestMode->isChecked());
    ui->cmdFileAbort->setEnabled(m_processingFile);
    ui->actFileOpen->setEnabled(!m_processingFile);
    ui->mnuRecent->setEnabled(!m_processingFile && ((m_recentFiles.count() > 0 && !m_heightMapMode)
                                                      || (m_recentHeightmaps.count() > 0 && m_heightMapMode)));
    ui->actFileSave->setEnabled(m_programModel.rowCount() > 1);
    ui->actFileSaveAs->setEnabled(m_programModel.rowCount() > 1);

    ui->tblProgram->setEditTriggers(m_processingFile ? QAbstractItemView::NoEditTriggers :
                                                         QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked
                                                         | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);

    if (!portOpened) {
        ui->txtStatus->setText(tr("Not connected"));
        ui->txtStatus->setStyleSheet(QString("background-color: palette(button); color: palette(text);"));
    }

    this->setWindowTitle(m_programFileName.isEmpty() ? qApp->applicationDisplayName()
                                                     : m_programFileName.mid(m_programFileName.lastIndexOf("/") + 1) + " - " + qApp->applicationDisplayName());

    if (!m_processingFile) ui->chkKeyboardControl->setChecked(m_storedKeyboardControl);

#ifdef WINDOWS
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
        if (!m_processingFile && m_taskBarProgress) m_taskBarProgress->hide();
    }
#endif

    style()->unpolish(ui->cmdFileOpen);
    style()->unpolish(ui->cmdFileReset);
    style()->unpolish(ui->cmdFileSend);
    style()->unpolish(ui->cmdFilePause);
    style()->unpolish(ui->cmdFileAbort);
    ui->cmdFileOpen->ensurePolished();
    ui->cmdFileReset->ensurePolished();
    ui->cmdFileSend->ensurePolished();
    ui->cmdFilePause->ensurePolished();
    ui->cmdFileAbort->ensurePolished();

    // Heightmap
    m_heightMapBorderDrawer.setVisible(ui->chkHeightMapBorderShow->isChecked() && m_heightMapMode);
    m_heightMapGridDrawer.setVisible(ui->chkHeightMapGridShow->isChecked() && m_heightMapMode);
    m_heightMapInterpolationDrawer.setVisible(ui->chkHeightMapInterpolationShow->isChecked() && m_heightMapMode);

    ui->grpProgram->setText(m_heightMapMode ? tr("Heightmap") : tr("G-code program"));
    ui->grpProgram->setProperty("overrided", m_heightMapMode);
    style()->unpolish(ui->grpProgram);
    ui->grpProgram->ensurePolished();

    ui->cboJogStep->setEditable(!ui->chkKeyboardControl->isChecked());
    ui->cboJogFeed->setEditable(!ui->chkKeyboardControl->isChecked());
    ui->cboJogStep->setStyleSheet(QString("font-size: %1").arg(m_settings->fontSize()));
    ui->cboJogFeed->setStyleSheet(ui->cboJogStep->styleSheet());

    ui->chkTestMode->setVisible(!m_heightMapMode);

    ui->tblHeightMap->setVisible(m_heightMapMode);
    ui->tblProgram->setVisible(!m_heightMapMode);

    ui->widgetHeightMap->setEnabled(!m_processingFile && m_programModel.rowCount() > 1);
    ui->cmdHeightMapMode->setEnabled(!ui->txtHeightMap->text().isEmpty());

    ui->cmdFileSend->setText(m_heightMapMode ? tr("Probe") : tr("Send"));

    ui->chkHeightMapUse->setEnabled(!m_heightMapMode && !ui->txtHeightMap->text().isEmpty());

    ui->actFileSaveTransformedAs->setVisible(ui->chkHeightMapUse->isChecked());

    ui->cmdFileSend->menu()->actions().first()->setEnabled(!ui->cmdHeightMapMode->isChecked());

    m_selectionDrawer.setVisible(!ui->cmdHeightMapMode->isChecked());    
}

void frmMain::openPort()
{
    if (m_serialPort.open(QIODevice::ReadWrite)) {
        ui->txtStatus->setText(tr("Port opened"));
        ui->txtStatus->setStyleSheet(QString("background-color: palette(button); color: palette(text);"));
        grblReset();
    }
}

void frmMain::sendCommand(QString command, int tableIndex, bool showInConsole, bool queue)
{
    if (!m_serialPort.isOpen() || !m_resetCompleted) return;

    // Commands queue
    if (queue || (bufferLength() + command.length() + 1) > BUFFERLENGTH) {
        CommandQueue cq;

        cq.command = command;
        cq.tableIndex = tableIndex;
        cq.showInConsole = showInConsole;
        cq.queue = queue;

        m_queue.append(cq);
        return;
    }

    // Evaluate scripts in command
    if (tableIndex < 0) command = evaluateCommand(command);

    command = command.toUpper();

    CommandAttributes ca;
    if (showInConsole) {
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
        if (ui->slbSpindle->value() != speed) {
            ui->slbSpindle->setValue(speed);
        }
    }

    // Set M2 & M30 commands sent flag
    if (command.contains(QRegExp("M0*2|M30"))) {
        m_fileEndSent = true;
    }

    // Queue offsets request on G92 command
    if (ca.tableIndex == -1 && command.contains("G92")) {
        m_storedCS = m_storedVars.CS();
        sendCommand("$#", -3, showInConsole, true);
    }

    m_serialPort.write((command + "\r").toLatin1());
}

void frmMain::grblReset()
{
    m_serialPort.write(QByteArray(1, (char)24));

    m_processingFile = false;
    m_transferCompleted = true;
    m_fileCommandIndex = 0;

    m_reseting = true;
    m_homing = false;
    m_resetCompleted = false;
    m_updateSpindleSpeed = true;
    m_lastGrblStatus = -1;
    m_statusReceived = true;

    // Drop all remaining commands in buffer
    m_commands.clear();
    m_queue.clear();

    // Prepare reset response catch
    CommandAttributes ca;
    ca.command = "[CTRL+X]";
    if (m_settings->showUICommands()) ui->txtConsole->appendPlainText(ca.command);
    ca.consoleIndex = m_settings->showUICommands() ? ui->txtConsole->blockCount() - 1 : -1;
    ca.tableIndex = -1;
    ca.length = ca.command.length() + 1;
    m_commands.append(ca);

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
            if (!dataIsReset(data)) continue;
            else {
                m_reseting = false;
                m_timerStateQuery.setInterval(m_settings->queryStateTime());
            }
        }

        // Status response
        if (data[0] == '<') {
            int status = -1;

            m_statusReceived = true;

            // Update machine coordinates
            static QRegExp mpx("MPos:([^,]*),([^,]*),([^,^>^|]*)");
            if (mpx.indexIn(data) != -1) {
                ui->txtMPosX->setValue(mpx.cap(1).toDouble());
                ui->txtMPosY->setValue(mpx.cap(2).toDouble());
                ui->txtMPosZ->setValue(mpx.cap(3).toDouble());

                // Update stored vars
                m_storedVars.setCoords("M", QVector3D(
                    ui->txtMPosX->value(),
                    ui->txtMPosY->value(),
                    ui->txtMPosZ->value()));
            }

            // Status
            static QRegExp stx("<([^,^>^|]*)");
            if (stx.indexIn(data) != -1) {
                status = m_status.indexOf(stx.cap(1));

                // Undetermined status
                if (status == -1) status = 0;

                // Update status
                if (status != m_lastGrblStatus) {
                    ui->txtStatus->setText(m_statusCaptions[status]);
                    ui->txtStatus->setStyleSheet(QString("background-color: %1; color: %2;")
                                                 .arg(m_statusBackColors[status]).arg(m_statusForeColors[status]));
                }

                // Update controls
                ui->cmdRestoreOrigin->setEnabled(status == IDLE);
                ui->cmdSafePosition->setEnabled(status == IDLE);
                ui->cmdZeroXY->setEnabled(status == IDLE);
                ui->cmdZeroZ->setEnabled(status == IDLE);
                ui->chkTestMode->setEnabled(status != RUN && !m_processingFile);
                ui->chkTestMode->setChecked(status == CHECK);
                ui->cmdFilePause->setChecked(status == HOLD0 || status == HOLD1 || status == QUEUE);
                ui->cmdSpindle->setEnabled(!m_processingFile || status == HOLD0);
#ifdef WINDOWS
                if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
                    if (m_taskBarProgress) m_taskBarProgress->setPaused(status == HOLD0 || status == HOLD1 || status == QUEUE);
                }
#endif

                // Update "elapsed time" timer
                if (m_processingFile) {
                    QTime time(0, 0, 0);
                    int elapsed = m_startTime.elapsed();
                    ui->glwVisualizer->setSpendTime(time.addMSecs(elapsed));
                }

                // Test for job complete
                if (m_processingFile && m_transferCompleted &&
                        ((status == IDLE && m_lastGrblStatus == RUN) || status == CHECK)) {

                    // Shadow last segment
                    GcodeViewParse *parser = m_currentDrawer->viewParser();
                    QList<LineSegment*> list = parser->getLineSegmentList();
                    if (m_lastDrawnLineIndex < list.count()) {
                        list[m_lastDrawnLineIndex]->setDrawn(true);
                        m_currentDrawer->update(QList<int>() << m_lastDrawnLineIndex);
                    }

                    // Update state
                    m_processingFile = false;
                    m_fileProcessedCommandIndex = 0;
                    m_lastDrawnLineIndex = 0;
                    m_storedParserStatus.clear();

                    updateControlsState();

                    qApp->beep();

                    m_timerStateQuery.stop();
                    m_timerConnection.stop();

                    QMessageBox::information(this, qApp->applicationDisplayName(), tr("Job done.\nTime elapsed: %1")
                                             .arg(ui->glwVisualizer->spendTime().toString("hh:mm:ss")));

                    m_timerStateQuery.setInterval(m_settings->queryStateTime());
                    m_timerConnection.start();
                    m_timerStateQuery.start();
                }

                // Store status
                if (status != m_lastGrblStatus) m_lastGrblStatus = status;

                // Abort
                static double x = sNan;
                static double y = sNan;
                static double z = sNan;

                if (m_aborting) {
                    switch (status) {
                    case IDLE: // Idle
                        if (!m_processingFile && m_resetCompleted) {
                            m_aborting = false;
                            restoreParserState();
                            restoreOffsets();
                            return;
                        }
                        break;
                    case HOLD0: // Hold
                    case HOLD1:
                    case QUEUE:
                        if (!m_reseting && compareCoordinates(x, y, z)) {
                            x = sNan;
                            y = sNan;
                            z = sNan;
                            grblReset();
                        } else {
                            x = ui->txtMPosX->value();
                            y = ui->txtMPosY->value();
                            z = ui->txtMPosZ->value();
                        }
                        break;
                    }
                }
            }

            // Store work offset
            static QVector3D workOffset;
            static QRegExp wpx("WCO:([^,]*),([^,]*),([^,^>^|]*)");

            if (wpx.indexIn(data) != -1)
            {
                workOffset = QVector3D(wpx.cap(1).toDouble(), wpx.cap(2).toDouble(), wpx.cap(3).toDouble());
            }

            // Update work coordinates
            ui->txtWPosX->setValue(ui->txtMPosX->value() - workOffset.x());
            ui->txtWPosY->setValue(ui->txtMPosY->value() - workOffset.y());
            ui->txtWPosZ->setValue(ui->txtMPosZ->value() - workOffset.z());
            
            // Update stored vars
            m_storedVars.setCoords("W", QVector3D(
                    ui->txtWPosX->value(),
                    ui->txtWPosY->value(),
                    ui->txtWPosZ->value()));

            // Update tool position
            QVector3D toolPosition;
            if (!(status == CHECK && m_fileProcessedCommandIndex < m_currentModel->rowCount() - 1)) {
                toolPosition = QVector3D(toMetric(ui->txtWPosX->value()),
                                         toMetric(ui->txtWPosY->value()),
                                         toMetric(ui->txtWPosZ->value()));
                m_toolDrawer.setToolPosition(m_codeDrawer->getIgnoreZ() ? QVector3D(toolPosition.x(), toolPosition.y(), 0) : toolPosition);
            }


            // Toolpath shadowing
            if (m_processingFile && status != CHECK) {
                GcodeViewParse *parser = m_currentDrawer->viewParser();

                bool toolOntoolpath = false;

                QList<int> drawnLines;
                QList<LineSegment*> list = parser->getLineSegmentList();

                for (int i = m_lastDrawnLineIndex; i < list.count()
                     && list.at(i)->getLineNumber()
                     <= (m_currentModel->data(m_currentModel->index(m_fileProcessedCommandIndex, 4)).toInt() + 1); i++) {
                    if (list.at(i)->contains(toolPosition)) {
                        toolOntoolpath = true;
                        m_lastDrawnLineIndex = i;
                        break;
                    }
                    drawnLines << i;
                }

                if (toolOntoolpath) {
                    foreach (int i, drawnLines) {
                        list.at(i)->setDrawn(true);
                    }
                    if (!drawnLines.isEmpty()) m_currentDrawer->update(drawnLines);
                }
            }

            // Get overridings
            static QRegExp ov("Ov:([^,]*),([^,]*),([^,^>^|]*)");
            if (ov.indexIn(data) != -1)
            {                
                updateOverride(ui->slbFeedOverride, ov.cap(1).toInt(), 0x91);
                updateOverride(ui->slbSpindleOverride, ov.cap(3).toInt(), 0x9a);

                int rapid = ov.cap(2).toInt();
                ui->slbRapidOverride->setCurrentValue(rapid);

                int target = ui->slbRapidOverride->isChecked() ? ui->slbRapidOverride->value() : 100;

                if (rapid != target) switch (target) {
                case 25:
                    m_serialPort.write(QByteArray(1, char(0x97)));
                    break;
                case 50:
                    m_serialPort.write(QByteArray(1, char(0x96)));
                    break;
                case 100:
                    m_serialPort.write(QByteArray(1, char(0x95)));
                    break;
                }

                // Update pins state
                QString pinState;
                static QRegExp pn("Pn:([^|^>]*)");
                if (pn.indexIn(data) != -1) {
                    pinState.append(QString(tr("PS: %1")).arg(pn.cap(1)));
                }

                // Process spindle state
                static QRegExp as("A:([^,^>^|]+)");
                if (as.indexIn(data) != -1) {
                    QString state = as.cap(1);
                    m_spindleCW = state.contains("S");
                    if (state.contains("S") || state.contains("C")) {
                        m_timerToolAnimation.start(25, this);
                        ui->cmdSpindle->setChecked(true);
                    } else {
                        m_timerToolAnimation.stop();
                        ui->cmdSpindle->setChecked(false);
                    }

                    if (!pinState.isEmpty()) pinState.append(" / ");
                    pinState.append(QString(tr("AS: %1")).arg(as.cap(1)));
                } else {
                    m_timerToolAnimation.stop();
                    ui->cmdSpindle->setChecked(false);
                }
                ui->glwVisualizer->setPinState(pinState);
            }

            // Get feed/spindle values
            static QRegExp fs("FS:([^,]*),([^,^|^>]*)");            
            if (fs.indexIn(data) != -1) {
                ui->glwVisualizer->setSpeedState((QString(tr("F/S: %1 / %2")).arg(fs.cap(1)).arg(fs.cap(2))));
            }

        } else if (data.length() > 0) {

            // Processed commands
            if (m_commands.length() > 0 && !dataIsFloating(data)
                    && !(m_commands[0].command != "[CTRL+X]" && dataIsReset(data))) {

                static QString response; // Full response string

                if ((m_commands[0].command != "[CTRL+X]" && dataIsEnd(data))
                        || (m_commands[0].command == "[CTRL+X]" && dataIsReset(data))) {

                    response.append(data);

                    // Take command from buffer
                    CommandAttributes ca = m_commands.takeFirst();
                    QTextBlock tb = ui->txtConsole->document()->findBlockByNumber(ca.consoleIndex);
                    QTextCursor tc(tb);

                    // Store current coordinate system
                    if (ca.command.toUpper() == "$G") {
                        static QRegExp g("G5[4-9]");
                        if (g.indexIn(response) != -1) {
                            m_storedVars.setCS(g.cap(0));
                        }
                    }

                    // Restore absolute/relative coordinate system after jog
                    if (ca.command.toUpper() == "$G" && ca.tableIndex == -2) {
                        if (ui->chkKeyboardControl->isChecked()) m_absoluteCoordinates = response.contains("G90");
                        else if (response.contains("G90")) sendCommand("G90", -1, m_settings->showUICommands());
                    }

                    // Jog
                    if (ca.command.toUpper().contains("$J=") && ca.tableIndex == -2) {
                        jogStep();
                    }

                    // Process parser status
                    if (ca.command.toUpper() == "$G" && ca.tableIndex == -3) {
                        // Update status in visualizer window
                        ui->glwVisualizer->setParserStatus(response.left(response.indexOf("; ")));

                        // Store parser status
                        if (m_processingFile) storeParserState();

                        // Spindle speed
                        QRegExp rx(".*S([\\d\\.]+)");
                        if (rx.indexIn(response) != -1) {
                            double speed = toMetric(rx.cap(1).toDouble()); //RPM in imperial?
                            ui->slbSpindle->setCurrentValue(speed);
                        }

                        m_updateParserStatus = true;
                    }

                    // Offsets
                    if (ca.command == "$#") {
                        storeOffsetsVars(response);

                        // Save G92 offsets
                        if (ca.tableIndex == -3) {
                            QVector3D v = m_storedVars.coords("G92");
                            m_storedX = v.x();
                            m_storedY = v.y();
                            m_storedZ = v.z();
                            ui->cmdRestoreOrigin->setToolTip(QString(tr("Restore origin:\n%1, %2, %3")).arg(m_storedX).arg(m_storedY).arg(m_storedZ));
                        }
                    }

                    // Settings response
                    if (ca.command == "$$" && ca.tableIndex == -2) {
                        static QRegExp gs("\\$(\\d+)\\=([^;]+)\\; ");
                        QMap<int, double> set;
                        int p = 0;
                        while ((p = gs.indexIn(response, p)) != -1) {
                            set[gs.cap(1).toInt()] = gs.cap(2).toDouble();
                            p += gs.matchedLength();
                        }
                        if (set.keys().contains(13)) m_settings->setUnits(set[13]);
                        if (set.keys().contains(110)) m_settings->setRapidSpeed(set[110]);
                        if (set.keys().contains(120)) m_settings->setAcceleration(set[120]);

                        setupCoordsTextboxes();
                    }

                    // Homing response
                    if ((ca.command.toUpper() == "$H" || ca.command.toUpper() == "$T") && m_homing) m_homing = false;

                    // Reset complete response
                    if (ca.command == "[CTRL+X]") {
                        m_resetCompleted = true;
                        m_updateParserStatus = true;

                        // Query grbl settings
                        sendCommand("$$", -2, false);                        
                    }

                    // Clear command buffer on "M2" & "M30" command (old firmwares)
                    if ((ca.command.contains("M2") || ca.command.contains("M30")) && response.contains("ok") && !response.contains("[Pgm End]")) {
                        m_commands.clear();
                        m_queue.clear();
                    }

                    // Update probe coords on user commands
                    if (ca.command.contains("G38.2") && ca.tableIndex < 0) {
                        static QRegExp PRB(".*PRB:([^,]*),([^,]*),([^]^:]*)");
                        if (PRB.indexIn(response) != -1) {
                            m_storedVars.setCoords("PRB", QVector3D(
                                PRB.cap(1).toDouble(),
                                PRB.cap(2).toDouble(),
                                PRB.cap(3).toDouble()
                            ));
                        }
                    }

                    // Process probing on heightmap mode only from table commands
                    if (ca.command.contains("G38.2") && m_heightMapMode && ca.tableIndex > -1) {
                        // Get probe Z coordinate
                        // "[PRB:0.000,0.000,0.000:0];ok"
                        QRegExp rx(".*PRB:([^,]*),([^,]*),([^]^:]*)");
                        double z = qQNaN();
                        if (rx.indexIn(response) != -1) {
                            z = toMetric(rx.cap(3).toDouble());
                        }

                        static double firstZ;
                        if (m_probeIndex == -1) {
                            firstZ = z;
                            z = 0;
                        } else {
                            // Calculate delta Z
                            z -= firstZ;

                            // Calculate table indexes
                            int row = (m_probeIndex / m_heightMapModel.columnCount());
                            int column = m_probeIndex - row * m_heightMapModel.columnCount();
                            if (row % 2) column = m_heightMapModel.columnCount() - 1 - column;

                            // Store Z in table
                            m_heightMapModel.setData(m_heightMapModel.index(row, column), z, Qt::UserRole);
                            ui->tblHeightMap->update(m_heightMapModel.index(m_heightMapModel.rowCount() - 1 - row, column));
                            updateHeightMapInterpolationDrawer();
                        }

                        m_probeIndex++;
                    }

                    // Change state query time on check mode on
                    if (ca.command.contains(QRegExp("$[cC]"))) {
                        m_timerStateQuery.setInterval(response.contains("Enable") ? 1000 : m_settings->queryStateTime());
                    }

                    // Add response to console
                    if (tb.isValid() && tb.text() == ca.command) {

                        bool scrolledDown = ui->txtConsole->verticalScrollBar()->value() 
                            == ui->txtConsole->verticalScrollBar()->maximum();

                        // Update text block numbers
                        int blocksAdded = response.count("; ");

                        if (blocksAdded > 0) for (int i = 0; i < m_commands.count(); i++) {
                            if (m_commands[i].consoleIndex != -1) m_commands[i].consoleIndex += blocksAdded;
                        }

                        tc.beginEditBlock();
                        tc.movePosition(QTextCursor::EndOfBlock);

                        tc.insertText(" < " + QString(response).replace("; ", "\r\n"));
                        tc.endEditBlock();

                        if (scrolledDown) ui->txtConsole->verticalScrollBar()->setValue(
                            ui->txtConsole->verticalScrollBar()->maximum());
                    }

                    // Emit response signal
                    emit responseReceived(ca.command, ca.tableIndex, response);

                    // Check queue
                    if (m_queue.length() > 0) {
                        CommandQueue cq = m_queue.takeFirst();
                       
                        while ((bufferLength() + cq.command.length() + 1) <= BUFFERLENGTH) {
                            if (!cq.command.isEmpty()) sendCommand(cq.command, cq.tableIndex, cq.showInConsole);
                            if (!cq.command.isEmpty() && (m_queue.isEmpty() || cq.queue)) break; 
                                else cq = m_queue.takeFirst();
                        }
                    }

                    // Add response to table, send next program commands
                    if (m_processingFile) {

                        // Only if command from table
                        if (ca.tableIndex > -1) {
                            m_currentModel->setData(m_currentModel->index(ca.tableIndex, 2), GCodeItem::Processed);
                            m_currentModel->setData(m_currentModel->index(ca.tableIndex, 3), response);

                            m_fileProcessedCommandIndex = ca.tableIndex;

                            if (ui->chkAutoScroll->isChecked() && ca.tableIndex != -1) {
                                ui->tblProgram->scrollTo(m_currentModel->index(ca.tableIndex + 1, 0));      // TODO: Update by timer
                                ui->tblProgram->setCurrentIndex(m_currentModel->index(ca.tableIndex, 1));
                            }
                        }

                        // Update taskbar progress
#ifdef WINDOWS
                        if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
                            if (m_taskBarProgress) m_taskBarProgress->setValue(m_fileProcessedCommandIndex);
                        }
#endif                                               
                        // Process error messages
                        static bool holding = false;
                        static QString errors;

                        if (ca.tableIndex > -1 && response.toUpper().contains("ERROR") && !m_settings->ignoreErrors()) {
                            errors.append(QString::number(ca.tableIndex + 1) + ": " + ca.command
                                          + " < " + response + "\n");

                            m_senderErrorBox->setText(tr("Error message(s) received:\n") + errors);

                            if (!holding) {
                                holding = true;         // Hold transmit while messagebox is visible
                                response.clear();

                                m_serialPort.write("!");
                                m_senderErrorBox->checkBox()->setChecked(false);
                                qApp->beep();
                                int result = m_senderErrorBox->exec();

                                holding = false;
                                errors.clear();
                                if (m_senderErrorBox->checkBox()->isChecked()) m_settings->setIgnoreErrors(true);
                                if (result == QMessageBox::Ignore) m_serialPort.write("~"); else on_cmdFileAbort_clicked();
                            }
                        }

                        // Check transfer complete (last row always blank, last command row = rowcount - 2)
                        if (m_fileProcessedCommandIndex == m_currentModel->rowCount() - 2
                                || ca.command.contains(QRegExp("M0*2|M30"))) m_transferCompleted = true;
                        // Send next program commands
                        else if (!m_fileEndSent && (m_fileCommandIndex < m_currentModel->rowCount()) && !holding) sendNextFileCommands();
                    }

                    // Scroll to first line on "M30" command
                    if (ca.command.contains("M30")) ui->tblProgram->setCurrentIndex(m_currentModel->index(0, 1));

                    // Toolpath shadowing on check mode
                    if (m_statusCaptions.indexOf(ui->txtStatus->text()) == CHECK) {
                        GcodeViewParse *parser = m_currentDrawer->viewParser();
                        QList<LineSegment*> list = parser->getLineSegmentList();

                        if (!m_transferCompleted && m_fileProcessedCommandIndex < m_currentModel->rowCount() - 1) {
                            int i;
                            QList<int> drawnLines;

                            for (i = m_lastDrawnLineIndex; i < list.count()
                                 && list.at(i)->getLineNumber()
                                 <= (m_currentModel->data(m_currentModel->index(m_fileProcessedCommandIndex, 4)).toInt()); i++) {
                                drawnLines << i;
                            }

                            if (!drawnLines.isEmpty() && (i < list.count())) {
                                m_lastDrawnLineIndex = i;
                                QVector3D vec = list.at(i)->getEnd();
                                m_toolDrawer.setToolPosition(vec);
                            }

                            foreach (int i, drawnLines) {
                                list.at(i)->setDrawn(true);
                            }
                            if (!drawnLines.isEmpty()) m_currentDrawer->update(drawnLines);
                        } else {
                            foreach (LineSegment* s, list) {
                                if (!qIsNaN(s->getEnd().length())) {
                                    m_toolDrawer.setToolPosition(s->getEnd());
                                    break;
                                }
                            }
                        }
                    }

                    response.clear();
                } else {
                    response.append(data + "; ");
                }

            } else {
                // Unprocessed responses
                // Handle hardware reset
                if (dataIsReset(data)) {
                    m_processingFile = false;
                    m_transferCompleted = true;
                    m_fileCommandIndex = 0;

                    m_reseting = false;
                    m_homing = false;
                    m_lastGrblStatus = -1;

                    m_updateParserStatus = true;
                    m_statusReceived = true;

                    m_commands.clear();
                    m_queue.clear();

                    updateControlsState();
                }
                ui->txtConsole->appendPlainText(data);
            }
        } else {
            // Blank response
        }
    }
}

void frmMain::onSerialPortError(QSerialPort::SerialPortError error)
{
    static QSerialPort::SerialPortError previousError;

    if (error != QSerialPort::NoError && error != previousError) {
        previousError = error;
        ui->txtConsole->appendPlainText(tr("Serial port error ") + QString::number(error) + ": " + m_serialPort.errorString());
        if (m_serialPort.isOpen()) {
            m_serialPort.close();
            updateControlsState();
        }
    }
}

void frmMain::onTimerConnection()
{
    if (!m_serialPort.isOpen()) {
        openPort();
    } else if (!m_homing/* && !m_reseting*/ && !ui->cmdFilePause->isChecked() && m_queue.length() == 0) {
        if (m_updateSpindleSpeed) {
            m_updateSpindleSpeed = false;
            sendCommand(QString("S%1").arg(ui->slbSpindle->value()), -2, m_settings->showUICommands());
        }
        if (m_updateParserStatus) {
            m_updateParserStatus = false;
            sendCommand("$G", -3, false);
        }
    }
}

void frmMain::onTimerStateQuery()
{
    if (m_serialPort.isOpen() && m_resetCompleted && m_statusReceived) {
        m_serialPort.write(QByteArray(1, '?'));
        m_statusReceived = false;
    }

    ui->glwVisualizer->setBufferState(QString(tr("Buffer: %1 / %2 / %3")).arg(bufferLength()).arg(m_commands.length()).arg(m_queue.length()));
}

void frmMain::onVisualizatorRotationChanged()
{
    ui->cmdIsometric->setChecked(false);
}

void frmMain::onScroolBarAction(int action)
{
    Q_UNUSED(action)

    if (m_processingFile) ui->chkAutoScroll->setChecked(false);
}

void frmMain::onJogTimer()
{
    m_jogBlock = false;
}

void frmMain::placeVisualizerButtons()
{
    ui->cmdIsometric->move(ui->glwVisualizer->width() - ui->cmdIsometric->width() - 8, 8);
    ui->cmdTop->move(ui->cmdIsometric->geometry().left() - ui->cmdTop->width() - 8, 8);
    ui->cmdLeft->move(ui->glwVisualizer->width() - ui->cmdLeft->width() - 8, ui->cmdIsometric->geometry().bottom() + 8);
    ui->cmdFront->move(ui->cmdLeft->geometry().left() - ui->cmdFront->width() - 8, ui->cmdIsometric->geometry().bottom() + 8);
    ui->cmdFit->move(ui->glwVisualizer->width() - ui->cmdFit->width() - 8, ui->cmdLeft->geometry().bottom() + 8);
}

void frmMain::showEvent(QShowEvent *se)
{
    Q_UNUSED(se)

    placeVisualizerButtons();

#ifdef WINDOWS
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
        if (m_taskBarButton == NULL) {
            m_taskBarButton = new QWinTaskbarButton(this);
            m_taskBarButton->setWindow(this->windowHandle());
            m_taskBarProgress = m_taskBarButton->progress();
        }
    }
#endif
}

void frmMain::hideEvent(QHideEvent *he)
{
    Q_UNUSED(he)
}

void frmMain::resizeEvent(QResizeEvent *re)
{
    Q_UNUSED(re)

    placeVisualizerButtons();
    resizeTableHeightMapSections();
}

void frmMain::resizeTableHeightMapSections()
{
    if (ui->tblHeightMap->horizontalHeader()->defaultSectionSize()
            * ui->tblHeightMap->horizontalHeader()->count() < ui->glwVisualizer->width())
        ui->tblHeightMap->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); else {
        ui->tblHeightMap->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    }
}

void frmMain::timerEvent(QTimerEvent *te)
{
    if (te->timerId() == m_timerToolAnimation.timerId()) {
        m_toolDrawer.rotate((m_spindleCW ? -40 : 40) * (double)(ui->slbSpindle->currentValue())
                            / (ui->slbSpindle->maximum()));
    } else {
        QMainWindow::timerEvent(te);
    }
}

void frmMain::closeEvent(QCloseEvent *ce)
{
    bool mode = m_heightMapMode;
    m_heightMapMode = false;

    if (!saveChanges(m_heightMapMode)) {
        ce->ignore();
        m_heightMapMode = mode;
        return;
    }

    if (m_processingFile && QMessageBox::warning(this, this->windowTitle(), tr("File sending in progress. Terminate and exit?"),
                                                   QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        ce->ignore();
        m_heightMapMode = mode;
        return;
    }

    if (m_serialPort.isOpen()) m_serialPort.close();
    if (m_queue.length() > 0) {
        m_commands.clear();
        m_queue.clear();
    }

    saveSettings();
}

void frmMain::dragEnterEvent(QDragEnterEvent *dee)
{
    if (m_processingFile) return;

    if (dee->mimeData()->hasFormat("application/widget")) return;

    if (dee->mimeData()->hasFormat("text/plain") && !m_heightMapMode) dee->acceptProposedAction();
    else if (dee->mimeData()->hasFormat("text/uri-list") && dee->mimeData()->urls().count() == 1) {
        QString fileName = dee->mimeData()->urls().at(0).toLocalFile();

        if ((!m_heightMapMode && isGCodeFile(fileName))
        || (m_heightMapMode && isHeightmapFile(fileName)))
            dee->acceptProposedAction();
    }
}

void frmMain::dropEvent(QDropEvent *de)
{    
    QString fileName = de->mimeData()->urls().at(0).toLocalFile();

    if (!m_heightMapMode) {
        if (!saveChanges(false)) return;

        // Load dropped g-code file
        if (!fileName.isEmpty()) {
            addRecentFile(fileName);
            updateRecentFilesMenu();
            loadFile(fileName);
        // Load dropped text
        } else {
            m_programFileName.clear();
            m_fileChanged = true;
            loadFile(de->mimeData()->text().split("\n"));
        }
    } else {
        if (!saveChanges(true)) return;

        // Load dropped heightmap file
        addRecentHeightmap(fileName);
        updateRecentFilesMenu();
        loadHeightMap(fileName);
    }
}

void frmMain::mousePressEvent(QMouseEvent *e)
{
    // qDebug() << childAt(e->pos());
}

QMenu *frmMain::createPopupMenu()
{
    QMenu *menu = QMainWindow::createPopupMenu();

    foreach (QAction *a, menu->actions()) {
        if (a->text().contains("_spacer")) {
            a->setVisible(false);
        }
    } 

    return menu;
}

void frmMain::on_actFileExit_triggered()
{
    close();
}

void frmMain::on_cmdFileOpen_clicked()
{
    if (!m_heightMapMode) {
        if (!saveChanges(false)) return;

        QString fileName  = QFileDialog::getOpenFileName(this, tr("Open"), m_lastFolder,
                                   tr("G-Code files (*.nc *.ncc *.ngc *.tap *.txt);;All files (*.*)"));

        if (!fileName.isEmpty()) m_lastFolder = fileName.left(fileName.lastIndexOf(QRegExp("[/\\\\]+")));

        if (fileName != "") {
            addRecentFile(fileName);
            updateRecentFilesMenu();

            loadFile(fileName);
        }
    } else {
        if (!saveChanges(true)) return;

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), m_lastFolder, tr("Heightmap files (*.map)"));

        if (fileName != "") {
            addRecentHeightmap(fileName);
            updateRecentFilesMenu();
            loadHeightMap(fileName);
        }
    }
}

void frmMain::resetHeightmap()
{
    delete m_heightMapInterpolationDrawer.data();
    m_heightMapInterpolationDrawer.setData(NULL);

    ui->tblHeightMap->setModel(NULL);
    m_heightMapModel.resize(1, 1);

    ui->txtHeightMap->clear();
    m_heightMapFileName.clear();
    m_heightMapChanged = false;
}

void frmMain::loadFile(QList<QString> data)
{
    // Reset tables
    clearTable();
    m_probeModel.clear();
    m_programHeightmapModel.clear();
    m_currentModel = &m_programModel;

    // Reset parsers
    m_viewParser.reset();
    m_probeParser.reset();

    // Reset code drawer
    m_currentDrawer = m_codeDrawer;
    m_codeDrawer->update();
    ui->glwVisualizer->fitDrawable(m_codeDrawer);
    updateProgramEstimatedTime(QList<LineSegment*>());

    // Update interface
    ui->chkHeightMapUse->setChecked(false);
    ui->grpHeightMap->setProperty("overrided", false);
    style()->unpolish(ui->grpHeightMap);
    ui->grpHeightMap->ensurePolished();

    // Reset tableview
    QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();
    ui->tblProgram->setModel(NULL);

    // Prepare parser
    GcodeParser gp;
    gp.setTraverseSpeed(m_settings->rapidSpeed());
    if (m_codeDrawer->getIgnoreZ()) gp.reset(QVector3D(qQNaN(), qQNaN(), 0));

    // Block parser updates on table changes
    m_programLoading = true;

    QString command;
    QString stripped;
    QString trimmed;
    QList<QString> args;
    GCodeItem item;

    // Prepare model
    m_programModel.data().clear();
    m_programModel.data().reserve(data.count());

    QProgressDialog progress(tr("Opening file..."), tr("Abort"), 0, data.count(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setFixedSize(progress.sizeHint());
    if (data.count() > PROGRESSMINLINES) {
        progress.show();
        progress.setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");
    }

    while (!data.isEmpty())
    {
        command = data.takeFirst();

        // Trim command
        trimmed = command.trimmed();

        if (!trimmed.isEmpty()) {
            // Split command
            stripped = GcodePreprocessorUtils::removeComment(command);
            args = GcodePreprocessorUtils::splitCommand(stripped);

            gp.addCommand(args);

            item.command = trimmed;
            item.state = GCodeItem::InQueue;
            item.line = gp.getCommandNumber();
            item.args = args;

            m_programModel.data().append(item);
        }

        if (progress.isVisible() && (data.count() % PROGRESSSTEP == 0)) {
            progress.setValue(progress.maximum() - data.count());
            qApp->processEvents();
            if (progress.wasCanceled()) break;
        }
    }
    progress.close();

    m_programModel.insertRow(m_programModel.rowCount());

    updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_settings->arcPrecision(), m_settings->arcDegreeMode()));

    m_programLoading = false;

    // Set table model
    ui->tblProgram->setModel(&m_programModel);
    ui->tblProgram->horizontalHeader()->restoreState(headerState);

    // Update tableview
    connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));
    ui->tblProgram->selectRow(0);

    //  Update code drawer
    m_codeDrawer->update();
    ui->glwVisualizer->fitDrawable(m_codeDrawer);

    resetHeightmap();
    updateControlsState();
}

void frmMain::loadFile(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, this->windowTitle(), tr("Can't open file:\n") + fileName);
        return;
    }

    // Set filename
    m_programFileName = fileName;

    // Prepare text stream
    QTextStream textStream(&file);

    // Read lines
    QList<QString> data;
    while (!textStream.atEnd()) data.append(textStream.readLine());

    // Load lines
    loadFile(data);
}

QTime frmMain::updateProgramEstimatedTime(QList<LineSegment*> lines)
{
    double time = 0;

    for (int i = 0; i < lines.count(); i++) {
        LineSegment *ls = lines[i];
        double length = (ls->getEnd() - ls->getStart()).length();

        // TODO: Update for rapid override
        if (!qIsNaN(length) && !qIsNaN(ls->getSpeed()) && ls->getSpeed() != 0) time +=
                length / ((ui->slbFeedOverride->isChecked() && !ls->isFastTraverse())
                          ? (ls->getSpeed() * ui->slbFeedOverride->value() / 100) :
                            (ui->slbRapidOverride->isChecked() && ls->isFastTraverse())
                             ? (ls->getSpeed() * ui->slbRapidOverride->value() / 100) : ls->getSpeed());
    }

    time *= 60;

    QTime t;

    t.setHMS(0, 0, 0);
    t = t.addSecs(time);

    ui->glwVisualizer->setSpendTime(QTime(0, 0, 0));
    ui->glwVisualizer->setEstimatedTime(t);

    return t;
}

void frmMain::clearTable()
{
    m_programModel.clear();
    m_programModel.insertRow(0);
}

void frmMain::on_cmdFit_clicked()
{
    ui->glwVisualizer->fitDrawable(m_currentDrawer);
}

void frmMain::on_cmdFileSend_clicked()
{
    if (m_currentModel->rowCount() == 1) return;

    on_cmdFileReset_clicked();

    m_startTime.start();

    m_transferCompleted = false;
    m_processingFile = true;
    m_fileEndSent = false;
    m_storedKeyboardControl = ui->chkKeyboardControl->isChecked();
    ui->chkKeyboardControl->setChecked(false);

    if (!ui->chkTestMode->isChecked()) storeOffsets(); // Allready stored on check
    storeParserState();

#ifdef WINDOWS
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
        if (m_taskBarProgress) {
            m_taskBarProgress->setMaximum(m_currentModel->rowCount() - 2);
            m_taskBarProgress->setValue(0);
            m_taskBarProgress->show();
        }
    }
#endif

    updateControlsState();
    ui->cmdFilePause->setFocus();

    sendNextFileCommands();
}

void frmMain::onActSendFromLineTriggered()
{
    if (m_currentModel->rowCount() == 1) return;

    //Line to start from
    int commandIndex = ui->tblProgram->currentIndex().row();

    // Set parser state
    if (m_settings->autoLine()) {
        GcodeViewParse *parser = m_currentDrawer->viewParser();
        QList<LineSegment*> list = parser->getLineSegmentList();
        QVector<QList<int>> lineIndexes = parser->getLinesIndexes();

        int lineNumber = m_currentModel->data(m_currentModel->index(commandIndex, 4)).toInt();
        LineSegment* firstSegment = list.at(lineIndexes.at(lineNumber).first());
        LineSegment* lastSegment = list.at(lineIndexes.at(lineNumber).last());
        LineSegment* feedSegment = lastSegment;
        int segmentIndex = list.indexOf(feedSegment);
        while (feedSegment->isFastTraverse() && segmentIndex > 0) feedSegment = list.at(--segmentIndex);

        QStringList commands;

        commands.append(QString("M3 S%1").arg(qMax<double>(lastSegment->getSpindleSpeed(), ui->slbSpindle->value())));

        commands.append(QString("G21 G90 G0 X%1 Y%2")
                        .arg(firstSegment->getStart().x())
                        .arg(firstSegment->getStart().y()));
        commands.append(QString("G1 Z%1 F%2")
                        .arg(firstSegment->getStart().z())
                        .arg(feedSegment->getSpeed()));

        commands.append(QString("%1 %2 %3 F%4")
                        .arg(lastSegment->isMetric() ? "G21" : "G20")
                        .arg(lastSegment->isAbsolute() ? "G90" : "G91")
                        .arg(lastSegment->isFastTraverse() ? "G0" : "G1")
                        .arg(lastSegment->isMetric() ? feedSegment->getSpeed() : feedSegment->getSpeed() / 25.4));

        if (lastSegment->isArc()) {
            commands.append(lastSegment->plane() == PointSegment::XY ? "G17"
            : lastSegment->plane() == PointSegment::ZX ? "G18" : "G19");
        }

        QMessageBox box(this);
        box.setIcon(QMessageBox::Information);
        box.setText(tr("Following commands will be sent before selected line:\n") + commands.join('\n'));
        box.setWindowTitle(qApp->applicationDisplayName());
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.addButton(tr("Skip"), QMessageBox::DestructiveRole);

        int res = box.exec();
        if (res == QMessageBox::Cancel) return;
        else if (res == QMessageBox::Ok) {
            foreach (QString command, commands) {
                sendCommand(command, -1, m_settings->showUICommands());
            }
        }
    }

    m_fileCommandIndex = commandIndex;
    m_fileProcessedCommandIndex = commandIndex;
    m_lastDrawnLineIndex = 0;
    m_probeIndex = -1;

    QList<LineSegment*> list = m_viewParser.getLineSegmentList();

    QList<int> indexes;
    for (int i = 0; i < list.count(); i++) {
        list[i]->setDrawn(list.at(i)->getLineNumber() < m_currentModel->data().at(commandIndex).line);
        indexes.append(i);
    }
    m_codeDrawer->update(indexes);

    ui->tblProgram->setUpdatesEnabled(false);

    for (int i = 0; i < m_currentModel->data().count() - 1; i++) {
        m_currentModel->data()[i].state = i < commandIndex ? GCodeItem::Skipped : GCodeItem::InQueue;
        m_currentModel->data()[i].response = QString();
    }
    ui->tblProgram->setUpdatesEnabled(true);
    ui->glwVisualizer->setSpendTime(QTime(0, 0, 0));

    m_startTime.start();

    m_transferCompleted = false;
    m_processingFile = true;
    m_fileEndSent = false;
    m_storedKeyboardControl = ui->chkKeyboardControl->isChecked();
    ui->chkKeyboardControl->setChecked(false);

    if (!ui->chkTestMode->isChecked()) storeOffsets(); // Allready stored on check
    storeParserState();

#ifdef WINDOWS
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
        if (m_taskBarProgress) {
            m_taskBarProgress->setMaximum(m_currentModel->rowCount() - 2);
            m_taskBarProgress->setValue(commandIndex);
            m_taskBarProgress->show();
        }
    }
#endif

    updateControlsState();
    ui->cmdFilePause->setFocus();

    m_fileCommandIndex = commandIndex;
    m_fileProcessedCommandIndex = commandIndex;
    sendNextFileCommands();
}

void frmMain::onSlbSpindleValueUserChanged()
{
    m_updateSpindleSpeed = true;
}

void frmMain::onSlbSpindleValueChanged()
{
    if (!ui->grpSpindle->isChecked() && ui->cmdSpindle->isChecked())
        ui->grpSpindle->setTitle(tr("Spindle") + QString(tr(" (%1)")).arg(ui->slbSpindle->value()));
}

void frmMain::onDockTopLevelChanged(bool topLevel)
{
    static_cast<QWidget*>(sender())->setStyleSheet("");
}

void frmMain::on_cmdFileAbort_clicked()
{
    m_aborting = true;
    if (!ui->chkTestMode->isChecked()) {
        m_serialPort.write("!");
    } else {
        grblReset();
    }
}

void frmMain::storeParserState()
{    
    m_storedParserStatus = ui->glwVisualizer->parserStatus().remove(
                QRegExp("GC:|\\[|\\]|G[01234]\\s|M[0345]+\\s|\\sF[\\d\\.]+|\\sS[\\d\\.]+"));
}

void frmMain::restoreParserState()
{
    if (!m_storedParserStatus.isEmpty()) sendCommand(m_storedParserStatus, -1, m_settings->showUICommands());
}

void frmMain::storeOffsets()
{
//    sendCommand("$#", -2, m_settings->showUICommands());
}

void frmMain::restoreOffsets()
{
    // Still have pre-reset working position
    sendCommand(QString("%4G53G90X%1Y%2Z%3").arg(ui->txtMPosX->value())
                                       .arg(ui->txtMPosY->value())
                                       .arg(ui->txtMPosZ->value())
                                       .arg(m_settings->units() ? "G20" : "G21"), 
                                       -2, m_settings->showUICommands());

    sendCommand(QString("%4G92X%1Y%2Z%3").arg(ui->txtWPosX->value())
                                       .arg(ui->txtWPosY->value())
                                       .arg(ui->txtWPosZ->value())
                                       .arg(m_settings->units() ? "G20" : "G21"),
                                       -2, m_settings->showUICommands());
}

void frmMain::storeOffsetsVars(QString response)
{
    static QRegExp gx("\\[(G5[4-9]|G28|G30|G92|PRB):([\\d\\.\\-]+),([\\d\\.\\-]+),([\\d\\.\\-]+)");
    static QRegExp tx("\\[(TLO):([\\d\\.\\-]+)");

    int p = 0;
    while ((p = gx.indexIn(response, p)) != -1) {
        m_storedVars.setCoords(gx.cap(1), QVector3D(
            gx.cap(2).toDouble(),
            gx.cap(3).toDouble(),
            gx.cap(4).toDouble()
        ));
            
        p += gx.matchedLength();
    }

    if (tx.indexIn(response) != -1) {
        m_storedVars.setCoords(tx.cap(1), QVector3D(
            0,
            0,
            tx.cap(2).toDouble()
        ));
    }
}

void frmMain::sendNextFileCommands() {
    if (m_queue.length() > 0) return;

    QString command = m_currentModel->data(m_currentModel->index(m_fileCommandIndex, 1)).toString();

    while ((bufferLength() + command.length() + 1) <= BUFFERLENGTH
           && m_fileCommandIndex < m_currentModel->rowCount() - 1
           && !(!m_commands.isEmpty() && m_commands.last().command.contains(QRegExp("M0*2|M30")))) {
        m_currentModel->setData(m_currentModel->index(m_fileCommandIndex, 2), GCodeItem::Sent);
        sendCommand(command, m_fileCommandIndex, m_settings->showProgramCommands());
        m_fileCommandIndex++;
        command = m_currentModel->data(m_currentModel->index(m_fileCommandIndex, 1)).toString();
    }
}

void frmMain::onTableCellChanged(QModelIndex i1, QModelIndex i2)
{
    Q_UNUSED(i2)

    GCodeTableModel *model = (GCodeTableModel*)sender();

    if (i1.column() != 1) return;
    // Inserting new line at end
    if (i1.row() == (model->rowCount() - 1) && model->data(model->index(i1.row(), 1)).toString() != "") {
        model->setData(model->index(model->rowCount() - 1, 2), GCodeItem::InQueue);
        model->insertRow(model->rowCount());
        if (!m_programLoading) ui->tblProgram->setCurrentIndex(model->index(i1.row() + 1, 1));
    }

    if (!m_programLoading) {

        // Clear cached args
        model->setData(model->index(i1.row(), 5), QVariant());

        // Drop heightmap cache
        if (m_currentModel == &m_programModel) m_programHeightmapModel.clear();

        // Update visualizer
        updateParser();

        // Hightlight w/o current cell changed event (double hightlight on current cell changed)
        QList<LineSegment*> list = m_viewParser.getLineSegmentList();
        for (int i = 0; i < list.count() && list[i]->getLineNumber() <= m_currentModel->data(m_currentModel->index(i1.row(), 4)).toInt(); i++) {
            list[i]->setIsHightlight(true);
        }
    }
}

void frmMain::onTableCurrentChanged(QModelIndex idx1, QModelIndex idx2)
{
    // Update toolpath hightlighting
    if (idx1.row() > m_currentModel->rowCount() - 2) idx1 = m_currentModel->index(m_currentModel->rowCount() - 2, 0);
    if (idx2.row() > m_currentModel->rowCount() - 2) idx2 = m_currentModel->index(m_currentModel->rowCount() - 2, 0);

    GcodeViewParse *parser = m_currentDrawer->viewParser();
    QList<LineSegment*> list = parser->getLineSegmentList();
    QVector<QList<int>> lineIndexes = parser->getLinesIndexes();

    // Update linesegments on cell changed
    if (!m_currentDrawer->geometryUpdated()) {
        for (int i = 0; i < list.count(); i++) {
            list.at(i)->setIsHightlight(list.at(i)->getLineNumber() <= m_currentModel->data(m_currentModel->index(idx1.row(), 4)).toInt());
        }
    // Update vertices on current cell changed
    } else {

        int lineFirst = m_currentModel->data(m_currentModel->index(idx1.row(), 4)).toInt();
        int lineLast = m_currentModel->data(m_currentModel->index(idx2.row(), 4)).toInt();
        if (lineLast < lineFirst) qSwap(lineLast, lineFirst);

        QList<int> indexes;
        for (int i = lineFirst + 1; i <= lineLast; i++) {
            foreach (int l, lineIndexes.at(i)) {
                list.at(l)->setIsHightlight(idx1.row() > idx2.row());
                indexes.append(l);
            }
        }

        m_selectionDrawer.setEndPosition(indexes.isEmpty() ? QVector3D(sNan, sNan, sNan) :
            (m_codeDrawer->getIgnoreZ() ? QVector3D(list.at(indexes.last())->getEnd().x(), list.at(indexes.last())->getEnd().y(), 0)
                                        : list.at(indexes.last())->getEnd()));
        m_selectionDrawer.update();

        if (!indexes.isEmpty()) m_currentDrawer->update(indexes);
    }

    // Update selection marker
    int line = m_currentModel->data(m_currentModel->index(idx1.row(), 4)).toInt();
    if (line > 0 && line < lineIndexes.count() && !lineIndexes.at(line).isEmpty()) {
        QVector3D pos = list.at(lineIndexes.at(line).last())->getEnd();
        m_selectionDrawer.setEndPosition(m_codeDrawer->getIgnoreZ() ? QVector3D(pos.x(), pos.y(), 0) : pos);
    } else {
        m_selectionDrawer.setEndPosition(QVector3D(sNan, sNan, sNan));
    }
    m_selectionDrawer.update();
}

void frmMain::onTableInsertLine()
{
    if (ui->tblProgram->selectionModel()->selectedRows().count() == 0 || m_processingFile) return;

    int row = ui->tblProgram->selectionModel()->selectedRows()[0].row();

    m_currentModel->insertRow(row);
    m_currentModel->setData(m_currentModel->index(row, 2), GCodeItem::InQueue);

    updateParser();
    m_cellChanged = true;
    ui->tblProgram->selectRow(row);
}

void frmMain::onTableDeleteLines()
{
    if (ui->tblProgram->selectionModel()->selectedRows().count() == 0 || m_processingFile ||
            QMessageBox::warning(this, this->windowTitle(), tr("Delete lines?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return;

    QModelIndex firstRow = ui->tblProgram->selectionModel()->selectedRows()[0];
    int rowsCount = ui->tblProgram->selectionModel()->selectedRows().count();
    if (ui->tblProgram->selectionModel()->selectedRows().last().row() == m_currentModel->rowCount() - 1) rowsCount--;

    if (firstRow.row() != m_currentModel->rowCount() - 1) {
        m_currentModel->removeRows(firstRow.row(), rowsCount);
    } else return;

    // Drop heightmap cache
    if (m_currentModel == &m_programModel) m_programHeightmapModel.clear();

    updateParser();
    m_cellChanged = true;
    ui->tblProgram->selectRow(firstRow.row());
}

bool frmMain::actionLessThan(const QAction *a1, const QAction *a2)
{
    return a1->objectName() < a2->objectName();
}

bool frmMain::actionTextLessThan(const QAction *a1, const QAction *a2)
{
    return a1->text() < a2->text();
}

void frmMain::on_actServiceSettings_triggered()
{
    QList<QAction*> acts = findChildren<QAction*>(QRegExp("act.*"));
    QTableWidget *table = m_settings->ui->tblShortcuts;

    table->clear();
    table->setColumnCount(3);
    table->setRowCount(acts.count());
    table->setHorizontalHeaderLabels(QStringList() << tr("Command") << tr("Text") << tr("Shortcuts"));

    table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->verticalHeader()->setFixedWidth(table->verticalHeader()->sizeHint().width() + 11);

    qSort(acts.begin(), acts.end(), frmMain::actionLessThan);
    for (int i = 0; i < acts.count(); i++) {
        table->setItem(i, 0, new QTableWidgetItem(acts.at(i)->objectName()));
        table->setItem(i, 1, new QTableWidgetItem(acts.at(i)->text().remove("&")));
        table->setItem(i, 2, new QTableWidgetItem(acts.at(i)->shortcut().toString()));

        table->item(i, 0)->setFlags(Qt::ItemIsEnabled);
        table->item(i, 1)->setFlags(Qt::ItemIsEnabled);
        table->item(i, 2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    }

    table->resizeColumnsToContents();
    table->setMinimumHeight(table->rowHeight(0) * 10
        + table->horizontalHeader()->height() + table->frameWidth() * 2);
    table->horizontalHeader()->setMinimumSectionSize(table->horizontalHeader()->sectionSize(2));
    table->horizontalHeader()->setStretchLastSection(true);

    if (m_settings->exec()) {
        if (m_settings->port() != "" && (m_settings->port() != m_serialPort.portName() ||
                                           m_settings->baud() != m_serialPort.baudRate())) {
            if (m_serialPort.isOpen()) m_serialPort.close();
            m_serialPort.setPortName(m_settings->port());
            m_serialPort.setBaudRate(m_settings->baud());
            openPort();
        }

        updateControlsState();
        applySettings();

        // Update shortcuts
        for (int i = 0; i < acts.count(); i++) {
            acts[i]->setShortcut(QKeySequence(table->item(i, 2)->data(Qt::DisplayRole).toString()));
        }

        emit settingsChanged();

    } else {
        m_settings->undo();
    }
}

bool buttonLessThan(StyledToolButton *b1, StyledToolButton *b2)
{
    return b1->objectName().right(1).toDouble() < b2->objectName().right(1).toDouble();
}

void frmMain::applySettings() {
    m_originDrawer->setLineWidth(m_settings->lineWidth());
    m_toolDrawer.setToolDiameter(m_settings->toolDiameter());
    m_toolDrawer.setToolLength(m_settings->toolLength());
    m_toolDrawer.setLineWidth(m_settings->lineWidth());
    m_codeDrawer->setLineWidth(m_settings->lineWidth());
    m_heightMapBorderDrawer.setLineWidth(m_settings->lineWidth());
    m_heightMapGridDrawer.setLineWidth(0.1);
    m_heightMapInterpolationDrawer.setLineWidth(m_settings->lineWidth());
    ui->glwVisualizer->setLineWidth(m_settings->lineWidth());
    m_timerStateQuery.setInterval(m_settings->queryStateTime());

    m_toolDrawer.setToolAngle(m_settings->toolType() == 0 ? 180 : m_settings->toolAngle());
    m_toolDrawer.setColor(m_settings->colors("Tool"));
    m_toolDrawer.update();

    ui->glwVisualizer->setAntialiasing(m_settings->antialiasing());
    ui->glwVisualizer->setMsaa(m_settings->msaa());
    ui->glwVisualizer->setZBuffer(m_settings->zBuffer());
    ui->glwVisualizer->setVsync(m_settings->vsync());
    ui->glwVisualizer->setFps(m_settings->fps());
    ui->glwVisualizer->setColorBackground(m_settings->colors("VisualizerBackground"));
    ui->glwVisualizer->setColorText(m_settings->colors("VisualizerText"));

    ui->slbSpindle->setMinimum(m_settings->spindleSpeedMin());
    ui->slbSpindle->setMaximum(m_settings->spindleSpeedMax());

    ui->cboCommand->setAutoCompletion(m_settings->autoCompletion());

    m_codeDrawer->setSimplify(m_settings->simplify());
    m_codeDrawer->setSimplifyPrecision(m_settings->simplifyPrecision());
    m_codeDrawer->setColorNormal(m_settings->colors("ToolpathNormal"));
    m_codeDrawer->setColorDrawn(m_settings->colors("ToolpathDrawn"));
    m_codeDrawer->setColorHighlight(m_settings->colors("ToolpathHighlight"));
    m_codeDrawer->setColorZMovement(m_settings->colors("ToolpathZMovement"));
    m_codeDrawer->setColorStart(m_settings->colors("ToolpathStart"));
    m_codeDrawer->setColorEnd(m_settings->colors("ToolpathEnd"));
    m_codeDrawer->setIgnoreZ(m_settings->grayscaleSegments() || !m_settings->drawModeVectors());
    m_codeDrawer->setGrayscaleSegments(m_settings->grayscaleSegments());
    m_codeDrawer->setGrayscaleCode(m_settings->grayscaleSCode() ? GcodeDrawer::S : GcodeDrawer::Z);
    m_codeDrawer->setDrawMode(m_settings->drawModeVectors() ? GcodeDrawer::Vectors : GcodeDrawer::Raster);
    m_codeDrawer->setGrayscaleMin(m_settings->laserPowerMin());
    m_codeDrawer->setGrayscaleMax(m_settings->laserPowerMax());
    m_codeDrawer->update();    

    m_selectionDrawer.setColor(m_settings->colors("ToolpathHighlight"));

    // Adapt visualizer buttons colors
    const int LIGHTBOUND = 127;
    const int NORMALSHIFT = 40;
    const int HIGHLIGHTSHIFT = 80;

    QColor base = m_settings->colors("VisualizerBackground");
    bool light = base.value() > LIGHTBOUND;
    QColor normal, highlight;

    normal.setHsv(base.hue(), base.saturation(), base.value() + (light ? -NORMALSHIFT : NORMALSHIFT));
    highlight.setHsv(base.hue(), base.saturation(), base.value() + (light ? -HIGHLIGHTSHIFT : HIGHLIGHTSHIFT));

    ui->glwVisualizer->setStyleSheet(QString("QToolButton {border: 1px solid %1; \
                background-color: %3} QToolButton:hover {border: 1px solid %2;}")
                .arg(normal.name()).arg(highlight.name())
                .arg(base.name()));

    ui->cmdFit->setIcon(QIcon(":/images/fit_1.png"));
    ui->cmdIsometric->setIcon(QIcon(":/images/cube.png"));
    ui->cmdFront->setIcon(QIcon(":/images/cubeFront.png"));
    ui->cmdLeft->setIcon(QIcon(":/images/cubeLeft.png"));
    ui->cmdTop->setIcon(QIcon(":/images/cubeTop.png"));

    if (!light) {
        Util::invertButtonIconColors(ui->cmdFit);
        Util::invertButtonIconColors(ui->cmdIsometric);
        Util::invertButtonIconColors(ui->cmdFront);
        Util::invertButtonIconColors(ui->cmdLeft);
        Util::invertButtonIconColors(ui->cmdTop);
    }

    int h = ui->cmdFileOpen->sizeHint().height();
    QSize s(h, h);
    ui->cboCommand->setMinimumHeight(h);
    ui->cmdClearConsole->setFixedSize(s);
    ui->cmdCommandSend->setFixedSize(s);

    foreach (StyledToolButton* button, this->findChildren<StyledToolButton*>(QRegExp("cmdUser\\d"))) {
        button->setToolTip(m_settings->userCommands(button->objectName().right(1).toInt()));
        button->setEnabled(!button->toolTip().isEmpty());
    }
}

void frmMain::updateParser()
{
    GcodeViewParse *parser = m_currentDrawer->viewParser();

    GcodeParser gp;
    gp.setTraverseSpeed(m_settings->rapidSpeed());
    if (m_codeDrawer->getIgnoreZ()) gp.reset(QVector3D(qQNaN(), qQNaN(), 0));

    ui->tblProgram->setUpdatesEnabled(false);

    QString stripped;
    QList<QString> args;

    QProgressDialog progress(tr("Updating..."), tr("Abort"), 0, m_currentModel->rowCount() - 2, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setFixedSize(progress.sizeHint());

    if (m_currentModel->rowCount() > PROGRESSMINLINES) {
        progress.show();
        progress.setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");
    }

    for (int i = 0; i < m_currentModel->rowCount() - 1; i++) {
        // Get stored args
        args = m_currentModel->data().at(i).args;

        // Store args if none
        if (args.isEmpty()) {
            stripped = GcodePreprocessorUtils::removeComment(m_currentModel->data().at(i).command);
            args = GcodePreprocessorUtils::splitCommand(stripped);
            m_currentModel->data()[i].args = args;
        }

        // Add command to parser
        gp.addCommand(args);

        // Update table model
        m_currentModel->data()[i].state = GCodeItem::InQueue;
        m_currentModel->data()[i].response = QString();
        m_currentModel->data()[i].line = gp.getCommandNumber();

        if (progress.isVisible() && (i % PROGRESSSTEP == 0)) {
            progress.setValue(i);
            qApp->processEvents();
            if (progress.wasCanceled()) break;
        }
    }
    progress.close();

    ui->tblProgram->setUpdatesEnabled(true);

    parser->reset();

    updateProgramEstimatedTime(parser->getLinesFromParser(&gp, m_settings->arcPrecision(), m_settings->arcDegreeMode()));
    m_currentDrawer->update();
    ui->glwVisualizer->updateExtremes(m_currentDrawer);
    updateControlsState();

    if (m_currentModel == &m_programModel) m_fileChanged = true;
}

void frmMain::on_cmdCommandSend_clicked()
{
    QString command = ui->cboCommand->currentText();
    if (command.isEmpty()) return;

    ui->cboCommand->storeText();
    ui->cboCommand->setCurrentText("");
    sendCommand(command, -1);
}

void frmMain::on_actFileOpen_triggered()
{
    on_cmdFileOpen_clicked();
}

void frmMain::on_cmdHome_clicked()
{
    m_homing = true;
    m_updateSpindleSpeed = true;
    sendCommand("$H", -1, m_settings->showUICommands());
}

void frmMain::on_cmdTouch_clicked()
{
    QStringList list = m_settings->touchCommand().split(";");

    foreach (QString cmd, list) {
        sendCommand(cmd.trimmed(), -1, m_settings->showUICommands(), list.indexOf(cmd));
    }
}

void frmMain::on_cmdZeroXY_clicked()
{
    sendCommand("G92X0Y0", -1, m_settings->showUICommands());
}

void frmMain::on_cmdZeroZ_clicked()
{
    sendCommand("G92Z0", -1, m_settings->showUICommands());
}

void frmMain::on_cmdRestoreOrigin_clicked()
{
    // Restore offset
    sendCommand(QString("%4G53G90G0X%1Y%2Z%3").arg(ui->txtMPosX->value())
                                            .arg(ui->txtMPosY->value())
                                            .arg(ui->txtMPosZ->value())
                                            .arg(m_settings->units() ? "G20" : "G21"), 
                                            -2, m_settings->showUICommands());

    m_storedVars.setCS(m_storedCS);
    sendCommand("$#", -2, m_settings->showUICommands());
    sendCommand("{vars.CS}", -2, m_settings->showUICommands(), true);
    sendCommand(QString("%4G92X{%1 - vars.x}Y{%2 - vars.y}Z{%3 - vars.z}")
                                        .arg(ui->txtMPosX->value() - m_storedX)
                                        .arg(ui->txtMPosY->value() - m_storedY)
                                        .arg(ui->txtMPosZ->value() - m_storedZ)
                                        .arg(m_settings->units() ? "G20" : "G21"), 
                                        -2, m_settings->showUICommands(), true);

    // Move tool
    if (m_settings->moveOnRestore()) switch (m_settings->restoreMode()) {
    case 0:
        sendCommand("G0X0Y0", -2, m_settings->showUICommands(), true);
        break;
    case 1:
    
        sendCommand("G0X0Y0Z0", -2, m_settings->showUICommands(), true);
        break;
    }
}

void frmMain::on_cmdReset_clicked()
{
    grblReset();
}

void frmMain::on_cmdUnlock_clicked()
{
    m_updateSpindleSpeed = true;
    sendCommand("$X", -1, m_settings->showUICommands());
}

void frmMain::on_cmdSafePosition_clicked()
{
    QStringList list = m_settings->safePositionCommand().split(";");

    foreach (QString cmd, list) {
        sendCommand(cmd.trimmed(), -1, m_settings->showUICommands(), list.indexOf(cmd));
    }
}

void frmMain::on_cmdSpindle_toggled(bool checked)
{
    ui->grpSpindle->setProperty("overrided", checked);
    style()->unpolish(ui->grpSpindle);
    ui->grpSpindle->ensurePolished();

    if (checked) {
        if (!ui->grpSpindle->isChecked()) ui->grpSpindle->setTitle(tr("Spindle") + QString(tr(" (%1)")).arg(ui->slbSpindle->value()));
    } else {
        ui->grpSpindle->setTitle(tr("Spindle"));
    }
}

void frmMain::on_cmdSpindle_clicked(bool checked)
{
    if (ui->cmdFilePause->isChecked()) {
        m_serialPort.write(QByteArray(1, char(0x9e)));
    } else {
        sendCommand(checked ? QString("M3 S%1").arg(ui->slbSpindle->value()) : "M5", -1, m_settings->showUICommands());
    }
}

void frmMain::on_chkTestMode_clicked(bool checked)
{
    if (checked) {
        storeOffsets();
        storeParserState();
        sendCommand("$C", -1, m_settings->showUICommands());
    } else {
        m_aborting = true;
        grblReset();
    };
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
    m_probeIndex = -1;

    if (!m_heightMapMode) {
        QList<LineSegment*> list = m_viewParser.getLineSegmentList();

        QList<int> indexes;
        for (int i = 0; i < list.count(); i++) {
            list[i]->setDrawn(false);
            indexes.append(i);
        }
        m_codeDrawer->update(indexes);

        ui->tblProgram->setUpdatesEnabled(false);

        for (int i = 0; i < m_currentModel->data().count() - 1; i++) {
            m_currentModel->data()[i].state = GCodeItem::InQueue;
            m_currentModel->data()[i].response = QString();
        }
        ui->tblProgram->setUpdatesEnabled(true);

        ui->tblProgram->scrollTo(m_currentModel->index(0, 0));
        ui->tblProgram->clearSelection();
        ui->tblProgram->selectRow(0);

        ui->glwVisualizer->setSpendTime(QTime(0, 0, 0));
    } else {
        ui->txtHeightMapGridX->setEnabled(true);
        ui->txtHeightMapGridY->setEnabled(true);
        ui->txtHeightMapGridZBottom->setEnabled(true);
        ui->txtHeightMapGridZTop->setEnabled(true);

        delete m_heightMapInterpolationDrawer.data();
        m_heightMapInterpolationDrawer.setData(NULL);

        m_heightMapModel.clear();
        updateHeightMapGrid();
    }
}

void frmMain::on_actFileNew_triggered()
{
    if (!saveChanges(m_heightMapMode)) return;

    if (!m_heightMapMode) {
        // Reset tables
        clearTable();
        m_probeModel.clear();
        m_programHeightmapModel.clear();
        m_currentModel = &m_programModel;

        // Reset parsers
        m_viewParser.reset();
        m_probeParser.reset();

        // Reset code drawer
        m_codeDrawer->update();
        m_currentDrawer = m_codeDrawer;
        ui->glwVisualizer->fitDrawable();
        updateProgramEstimatedTime(QList<LineSegment*>());

        m_programFileName = "";
        ui->chkHeightMapUse->setChecked(false);
        ui->grpHeightMap->setProperty("overrided", false);
        style()->unpolish(ui->grpHeightMap);
        ui->grpHeightMap->ensurePolished();

        // Reset tableview
        QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();
        ui->tblProgram->setModel(NULL);

        // Set table model
        ui->tblProgram->setModel(&m_programModel);
        ui->tblProgram->horizontalHeader()->restoreState(headerState);

        // Update tableview
        connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));
        ui->tblProgram->selectRow(0);

        // Clear selection marker
        m_selectionDrawer.setEndPosition(QVector3D(sNan, sNan, sNan));
        m_selectionDrawer.update();

        resetHeightmap();
    } else {
        m_heightMapModel.clear();
        on_cmdFileReset_clicked();
        ui->txtHeightMap->setText(tr("Untitled"));
        m_heightMapFileName.clear();

        updateHeightMapBorderDrawer();
        updateHeightMapGrid();

        m_heightMapChanged = false;
    }

    updateControlsState();
}

void frmMain::on_cmdClearConsole_clicked()
{
    ui->txtConsole->clear();
}

bool frmMain::saveProgramToFile(QString fileName, GCodeTableModel *model)
{
    QFile file(fileName);
    QDir dir;

    if (file.exists()) dir.remove(file.fileName());
    if (!file.open(QIODevice::WriteOnly)) return false;

    QTextStream textStream(&file);

    for (int i = 0; i < model->rowCount() - 1; i++) {
        textStream << model->data(model->index(i, 1)).toString() << "\r\n";
    }

    file.close();

    return true;
}

void frmMain::on_actFileSaveTransformedAs_triggered()
{
    QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), m_lastFolder, tr("G-Code files (*.nc *.ncc *.ngc *.tap *.txt)")));

    if (!fileName.isEmpty()) {
        saveProgramToFile(fileName, &m_programHeightmapModel);
    }
}

void frmMain::on_actFileSaveAs_triggered()
{
    if (!m_heightMapMode) {
        QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), m_lastFolder, tr("G-Code files (*.nc *.ncc *.ngc *.tap *.txt)")));

        if (!fileName.isEmpty()) if (saveProgramToFile(fileName, &m_programModel)) {
            m_programFileName = fileName;
            m_fileChanged = false;

            addRecentFile(fileName);
            updateRecentFilesMenu();

            updateControlsState();
        }
    } else {
        QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), m_lastFolder, tr("Heightmap files (*.map)")));

        if (!fileName.isEmpty()) if (saveHeightMap(fileName)) {
            ui->txtHeightMap->setText(fileName.mid(fileName.lastIndexOf("/") + 1));
            m_heightMapFileName = fileName;
            m_heightMapChanged = false;

            addRecentHeightmap(fileName);
            updateRecentFilesMenu();

            updateControlsState();
        }
    }
}

void frmMain::on_actFileSave_triggered()
{
    if (!m_heightMapMode) {
        // G-code saving
        if (m_programFileName.isEmpty()) on_actFileSaveAs_triggered(); else {
            saveProgramToFile(m_programFileName, &m_programModel);
            m_fileChanged = false;
        }
    } else {
        // Height map saving
        if (m_heightMapFileName.isEmpty()) on_actFileSaveAs_triggered(); else saveHeightMap(m_heightMapFileName);
    }
}

void frmMain::on_cmdTop_clicked()
{
    ui->glwVisualizer->setTopView();
}

void frmMain::on_cmdFront_clicked()
{
    ui->glwVisualizer->setFrontView();
}

void frmMain::on_cmdLeft_clicked()
{
    ui->glwVisualizer->setLeftView();
}

void frmMain::on_cmdIsometric_clicked()
{
    ui->glwVisualizer->setIsometricView();
}

void frmMain::on_actAbout_triggered()
{
    m_frmAbout.exec();
}

bool frmMain::dataIsEnd(QString data) {
    QStringList ends;

    ends << "ok";
    ends << "error";

    foreach (QString str, ends) {
        if (data.contains(str)) return true;
    }

    return false;
}

bool frmMain::dataIsFloating(QString data) {
    QStringList ends;

    ends << "Reset to continue";
    ends << "'$H'|'$X' to unlock";
    ends << "ALARM: Soft limit";
    ends << "ALARM: Hard limit";
    ends << "Check Door";

    foreach (QString str, ends) {
        if (data.contains(str)) return true;
    }

    return false;
}

bool frmMain::dataIsReset(QString data) {
    return QRegExp("^GRBL|GCARVIN\\s\\d\\.\\d.").indexIn(data.toUpper()) != -1;
}

void frmMain::on_grpOverriding_toggled(bool checked)
{
    if (checked) {
        ui->grpOverriding->setTitle(tr("Overriding"));
    } else if (ui->slbFeedOverride->isChecked() | ui->slbRapidOverride->isChecked() | ui->slbSpindleOverride->isChecked()) {
        ui->grpOverriding->setTitle(tr("Overriding") + QString(tr(" (%1/%2/%3)"))
                                    .arg(ui->slbFeedOverride->isChecked() ? QString::number(ui->slbFeedOverride->value()) : "-")
                                    .arg(ui->slbRapidOverride->isChecked() ? QString::number(ui->slbRapidOverride->value()) : "-")
                                    .arg(ui->slbSpindleOverride->isChecked() ? QString::number(ui->slbSpindleOverride->value()) : "-"));
    }
    updateLayouts();

    ui->widgetFeed->setVisible(checked);
}

void frmMain::on_grpSpindle_toggled(bool checked)
{
    if (checked) {
        ui->grpSpindle->setTitle(tr("Spindle"));
    } else if (ui->cmdSpindle->isChecked()) {
//        ui->grpSpindle->setTitle(tr("Spindle") + QString(tr(" (%1)")).arg(ui->txtSpindleSpeed->text()));
        ui->grpSpindle->setTitle(tr("Spindle") + QString(tr(" (%1)")).arg(ui->slbSpindle->value()));
    }
    updateLayouts();

    ui->widgetSpindle->setVisible(checked);
}

void frmMain::on_grpUserCommands_toggled(bool checked)
{
    ui->widgetUserCommands->setVisible(checked);
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (obj->inherits("QWidgetWindow")) {

        QKeySequence ks;

        if ((event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)) {
            QKeyEvent *ev = static_cast<QKeyEvent*>(event);
            ks = QKeySequence(ev->key() | ev->modifiers());
        }

        // Jog on keyboard control
        if (!m_processingFile && ui->chkKeyboardControl->isChecked() &&
                (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
                && !static_cast<QKeyEvent*>(event)->isAutoRepeat()) {

            if (ui->actJogXMinus->shortcuts().contains(ks)) {
                if (event->type() == QEvent::KeyPress) emit ui->cmdXMinus->pressed(); else emit ui->cmdXMinus->released();                
            } else if (ui->actJogXPlus->shortcuts().contains(ks)) {
                if (event->type() == QEvent::KeyPress) emit ui->cmdXPlus->pressed(); else emit ui->cmdXPlus->released();
            } else if (ui->actJogYPlus->shortcuts().contains(ks)) {
                if (event->type() == QEvent::KeyPress) emit ui->cmdYPlus->pressed(); else emit ui->cmdYPlus->released();
            } else if (ui->actJogYMinus->shortcuts().contains(ks)) {
                if (event->type() == QEvent::KeyPress) emit ui->cmdYMinus->pressed(); else emit ui->cmdYMinus->released();
            } else if (ui->actJogZPlus->shortcuts().contains(ks)) {
                if (event->type() == QEvent::KeyPress) emit ui->cmdZPlus->pressed(); else emit ui->cmdZPlus->released();
            } else if (ui->actJogZMinus->shortcuts().contains(ks)) {
                if (event->type() == QEvent::KeyPress) emit ui->cmdZMinus->pressed(); else emit ui->cmdZMinus->released();
            }
        }
    } else if (obj == ui->tblProgram && m_processingFile) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_PageDown || keyEvent->key() == Qt::Key_PageUp
                    || keyEvent->key() == Qt::Key_Down || keyEvent->key() == Qt::Key_Up) {
            ui->chkAutoScroll->setChecked(false);
        }
    }

    if (obj == this && event->type() == QEvent::WindowStateChange) {
        ui->glwVisualizer->setUpdatesEnabled(!isMinimized() && ui->dockVisualizer->isVisible());
    }

    if (!ui->actViewLockPanels->isChecked() && obj->inherits("QGroupBox") 
        && (obj->parent()->objectName() == "scrollContentsDevice"
        || obj->parent()->objectName() == "scrollContentsModification"
        || obj->parent()->objectName() == "scrollContentsUser")
        && obj->objectName().startsWith("grp")) {

        if (event->type() == QEvent::MouseButtonPress) {
            
            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            m_mousePressPos = e->pos();
            qDebug() << m_mousePressPos;

        } else if (event->type() == QEvent::MouseMove) {

            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            int d = (e->pos() - m_mousePressPos).manhattanLength();

            if (e->buttons() & Qt::LeftButton && d > QApplication::startDragDistance()) {
                QDrag *drag = new QDrag(this);
                WidgetMimeData *mimeData = new WidgetMimeData();

                mimeData->setWidget(static_cast<QWidget*>(obj));

                QPixmap *pix = new QPixmap(static_cast<QWidget*>(obj)->size());
                static_cast<QWidget*>(obj)->render(pix);
                
                drag->setMimeData(mimeData);
                drag->setPixmap(*pix);
                drag->exec();
            }
        }
    }

    return false;
}

bool frmMain::keyIsMovement(int key)
{
    return key == Qt::Key_4 || key == Qt::Key_6 || key == Qt::Key_8 || key == Qt::Key_2 || key == Qt::Key_9 || key == Qt::Key_3;
}


void frmMain::on_grpJog_toggled(bool checked)
{
    updateJogTitle();
    updateLayouts();

    ui->widgetJog->setVisible(checked);
}

void frmMain::on_chkKeyboardControl_toggled(bool checked)
{
    ui->grpJog->setProperty("overrided", checked);
    style()->unpolish(ui->grpJog);
    ui->grpJog->ensurePolished();

    // Store/restore coordinate system
    if (checked) {
        sendCommand("$G", -2, m_settings->showUICommands());
    } else {
        if (m_absoluteCoordinates) sendCommand("G90", -1, m_settings->showUICommands());
    }

    if (!m_processingFile) m_storedKeyboardControl = checked;

    updateJogTitle();
    updateControlsState();
}

void frmMain::updateJogTitle()
{
    if (ui->grpJog->isChecked() || !ui->chkKeyboardControl->isChecked()) {
        ui->grpJog->setTitle(tr("Jog"));
    } else if (ui->chkKeyboardControl->isChecked()) {
        ui->grpJog->setTitle(tr("Jog") + QString(tr(" (%1/%2)"))
                             .arg(ui->cboJogStep->currentText().toDouble() > 0 ? ui->cboJogStep->currentText() : tr("C"))
                             .arg(ui->cboJogFeed->currentText()));
    }
}

void frmMain::on_tblProgram_customContextMenuRequested(const QPoint &pos)
{
    if (m_processingFile) return;

    if (ui->tblProgram->selectionModel()->selectedRows().count() > 0) {
        m_tableMenu->actions().at(0)->setEnabled(true);
        m_tableMenu->actions().at(1)->setEnabled(ui->tblProgram->selectionModel()->selectedRows()[0].row() != m_currentModel->rowCount() - 1);
    } else {
        m_tableMenu->actions().at(0)->setEnabled(false);
        m_tableMenu->actions().at(1)->setEnabled(false);
    }
    m_tableMenu->popup(ui->tblProgram->viewport()->mapToGlobal(pos));
}

void frmMain::updateLayouts()
{
    this->update();
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}

void frmMain::addRecentFile(QString fileName)
{
    m_recentFiles.removeAll(fileName);
    m_recentFiles.append(fileName);
    if (m_recentFiles.count() > 5) m_recentFiles.takeFirst();
}

void frmMain::addRecentHeightmap(QString fileName)
{
    m_recentHeightmaps.removeAll(fileName);
    m_recentHeightmaps.append(fileName);
    if (m_recentHeightmaps.count() > 5) m_recentHeightmaps.takeFirst();
}

void frmMain::onActRecentFileTriggered()
{
    QAction *action = static_cast<QAction*>(sender());
    QString fileName = action->text();

    if (action != NULL) {
        if (!saveChanges(m_heightMapMode)) return;
        if (!m_heightMapMode) loadFile(fileName); else loadHeightMap(fileName);
    }
}

void frmMain::onCboCommandReturnPressed()
{
    QString command = ui->cboCommand->currentText();
    if (command.isEmpty()) return;

    ui->cboCommand->setCurrentText("");
    sendCommand(command, -1);
}

void frmMain::updateRecentFilesMenu()
{
    foreach (QAction * action, ui->mnuRecent->actions()) {
        if (action->text() == "") break; else {
            ui->mnuRecent->removeAction(action);
            delete action;
        }
    }

    foreach (QString file, !m_heightMapMode ? m_recentFiles : m_recentHeightmaps) {
        QAction *action = new QAction(file, this);
        connect(action, SIGNAL(triggered()), this, SLOT(onActRecentFileTriggered()));
        ui->mnuRecent->insertAction(ui->mnuRecent->actions()[0], action);
    }

    updateControlsState();
}

void frmMain::on_actRecentClear_triggered()
{
    if (!m_heightMapMode) m_recentFiles.clear(); else m_recentHeightmaps.clear();
    updateRecentFilesMenu();
}

double frmMain::toMetric(double value)
{
    return m_settings->units() == 0 ? value : value * 25.4;
}

void frmMain::on_grpHeightMap_toggled(bool arg1)
{
    ui->widgetHeightMap->setVisible(arg1);
}

QRectF frmMain::borderRectFromTextboxes()
{
    QRectF rect;

    rect.setX(ui->txtHeightMapBorderX->value());
    rect.setY(ui->txtHeightMapBorderY->value());
    rect.setWidth(ui->txtHeightMapBorderWidth->value());
    rect.setHeight(ui->txtHeightMapBorderHeight->value());

    return rect;
}

QRectF frmMain::borderRectFromExtremes()
{
    QRectF rect;

    rect.setX(m_codeDrawer->getMinimumExtremes().x());
    rect.setY(m_codeDrawer->getMinimumExtremes().y());
    rect.setWidth(m_codeDrawer->getSizes().x());
    rect.setHeight(m_codeDrawer->getSizes().y());

    return rect;
}

void frmMain::updateHeightMapBorderDrawer()
{
    if (m_settingsLoading) return;

    m_heightMapBorderDrawer.setBorderRect(borderRectFromTextboxes());
}

void frmMain::updateHeightMapGrid(double arg1)
{
    if (sender()->property("previousValue").toDouble() != arg1 && !updateHeightMapGrid())
        static_cast<QDoubleSpinBox*>(sender())->setValue(sender()->property("previousValue").toDouble());
    else sender()->setProperty("previousValue", arg1);
}

bool frmMain::updateHeightMapGrid()
{
    if (m_settingsLoading) return true;

    // Grid map changing warning
    bool nan = true;
    for (int i = 0; i < m_heightMapModel.rowCount(); i++)
        for (int j = 0; j < m_heightMapModel.columnCount(); j++)
            if (!qIsNaN(m_heightMapModel.data(m_heightMapModel.index(i, j), Qt::UserRole).toDouble())) {
                nan = false;
                break;
            }
    if (!nan && QMessageBox::warning(this, this->windowTitle(), tr("Changing grid settings will reset probe data. Continue?"),
                                                           QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return false;

    // Update grid drawer
    QRectF borderRect = borderRectFromTextboxes();
    m_heightMapGridDrawer.setBorderRect(borderRect);
    m_heightMapGridDrawer.setGridSize(QPointF(ui->txtHeightMapGridX->value(), ui->txtHeightMapGridY->value()));
    m_heightMapGridDrawer.setZBottom(ui->txtHeightMapGridZBottom->value());
    m_heightMapGridDrawer.setZTop(ui->txtHeightMapGridZTop->value());

    // Reset model
    int gridPointsX = ui->txtHeightMapGridX->value();
    int gridPointsY = ui->txtHeightMapGridY->value();

    m_heightMapModel.resize(gridPointsX, gridPointsY);
    ui->tblHeightMap->setModel(NULL);
    ui->tblHeightMap->setModel(&m_heightMapModel);
    resizeTableHeightMapSections();

    // Update interpolation
    updateHeightMapInterpolationDrawer(true);

    // Generate probe program
    double gridStepX = gridPointsX > 1 ? borderRect.width() / (gridPointsX - 1) : 0;
    double gridStepY = gridPointsY > 1 ? borderRect.height() / (gridPointsY - 1) : 0;

    m_programLoading = true;
    m_probeModel.clear();
    m_probeModel.insertRow(0);

    m_probeModel.setData(m_probeModel.index(m_probeModel.rowCount() - 1, 1), QString("G21G90F%1G0Z%2").
                         arg(m_settings->heightmapProbingFeed()).arg(ui->txtHeightMapGridZTop->value()));
    m_probeModel.setData(m_probeModel.index(m_probeModel.rowCount() - 1, 1), QString("G0X0Y0"));
    m_probeModel.setData(m_probeModel.index(m_probeModel.rowCount() - 1, 1), QString("G38.2Z%1")
                         .arg(ui->txtHeightMapGridZBottom->value()));
    m_probeModel.setData(m_probeModel.index(m_probeModel.rowCount() - 1, 1), QString("G0Z%1")
                         .arg(ui->txtHeightMapGridZTop->value()));

    double x, y;

    for (int i = 0; i < gridPointsY; i++) {
        y = borderRect.top() + gridStepY * i;
        for (int j = 0; j < gridPointsX; j++) {
            x = borderRect.left() + gridStepX * (i % 2 ? gridPointsX - 1 - j : j);
            m_probeModel.setData(m_probeModel.index(m_probeModel.rowCount() - 1, 1), QString("G0X%1Y%2")
                                 .arg(x, 0, 'f', 3).arg(y, 0, 'f', 3));
            m_probeModel.setData(m_probeModel.index(m_probeModel.rowCount() - 1, 1), QString("G38.2Z%1")
                                 .arg(ui->txtHeightMapGridZBottom->value()));
            m_probeModel.setData(m_probeModel.index(m_probeModel.rowCount() - 1, 1), QString("G0Z%1")
                                 .arg(ui->txtHeightMapGridZTop->value()));
        }
    }

    m_programLoading = false;

    if (m_currentDrawer == m_probeDrawer) updateParser();

    m_heightMapChanged = true;
    return true;
}

void frmMain::updateHeightMapInterpolationDrawer(bool reset)
{
    if (m_settingsLoading) return;

    QRectF borderRect = borderRectFromTextboxes();
    m_heightMapInterpolationDrawer.setBorderRect(borderRect);

    QVector<QVector<double>> *interpolationData = new QVector<QVector<double>>;

    int interpolationPointsX = ui->txtHeightMapInterpolationStepX->value();// * (ui->txtHeightMapGridX->value() - 1) + 1;
    int interpolationPointsY = ui->txtHeightMapInterpolationStepY->value();// * (ui->txtHeightMapGridY->value() - 1) + 1;

    double interpolationStepX = interpolationPointsX > 1 ? borderRect.width() / (interpolationPointsX - 1) : 0;
    double interpolationStepY = interpolationPointsY > 1 ? borderRect.height() / (interpolationPointsY - 1) : 0;

    for (int i = 0; i < interpolationPointsY; i++) {
        QVector<double> row;
        for (int j = 0; j < interpolationPointsX; j++) {

            double x = interpolationStepX * j + borderRect.x();
            double y = interpolationStepY * i + borderRect.y();

            row.append(reset ? qQNaN() : Interpolation::bicubicInterpolate(borderRect, &m_heightMapModel, x, y));
        }
        interpolationData->append(row);
    }

    if (m_heightMapInterpolationDrawer.data() != NULL) {
        delete m_heightMapInterpolationDrawer.data();
    }
    m_heightMapInterpolationDrawer.setData(interpolationData);

    // Update grid drawer
    m_heightMapGridDrawer.update();

    // Heightmap changed by table user input
    if (sender() == &m_heightMapModel) m_heightMapChanged = true;

    // Reset heightmapped program model
    m_programHeightmapModel.clear();
}

void frmMain::on_chkHeightMapBorderShow_toggled(bool checked)
{
    Q_UNUSED(checked)

    updateControlsState();
}

void frmMain::on_txtHeightMapBorderX_valueChanged(double arg1)
{
    updateHeightMapBorderDrawer();
    updateHeightMapGrid(arg1);
}

void frmMain::on_txtHeightMapBorderWidth_valueChanged(double arg1)
{
    updateHeightMapBorderDrawer();
    updateHeightMapGrid(arg1);
}

void frmMain::on_txtHeightMapBorderY_valueChanged(double arg1)
{
    updateHeightMapBorderDrawer();
    updateHeightMapGrid(arg1);
}

void frmMain::on_txtHeightMapBorderHeight_valueChanged(double arg1)
{
    updateHeightMapBorderDrawer();
    updateHeightMapGrid(arg1);
}

void frmMain::on_chkHeightMapGridShow_toggled(bool checked)
{
    Q_UNUSED(checked)

    updateControlsState();
}

void frmMain::on_txtHeightMapGridX_valueChanged(double arg1)
{
    updateHeightMapGrid(arg1);
}

void frmMain::on_txtHeightMapGridY_valueChanged(double arg1)
{
    updateHeightMapGrid(arg1);
}

void frmMain::on_txtHeightMapGridZBottom_valueChanged(double arg1)
{
    updateHeightMapGrid(arg1);
}

void frmMain::on_txtHeightMapGridZTop_valueChanged(double arg1)
{
    updateHeightMapGrid(arg1);
}

void frmMain::on_cmdHeightMapMode_toggled(bool checked)
{
    // Update flag
    m_heightMapMode = checked;

    // Reset file progress
    m_fileCommandIndex = 0;
    m_fileProcessedCommandIndex = 0;
    m_lastDrawnLineIndex = 0;

    // Reset/restore g-code program modification on edit mode enter/exit
    if (ui->chkHeightMapUse->isChecked()) {
        on_chkHeightMapUse_clicked(!checked); // Update gcode program parser
    }

    if (checked) {
        ui->tblProgram->setModel(&m_probeModel);
        resizeTableHeightMapSections();
        m_currentModel = &m_probeModel;
        m_currentDrawer = m_probeDrawer;
        updateParser();  // Update probe program parser
    } else {
        m_probeParser.reset();
        if (!ui->chkHeightMapUse->isChecked()) {
            ui->tblProgram->setModel(&m_programModel);
            connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));
            ui->tblProgram->selectRow(0);

            resizeTableHeightMapSections();
            m_currentModel = &m_programModel;
            m_currentDrawer = m_codeDrawer;

            if (!ui->chkHeightMapUse->isChecked()) {
                ui->glwVisualizer->updateExtremes(m_codeDrawer);
                updateProgramEstimatedTime(m_currentDrawer->viewParser()->getLineSegmentList());
            }
        }
    }

    // Shadow toolpath
    QList<LineSegment*> list = m_viewParser.getLineSegmentList();
    QList<int> indexes;
    for (int i = m_lastDrawnLineIndex; i < list.count(); i++) {
        list[i]->setDrawn(checked);
        list[i]->setIsHightlight(false);
        indexes.append(i);
    }
    // Update only vertex color.
    // If chkHeightMapUse was checked codeDrawer updated via updateParser
    if (!ui->chkHeightMapUse->isChecked()) m_codeDrawer->update(indexes);

    updateRecentFilesMenu();
    updateControlsState();
}

bool frmMain::saveHeightMap(QString fileName)
{
    QFile file(fileName);
    QDir dir;

    if (file.exists()) dir.remove(file.fileName());
    if (!file.open(QIODevice::WriteOnly)) return false;

    QTextStream textStream(&file);
    textStream << ui->txtHeightMapBorderX->text() << ";"
               << ui->txtHeightMapBorderY->text() << ";"
               << ui->txtHeightMapBorderWidth->text() << ";"
               << ui->txtHeightMapBorderHeight->text() << "\r\n";
    textStream << ui->txtHeightMapGridX->text() << ";"
               << ui->txtHeightMapGridY->text() << ";"
               << ui->txtHeightMapGridZBottom->text() << ";"
               << ui->txtHeightMapGridZTop->text() << "\r\n";
    textStream << ui->cboHeightMapInterpolationType->currentIndex() << ";"
               << ui->txtHeightMapInterpolationStepX->text() << ";"
                << ui->txtHeightMapInterpolationStepY->text() << "\r\n";

    for (int i = 0; i < m_heightMapModel.rowCount(); i++) {
        for (int j = 0; j < m_heightMapModel.columnCount(); j++) {
            textStream << m_heightMapModel.data(m_heightMapModel.index(i, j), Qt::UserRole).toString() << ((j == m_heightMapModel.columnCount() - 1) ? "" : ";");
        }
        textStream << "\r\n";
    }

    file.close();

    m_heightMapChanged = false;

    return true;
}

void frmMain::loadHeightMap(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, this->windowTitle(), tr("Can't open file:\n") + fileName);
        return;
    }
    QTextStream textStream(&file);

    m_settingsLoading = true;

    // Storing previous values
    ui->txtHeightMapBorderX->setValue(qQNaN());
    ui->txtHeightMapBorderY->setValue(qQNaN());
    ui->txtHeightMapBorderWidth->setValue(qQNaN());
    ui->txtHeightMapBorderHeight->setValue(qQNaN());

    ui->txtHeightMapGridX->setValue(qQNaN());
    ui->txtHeightMapGridY->setValue(qQNaN());
    ui->txtHeightMapGridZBottom->setValue(qQNaN());
    ui->txtHeightMapGridZTop->setValue(qQNaN());

    QList<QString> list = textStream.readLine().split(";");
    ui->txtHeightMapBorderX->setValue(list[0].toDouble());
    ui->txtHeightMapBorderY->setValue(list[1].toDouble());
    ui->txtHeightMapBorderWidth->setValue(list[2].toDouble());
    ui->txtHeightMapBorderHeight->setValue(list[3].toDouble());

    list = textStream.readLine().split(";");
    ui->txtHeightMapGridX->setValue(list[0].toDouble());
    ui->txtHeightMapGridY->setValue(list[1].toDouble());
    ui->txtHeightMapGridZBottom->setValue(list[2].toDouble());
    ui->txtHeightMapGridZTop->setValue(list[3].toDouble());

    m_settingsLoading = false;

    updateHeightMapBorderDrawer();

    m_heightMapModel.clear();   // To avoid probe data wipe message
    updateHeightMapGrid();

    list = textStream.readLine().split(";");

    for (int i = 0; i < m_heightMapModel.rowCount(); i++) {
        QList<QString> row = textStream.readLine().split(";");
        for (int j = 0; j < m_heightMapModel.columnCount(); j++) {
            m_heightMapModel.setData(m_heightMapModel.index(i, j), row[j].toDouble(), Qt::UserRole);
        }
    }

    file.close();

    ui->txtHeightMap->setText(fileName.mid(fileName.lastIndexOf("/") + 1));
    m_heightMapFileName = fileName;
    m_heightMapChanged = false;

    ui->cboHeightMapInterpolationType->setCurrentIndex(list[0].toInt());
    ui->txtHeightMapInterpolationStepX->setValue(list[1].toDouble());
    ui->txtHeightMapInterpolationStepY->setValue(list[2].toDouble());

    updateHeightMapInterpolationDrawer();
}

void frmMain::on_chkHeightMapInterpolationShow_toggled(bool checked)
{
    Q_UNUSED(checked)

    updateControlsState();
}

void frmMain::on_cmdHeightMapLoad_clicked()
{
    if (!saveChanges(true)) {
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), m_lastFolder, tr("Heightmap files (*.map)"));

    if (fileName != "") {
        addRecentHeightmap(fileName);
        loadHeightMap(fileName);

        // If using heightmap
        if (ui->chkHeightMapUse->isChecked() && !m_heightMapMode) {
            // Restore original file
            on_chkHeightMapUse_clicked(false);
            // Apply heightmap
            on_chkHeightMapUse_clicked(true);
        }

        updateRecentFilesMenu();
        updateControlsState(); // Enable 'cmdHeightMapMode' button
    }
}

void frmMain::on_txtHeightMapInterpolationStepX_valueChanged(double arg1)
{
    Q_UNUSED(arg1)

    updateHeightMapInterpolationDrawer();
}

void frmMain::on_txtHeightMapInterpolationStepY_valueChanged(double arg1)
{
    Q_UNUSED(arg1)

    updateHeightMapInterpolationDrawer();
}

void frmMain::on_chkHeightMapUse_clicked(bool checked)
{
//    static bool fileChanged;

    // Reset table view
    QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();
    ui->tblProgram->setModel(NULL);

    CancelException cancel;

    if (checked) try {

        // Prepare progress dialog
        QProgressDialog progress(tr("Applying heightmap..."), tr("Abort"), 0, 0, this);
        progress.setWindowModality(Qt::WindowModal);
        progress.setFixedHeight(progress.sizeHint().height());
        progress.show();
        progress.setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");

        // Set current model to prevent reseting heightmap cache
        m_currentModel = &m_programHeightmapModel;

        // Update heightmap-modificated program if not cached
        if (m_programHeightmapModel.rowCount() == 0) {

            // Modifying linesegments
            QList<LineSegment*> *list = m_viewParser.getLines();
            QRectF borderRect = borderRectFromTextboxes();
            double x, y, z;
            QVector3D point;

            progress.setLabelText(tr("Subdividing segments..."));
            progress.setMaximum(list->count() - 1);

            for (int i = 0; i < list->count(); i++) {
                if (!list->at(i)->isZMovement()) {
                    QList<LineSegment*> subSegments = subdivideSegment(list->at(i));

                    if (subSegments.count() > 0) {
                        delete list->at(i);
                        list->removeAt(i);
                        foreach (LineSegment* subSegment, subSegments) list->insert(i++, subSegment);
                        i--;
                    }
                }

                if (progress.isVisible() && (i % PROGRESSSTEP == 0)) {
                    progress.setMaximum(list->count() - 1);
                    progress.setValue(i);
                    qApp->processEvents();
                    if (progress.wasCanceled()) throw cancel;
                }
            }

            progress.setLabelText(tr("Updating Z-coordinates..."));
            progress.setMaximum(list->count() - 1);

            for (int i = 0; i < list->count(); i++) {
                if (i == 0) {
                    x = list->at(i)->getStart().x();
                    y = list->at(i)->getStart().y();
                    z = list->at(i)->getStart().z() + Interpolation::bicubicInterpolate(borderRect, &m_heightMapModel, x, y);
                    list->at(i)->setStart(QVector3D(x, y, z));
                } else list->at(i)->setStart(list->at(i - 1)->getEnd());

                x = list->at(i)->getEnd().x();
                y = list->at(i)->getEnd().y();
                z = list->at(i)->getEnd().z() + Interpolation::bicubicInterpolate(borderRect, &m_heightMapModel, x, y);
                list->at(i)->setEnd(QVector3D(x, y, z));

                if (progress.isVisible() && (i % PROGRESSSTEP == 0)) {
                    progress.setValue(i);
                    qApp->processEvents();
                    if (progress.wasCanceled()) throw cancel;
                }
            }

            progress.setLabelText(tr("Modifying G-code program..."));
            progress.setMaximum(m_programModel.rowCount() - 2);

            // Modifying g-code program
            QString command;
            QStringList args;
            int line;
            QString newCommand;
            GCodeItem item;
            int lastSegmentIndex = 0;
            int lastCommandIndex = -1;

            // Search strings
            QString coords("XxYyZzIiJjKkRr");
            QString g("Gg");
            QString m("Mm");

            char codeChar;          // Single code char G1 -> G
            float codeNum;          // Code number      G1 -> 1

            QString lastCode;
            bool isLinearMove;
            bool hasCommand;

            m_programLoading = true;
            for (int i = 0; i < m_programModel.rowCount() - 1; i++) {
                command = m_programModel.data().at(i).command;
                line = m_programModel.data().at(i).line;
                isLinearMove = false;
                hasCommand = false;

                if (line < 0 || line == lastCommandIndex || lastSegmentIndex == list->count() - 1) {
                    item.command = command;
                    m_programHeightmapModel.data().append(item);
                } else {
                    // Get commands args
                    args = m_programModel.data().at(i).args;
                    newCommand.clear();

                    // Parse command args
                    foreach (QString arg, args) {                   // arg examples: G1, G2, M3, X100...
                        codeChar = arg.at(0).toLatin1();            // codeChar: G, M, X...
                        if (!coords.contains(codeChar)) {           // Not parameter
                            codeNum = arg.mid(1).toDouble();
                            if (g.contains(codeChar)) {             // 'G'-command
                                // Store 'G0' & 'G1'
                                if (codeNum == 0.0f || codeNum == 1.0f) {
                                    lastCode = arg;
                                    isLinearMove = true;            // Store linear move
                                }

                                // Replace 'G2' & 'G3' with 'G1'
                                if (codeNum == 2.0f || codeNum == 3.0f) {
                                    newCommand.append("G1");
                                    isLinearMove = true;
                                // Drop plane command for arcs
                                } else if (codeNum != 17.0f && codeNum != 18.0f && codeNum != 19.0f) {
                                    newCommand.append(arg);
                                }

                                hasCommand = true;                  // Command has 'G'
                            } else {
                                if (m.contains(codeChar))
                                    hasCommand = true;              // Command has 'M'
                                newCommand.append(arg);       // Other commands
                            }
                        }
                    }

                    // Find first linesegment by command index
                    for (int j = lastSegmentIndex; j < list->count(); j++) {
                        if (list->at(j)->getLineNumber() == line) {
                            if (!qIsNaN(list->at(j)->getEnd().length()) && (isLinearMove || (!hasCommand && !lastCode.isEmpty()))) {
                                // Create new commands for each linesegment with given command index
                                while ((j < list->count()) && (list->at(j)->getLineNumber() == line)) {

                                    point = list->at(j)->getEnd();
                                    if (!list->at(j)->isAbsolute()) point -= list->at(j)->getStart();
                                    if (!list->at(j)->isMetric()) point /= 25.4;

                                    item.command = newCommand + QString("X%1Y%2Z%3")
                                            .arg(point.x(), 0, 'f', 3).arg(point.y(), 0, 'f', 3).arg(point.z(), 0, 'f', 3);
                                    m_programHeightmapModel.data().append(item);

                                    if (!newCommand.isEmpty()) newCommand.clear();
                                    j++;
                                }
                            // Copy original command if not G0 or G1
                            } else {
                                item.command = command;
                                m_programHeightmapModel.data().append(item);
                            }

                            lastSegmentIndex = j;
                            break;
                        }
                    }
                }
                lastCommandIndex = line;

                if (progress.isVisible() && (i % PROGRESSSTEP == 0)) {
                    progress.setValue(i);
                    qApp->processEvents();
                    if (progress.wasCanceled()) throw cancel;
                }
            }
            m_programHeightmapModel.insertRow(m_programHeightmapModel.rowCount());
        }
        progress.close();

        ui->tblProgram->setModel(&m_programHeightmapModel);
        ui->tblProgram->horizontalHeader()->restoreState(headerState);

        connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));

        m_programLoading = false;

        // Update parser
        m_currentDrawer = m_codeDrawer;
        updateParser();

        // Select first row
        ui->tblProgram->selectRow(0);
    }
    catch (CancelException) {                       // Cancel modification
        m_programHeightmapModel.clear();
        m_currentModel = &m_programModel;

        ui->tblProgram->setModel(&m_programModel);
        ui->tblProgram->horizontalHeader()->restoreState(headerState);

        connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));
        ui->tblProgram->selectRow(0);

        ui->chkHeightMapUse->setChecked(false);

        return;
    } else {                                        // Restore original program
        m_currentModel = &m_programModel;

        ui->tblProgram->setModel(&m_programModel);
        ui->tblProgram->horizontalHeader()->restoreState(headerState);

        connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));

        // Store changes flag
        bool fileChanged = m_fileChanged;

        // Update parser
        updateParser();

        // Select first row
        ui->tblProgram->selectRow(0);

        // Restore changes flag
        m_fileChanged = fileChanged;
    }

    // Update groupbox title
    ui->grpHeightMap->setProperty("overrided", checked);
    style()->unpolish(ui->grpHeightMap);
    ui->grpHeightMap->ensurePolished();

    // Update menu
    ui->actFileSaveTransformedAs->setVisible(checked);
}

QList<LineSegment*> frmMain::subdivideSegment(LineSegment* segment)
{
    QList<LineSegment*> list;

    QRectF borderRect = borderRectFromTextboxes();

    double interpolationStepX = borderRect.width() / (ui->txtHeightMapInterpolationStepX->value() - 1);
    double interpolationStepY = borderRect.height() / (ui->txtHeightMapInterpolationStepY->value() - 1);

    double length;

    QVector3D vec = segment->getEnd() - segment->getStart();

    if (qIsNaN(vec.length())) return QList<LineSegment*>();

    if (fabs(vec.x()) / fabs(vec.y()) < interpolationStepX / interpolationStepY) length = interpolationStepY / (vec.y() / vec.length());
    else length = interpolationStepX / (vec.x() / vec.length());

    length = fabs(length);

    if (qIsNaN(length)) {
        return QList<LineSegment*>();
    }

    QVector3D seg = vec.normalized() * length;
    // int count = trunc(vec.length() / length);
    int count = (vec.length() / length);

    if (count == 0) return QList<LineSegment*>();

    for (int i = 0; i < count; i++) {
        LineSegment* line = new LineSegment(segment);
        line->setStart(i == 0 ? segment->getStart() : list[i - 1]->getEnd());
        line->setEnd(line->getStart() + seg);
        list.append(line);
    }

    if (list.count() > 0 && list.last()->getEnd() != segment->getEnd()) {
        LineSegment* line = new LineSegment(segment);
        line->setStart(list.last()->getEnd());
        line->setEnd(segment->getEnd());
        list.append(line);
    }

    return list;
}

void frmMain::on_cmdHeightMapCreate_clicked()
{
    ui->cmdHeightMapMode->setChecked(true);
    on_actFileNew_triggered();
}

void frmMain::on_cmdHeightMapBorderAuto_clicked()
{
    QRectF rect = borderRectFromExtremes();

    if (!qIsNaN(rect.width()) && !qIsNaN(rect.height())) {
        ui->txtHeightMapBorderX->setValue(rect.x());
        ui->txtHeightMapBorderY->setValue(rect.y());
        ui->txtHeightMapBorderWidth->setValue(rect.width());
        ui->txtHeightMapBorderHeight->setValue(rect.height());
    }
}

bool frmMain::compareCoordinates(double x, double y, double z)
{
    return ui->txtMPosX->value() == x && ui->txtMPosY->value() == y && ui->txtMPosZ->value() == z;
}

void frmMain::onCmdUserClicked(bool checked)
{
    int i = sender()->objectName().right(1).toInt();

    QStringList list = m_settings->userCommands(i).remove("\n").split(QRegExp(";(?![^\\{]+\\})"));

    foreach (QString cmd, list) {
        if (!cmd.isEmpty()) sendCommand(cmd.trimmed(), -1, m_settings->showUICommands(), list.indexOf(cmd));
    }
}

void frmMain::onOverridingToggled(bool checked)
{
    ui->grpOverriding->setProperty("overrided", ui->slbFeedOverride->isChecked()
                                   || ui->slbRapidOverride->isChecked() || ui->slbSpindleOverride->isChecked());
    style()->unpolish(ui->grpOverriding);
    ui->grpOverriding->ensurePolished();
}

void frmMain::onOverrideChanged()
{
    updateProgramEstimatedTime(m_currentDrawer->viewParser()->getLineSegmentList());
}

void frmMain::updateOverride(SliderBox *slider, int value, char command)
{
    slider->setCurrentValue(value);

    int target = slider->isChecked() ? slider->value() : 100;
    bool smallStep = abs(target - slider->currentValue()) < 10 || m_settings->queryStateTime() < 100;

    if (slider->currentValue() < target) {
        m_serialPort.write(QByteArray(1, char(smallStep ? command + 2 : command)));
    } else if (slider->currentValue() > target) {
        m_serialPort.write(QByteArray(1, char(smallStep ? command + 3 : command + 1)));
    }
}

void frmMain::jogStep()
{
    if (m_jogVector.length() == 0) return;

    if (ui->cboJogStep->currentText().toDouble() == 0) {
        const double acc = m_settings->acceleration();              // Acceleration mm/sec^2
        int speed = ui->cboJogFeed->currentText().toInt();          // Speed mm/min
        double v = (double)speed / 60;                              // Rapid speed mm/sec
        int N = 15;                                                 // Planner blocks
        double tt = 0.002;                                          // Transfer time
        double dt = qMax(0.01, sqrt(v) / (2 * acc * (N - 1))) + tt; // Single jog command time
        double s = v * dt;                                          // Jog distance

        QVector3D vec = m_jogVector.normalized() * s;

        sendCommand(QString("$J=G21G91X%1Y%2Z%3F%4")
                    .arg(vec.x(), 0, 'g', 4)
                    .arg(vec.y(), 0, 'g', 4)
                    .arg(vec.z(), 0, 'g', 4)
                    .arg(speed), -2, m_settings->showUICommands());
    } else {
        int speed = ui->cboJogFeed->currentText().toInt();          // Speed mm/min
        QVector3D vec = m_jogVector * ui->cboJogStep->currentText().toDouble();

        sendCommand(QString("$J=G21G91X%1Y%2Z%3F%4")
                    .arg(vec.x(), 0, 'g', 4)
                    .arg(vec.y(), 0, 'g', 4)
                    .arg(vec.z(), 0, 'g', 4)
                    .arg(speed), -3, m_settings->showUICommands());
    }
}

QString frmMain::evaluateCommand(QString command)
{
    // Evaluate script  
    static QRegExp sx("\\{([^\\}]+)\\}");
    QScriptValue v;
    QString vs;
    while (sx.indexIn(command) != -1) {
        v = m_scriptEngine.evaluate(sx.cap(1));
        vs = v.isUndefined() ? "" : v.isNumber() ? QString::number(v.toNumber(), 'f', 4) : v.toString();
        command.replace(sx.cap(0), vs);
    }
    return command;
}

void frmMain::setupCoordsTextboxes()
{
    int prec = m_settings->units() == 0 ? 3 : 4;
    int bound = m_settings->units() == 0 ? 9999 : 999;

    ui->txtMPosX->setDecimals(prec);
    ui->txtMPosX->setMinimum(-bound);
    ui->txtMPosX->setMaximum(bound);
    ui->txtMPosY->setDecimals(prec);
    ui->txtMPosY->setMinimum(-bound);
    ui->txtMPosY->setMaximum(bound);
    ui->txtMPosZ->setDecimals(prec);
    ui->txtMPosZ->setMinimum(-bound);
    ui->txtMPosZ->setMaximum(bound);

    ui->txtWPosX->setDecimals(prec);
    ui->txtWPosX->setMinimum(-bound);
    ui->txtWPosX->setMaximum(bound);
    ui->txtWPosY->setDecimals(prec);
    ui->txtWPosY->setMinimum(-bound);
    ui->txtWPosY->setMaximum(bound);
    ui->txtWPosZ->setDecimals(prec);
    ui->txtWPosZ->setMinimum(-bound);
    ui->txtWPosZ->setMaximum(bound);    
}

void frmMain::loadPlugins()
{
    QString pluginsDir = qApp->applicationDirPath() + "/plugins/";

    UiLoader uiLoader;

    // Get plugins list
    QStringList pl = QDir(pluginsDir).entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    qDebug() << "Loading plugins:" << pl;

    foreach (QString p, pl) {
        // Config
        QSettings set(pluginsDir + p + "/config.ini", QSettings::IniFormat);
        QString title = set.value("title").toString();
        QString name = set.value("name").toString();
        QString type = set.value("type").toString();
        qDebug() << "Loading plugin:" << p << title << name << type;

        // Translation
        QString loc = QLocale().name().left(2);
        QString translationFileName = pluginsDir + p + "/translation_" + loc + ".qm";
        if(QFile::exists(translationFileName)) {
            QTranslator *translator = new QTranslator();
            if (translator->load(translationFileName)) qApp->installTranslator(translator);
            else delete translator;
        }        

        // Ui
        uiLoader.setWorkingDirectory(pluginsDir + p);
        uiLoader.addPluginPath(pluginsDir + p + "/plugins");

            // Main
        QWidget *widget = 0;
        QFile f(pluginsDir + p + "/widget.ui");
        if (f.open(QFile::ReadOnly)) {
            // Load widget
            widget = uiLoader.load(&f, this);
            f.close();

            if (widget) {
                if (type.toUpper() == "PANEL") {
                    // Create panel
                    GroupBox *box = new GroupBox(this);
                    QVBoxLayout *layout1 = new QVBoxLayout(box);
                    QWidget *bw = new QWidget(box);
                    QVBoxLayout *layout2 = new QVBoxLayout(bw);
                    box->setObjectName("grp" + name);
                    box->setTitle(tr(title.toLatin1()));
                    box->setLayout(layout1);
                    box->setCheckable(true);
                    box->setProperty("overrided", false);
                    layout1->addWidget(bw);
                    bw->setLayout(layout2);
                    layout2->addWidget(widget);
                    layout2->setMargin(0);
                    connect(box, &QGroupBox::toggled, bw, &QWidget::setVisible);

                    // Add panel to user window
                    static_cast<QVBoxLayout*>(ui->scrollContentsUser->layout())->insertWidget(0, box);

                } else if (type.toUpper() == "WINDOW") {
                    // Create dock widget
                    QDockWidget *dock = new QDockWidget(this);
                    QWidget *contents = new QWidget(dock);
                    QFrame *frame = new QFrame(contents);
                    QVBoxLayout *layout1 = new QVBoxLayout(contents);
                    QVBoxLayout *layout2 = new QVBoxLayout(frame);
                    dock->setObjectName("dock" + name);
                    dock->setWindowTitle(tr(title.toLatin1()));
                    dock->setWidget(contents);
                    contents->setLayout(layout1);
                    layout1->addWidget(frame);
                    QMargins m = layout1->contentsMargins();
                    m.setLeft(0);
                    m.setRight(0);
                    layout1->setContentsMargins(m);
                    frame->setLayout(layout2);
                    layout2->addWidget(widget);
                    layout2->setMargin(0);

                    // Add to main form
                    this->addDockWidget(Qt::RightDockWidgetArea, dock);

                } else {
                    qDebug() << "Unknown plugin type" << type;
                }
            }
        }

            // Settings
        QWidget *settingsWidget = 0;
        f.setFileName(pluginsDir + p + "/settings.ui");
        if (f.open(QFile::ReadOnly)) {
            // Load settings widget
            uiLoader.setWorkingDirectory(pluginsDir + p);
            settingsWidget = uiLoader.load(&f, this);
            f.close();

            if (settingsWidget) {
                // Create groupbox
                GroupBox *box = new GroupBox(m_settings);
                QVBoxLayout *layout1 = new QVBoxLayout(box);
                box->setObjectName("grpSettings" + name);
                box->setTitle(tr(title.toLatin1()));
                box->setLayout(layout1);
                layout1->addWidget(settingsWidget);

                // Add to settings form
                m_settings->addCustomSettings(box);
            }
        }

        // Delegate actions to main form
        QList<QAction*> acts = widget->findChildren<QAction*>();
        foreach (QAction *a, acts) addAction(a);

        // Script
        f.setFileName(pluginsDir + p + "/script.js");
        if (f.open(QFile::ReadOnly)) {
            QScriptEngine *se = new QScriptEngine();

            // Delegate Ui
            if (widget) {
                QScriptValue sw = se->newQObject(widget);
                se->globalObject().setProperty("ui", sw);
            }

                // Settings ui
            if (settingsWidget) {
                QScriptValue setw = se->newQObject(settingsWidget);
                se->globalObject().setProperty("settings", setw);
            }

            // Main form
            QScriptValue main = se->newQObject(this);
            se->globalObject().setProperty("main", main);

            // Settings
            QScriptValue settings = se->newQObject(m_settings);
            se->globalObject().setProperty("mainSettings", settings);

            // Stored vars
            QScriptValue vars = se->newQObject(&m_storedVars);
            se->globalObject().setProperty("vars", vars);

            // Translator
            se->installTranslatorFunctions();

            // Run script
            QString script = f.readAll();
            qDebug() << "Running plugin:" << p <<  se->evaluate(script).toString();
            qDebug() << se->uncaughtExceptionBacktrace();

            f.close();
        }
    }
}

void frmMain::on_cmdYPlus_pressed()
{
    m_jogVector += QVector3D(0, 1, 0);
    jogStep();
}

void frmMain::on_cmdYPlus_released()
{
    m_jogVector -= QVector3D(0, 1, 0);
    jogStep();
}

void frmMain::on_cmdYMinus_pressed()
{
    m_jogVector += QVector3D(0, -1, 0);
    jogStep();
}

void frmMain::on_cmdYMinus_released()
{
    m_jogVector -= QVector3D(0, -1, 0);
    jogStep();
}

void frmMain::on_cmdXPlus_pressed()
{
    m_jogVector += QVector3D(1, 0, 0);
    jogStep();
}

void frmMain::on_cmdXPlus_released()
{
    m_jogVector -= QVector3D(1, 0, 0);
    jogStep();
}

void frmMain::on_cmdXMinus_pressed()
{
    m_jogVector += QVector3D(-1, 0, 0);
    jogStep();
}

void frmMain::on_cmdXMinus_released()
{
    m_jogVector -= QVector3D(-1, 0, 0);
    jogStep();
}

void frmMain::on_cmdZPlus_pressed()
{
    m_jogVector += QVector3D(0, 0, 1);
    jogStep();
}

void frmMain::on_cmdZPlus_released()
{
    m_jogVector -= QVector3D(0, 0, 1);
    jogStep();
}

void frmMain::on_cmdZMinus_pressed()
{
    m_jogVector += QVector3D(0, 0, -1);
    jogStep();
}

void frmMain::on_cmdZMinus_released()
{
    m_jogVector -= QVector3D(0, 0, -1);
    jogStep();
}

void frmMain::on_cmdStop_clicked()
{
    m_queue.clear();
    m_serialPort.write(QByteArray(1, char(0x85)));
}

void frmMain::on_mnuViewWindows_aboutToShow()
{
    QAction *a;
    QList<QAction*> al;

    foreach (QDockWidget *d, findChildren<QDockWidget*>()) {
        a = new QAction(d->windowTitle(), ui->mnuViewWindows);
        a->setCheckable(true);
        a->setChecked(d->isVisible());
        connect(a, &QAction::triggered, d, &QDockWidget::setVisible);
        al.append(a);
    }

    qSort(al.begin(), al.end(), frmMain::actionTextLessThan);

    ui->mnuViewWindows->clear();
    ui->mnuViewWindows->addActions(al);
}

void frmMain::on_mnuViewPanels_aboutToShow()
{
    QAction *a;

    ui->mnuViewPanels->clear();

    QStringList panels;
    if (ui->scrollContentsDevice->isVisible()) panels << ui->scrollContentsDevice->saveState();
    if (ui->scrollContentsModification->isVisible()) panels << "\n" << ui->scrollContentsModification->saveState();
    if (ui->scrollContentsUser->isVisible()) panels << "\n" << ui->scrollContentsUser->saveState();

    foreach (QString s, panels) {
        if (s == "\n") {
            ui->mnuViewPanels->addSeparator();
        } else {
            QGroupBox *b = findChild<QGroupBox*>(s);
            if (b) {
                a = ui->mnuViewPanels->addAction(b->title());
                a->setCheckable(true);
                a->setChecked(b->isVisible());
                connect(a, &QAction::triggered, b, &QWidget::setVisible);
            }
        }
    }
}

void frmMain::on_actJogStepNext_triggered()
{
    ui->cboJogStep->setCurrentNext();
}

void frmMain::on_actJogStepPrevious_triggered()
{
    ui->cboJogStep->setCurrentPrevious();
}

void frmMain::on_actJogFeedNext_triggered()
{
    ui->cboJogFeed->setCurrentNext();
}

void frmMain::on_actJogFeedPrevious_triggered()
{
    ui->cboJogFeed->setCurrentPrevious();
}

void frmMain::on_actSpindleSpeedPlus_triggered()
{
    ui->slbSpindle->setSliderPosition(ui->slbSpindle->sliderPosition() + 1);
}

void frmMain::on_actSpindleSpeedMinus_triggered()
{
    ui->slbSpindle->setSliderPosition(ui->slbSpindle->sliderPosition() - 1);
}

void frmMain::on_actOverrideFeedPlus_triggered()
{
    ui->slbFeedOverride->setSliderPosition(ui->slbFeedOverride->sliderPosition() + 1);
}

void frmMain::on_actOverrideFeedMinus_triggered()
{
    ui->slbFeedOverride->setSliderPosition(ui->slbFeedOverride->sliderPosition() - 1);
}

void frmMain::on_actOverrideRapidPlus_triggered()
{
    ui->slbRapidOverride->setSliderPosition(ui->slbRapidOverride->sliderPosition() + 1);
}

void frmMain::on_actOverrideRapidMinus_triggered()
{
    ui->slbRapidOverride->setSliderPosition(ui->slbRapidOverride->sliderPosition() - 1);
}

void frmMain::on_actOverrideSpindlePlus_triggered()
{
    ui->slbSpindleOverride->setSliderPosition(ui->slbSpindleOverride->sliderPosition() + 1);
}

void frmMain::on_actOverrideSpindleMinus_triggered()
{
    ui->slbSpindleOverride->setSliderPosition(ui->slbSpindleOverride->sliderPosition() - 1);
}

void frmMain::on_dockVisualizer_visibilityChanged(bool visible)
{
    ui->glwVisualizer->setUpdatesEnabled(visible);
}

void frmMain::on_actViewLockWindows_toggled(bool checked)
{
    QList<QDockWidget*> dl = findChildren<QDockWidget*>();

    foreach (QDockWidget *d, dl) {
        d->setFeatures(checked ? QDockWidget::NoDockWidgetFeatures : QDockWidget::AllDockWidgetFeatures);
    }
}