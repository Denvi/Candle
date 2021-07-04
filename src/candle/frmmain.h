// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSettings>
#include <QTimer>
#include <QBasicTimer>
#include <QStringList>
#include <QList>
#include <QTime>
#include <QMenu>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QProgressDialog>
#include <QScriptEngine>
#include <QGroupBox>
#include <exception>

#include "parser/gcodeviewparse.h"

#include "drawers/origindrawer.h"
#include "drawers/gcodedrawer.h"
#include "drawers/tooldrawer.h"
#include "drawers/heightmapborderdrawer.h"
#include "drawers/heightmapgriddrawer.h"
#include "drawers/heightmapinterpolationdrawer.h"
#include "drawers/shaderdrawable.h"
#include "drawers/selectiondrawer.h"
#include "drawers/machineboundsdrawer.h"

#include "tables/gcodetablemodel.h"
#include "tables/heightmaptablemodel.h"

#include "utils/interpolation.h"

#include "styledtoolbutton.h"
#include "sliderbox.h"

#include "frmsettings.h"
#include "frmabout.h"

#include "scriptvars.h"
#include "scriptfunctions.h"

#ifdef WINDOWS
    #include <QtWinExtras/QtWinExtras>
    #include "shobjidl.h"
#endif

namespace Ui {
class frmMain;
class frmProgram;
}

struct CommandAttributes {
    int length;
    int consoleIndex;
    int tableIndex;
    QString command;
};

struct CommandQueue {
    QString command;
    int tableIndex;
    bool showInConsole;
    bool wait;
};

class CancelException : public std::exception {
public:
#ifdef Q_OS_MAC
#undef _GLIBCXX_USE_NOEXCEPT
#define _GLIBCXX_USE_NOEXCEPT _NOEXCEPT
#endif

    const char* what() const throw()
    {
        return "Operation was cancelled by user";
    }
};

class frmMain : public QMainWindow
{
    Q_OBJECT

    friend class ScriptFunctions;

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

signals:
    void responseReceived(QString command, int tableIndex, QString response);
    void statusReceived(QString status);
    void senderStateChanged(int state);
    void deviceStateChanged(int state);
    void settingsAboutToLoad();
    void settingsLoaded();
    void settingsAboutToSave();
    void settingsSaved();
    void settingsAboutToShow();
    void settingsAccepted();
    void settingsRejected();
    void settingsSetByDefault();
    void pluginsLoaded();

private slots:
    void on_actFileNew_triggered();
    void on_actFileOpen_triggered();
    void on_actFileSave_triggered();
    void on_actFileSaveAs_triggered();
    void on_actFileSaveTransformedAs_triggered();
    void on_actRecentClear_triggered();
    void on_actFileExit_triggered();
    void on_actServiceSettings_triggered();
    void on_actAbout_triggered();
    void on_actJogStepNext_triggered();
    void on_actJogStepPrevious_triggered();
    void on_actJogFeedNext_triggered();
    void on_actJogFeedPrevious_triggered();
    void on_actSpindleSpeedPlus_triggered();
    void on_actSpindleSpeedMinus_triggered();
    void on_actOverrideFeedPlus_triggered();
    void on_actOverrideFeedMinus_triggered();
    void on_actOverrideRapidPlus_triggered();
    void on_actOverrideRapidMinus_triggered();
    void on_actOverrideSpindlePlus_triggered();
    void on_actOverrideSpindleMinus_triggered();
    void on_actViewLockWindows_toggled(bool checked);
    void on_cmdFileOpen_clicked();
    void on_cmdFileSend_clicked();
    void on_cmdFilePause_clicked(bool checked);
    void on_cmdFileAbort_clicked();
    void on_cmdFileReset_clicked();
    void on_cmdCommandSend_clicked();
    void on_cmdClearConsole_clicked();
    void on_cmdHome_clicked();
    void on_cmdCheck_clicked(bool checked);
    void on_cmdReset_clicked();
    void on_cmdUnlock_clicked();
    void on_cmdHold_clicked(bool checked);
    void on_cmdSleep_clicked();
    void on_cmdDoor_clicked();
    void on_cmdFlood_clicked();
    void on_cmdSpindle_toggled(bool checked);
    void on_cmdSpindle_clicked(bool checked);
    void on_cmdTop_clicked();
    void on_cmdFront_clicked();
    void on_cmdLeft_clicked();
    void on_cmdIsometric_clicked();
    void on_cmdFit_clicked();
    void on_grpOverriding_toggled(bool checked);
    void on_grpSpindle_toggled(bool checked);
    void on_grpJog_toggled(bool checked);
    void on_grpHeightMap_toggled(bool arg1);
    void on_chkKeyboardControl_toggled(bool checked);
    void on_chkHeightMapBorderShow_toggled(bool checked);
    void on_chkHeightMapInterpolationShow_toggled(bool checked);
    void on_chkHeightMapUse_clicked(bool checked);
    void on_chkHeightMapGridShow_toggled(bool checked);
    void on_txtHeightMapBorderX_valueChanged(double arg1);
    void on_txtHeightMapBorderWidth_valueChanged(double arg1);
    void on_txtHeightMapBorderY_valueChanged(double arg1);
    void on_txtHeightMapBorderHeight_valueChanged(double arg1);
    void on_txtHeightMapGridX_valueChanged(double arg1);
    void on_txtHeightMapGridY_valueChanged(double arg1);
    void on_txtHeightMapGridZBottom_valueChanged(double arg1);
    void on_txtHeightMapGridZTop_valueChanged(double arg1);
    void on_txtHeightMapInterpolationStepX_valueChanged(double arg1);
    void on_txtHeightMapInterpolationStepY_valueChanged(double arg1);
    void on_cmdHeightMapMode_toggled(bool checked);
    void on_cmdHeightMapCreate_clicked();
    void on_cmdHeightMapLoad_clicked();
    void on_cmdHeightMapBorderAuto_clicked();
    void on_cmdYPlus_pressed();
    void on_cmdYPlus_released();
    void on_cmdYMinus_pressed();
    void on_cmdYMinus_released();
    void on_cmdXPlus_pressed();
    void on_cmdXPlus_released();
    void on_cmdXMinus_pressed();
    void on_cmdXMinus_released();
    void on_cmdZPlus_pressed();
    void on_cmdZPlus_released();
    void on_cmdZMinus_pressed();
    void on_cmdZMinus_released();
    void on_cmdStop_clicked();
    void on_tblProgram_customContextMenuRequested(const QPoint &pos);
    void on_mnuViewWindows_aboutToShow();
    void on_mnuViewPanels_aboutToShow();
    void on_dockVisualizer_visibilityChanged(bool visible);

    void onSerialPortReadyRead();
    void onSerialPortError(QSerialPort::SerialPortError);
    void onTimerConnection();
    void onTimerStateQuery();
    void onTableInsertLine();
    void onTableDeleteLines();
    void onTableCellChanged(QModelIndex i1, QModelIndex i2);
    void onTableCurrentChanged(QModelIndex idx1, QModelIndex idx2);
    void onOverridingToggled(bool checked);
    void onOverrideChanged();
    void onActRecentFileTriggered();
    void onActSendFromLineTriggered();
    void onSlbSpindleValueUserChanged();
    void onSlbSpindleValueChanged();
    void onCboCommandReturnPressed();
    void onDockTopLevelChanged(bool topLevel);
    void onScroolBarAction(int action);
    void onScriptException(const QScriptValue &exception);

    void updateHeightMapInterpolationDrawer(bool reset = false);
    void placeVisualizerButtons();

protected:
    void showEvent(QShowEvent *se);
    void hideEvent(QHideEvent *he);
    void resizeEvent(QResizeEvent *re);
    void timerEvent(QTimerEvent *);
    void closeEvent(QCloseEvent *ce);
    void dragEnterEvent(QDragEnterEvent *dee);
    void dropEvent(QDropEvent *de);
    QMenu *createPopupMenu() override;

private:
    static const int BUFFERLENGTH = 127;
    static const int PROGRESSMINLINES = 10000;
    static const int PROGRESSSTEP = 1000;    

    enum SenderState {
        SenderUnknown = -1,
        SenderTransferring = 0,
        SenderPausing = 1,
        SenderPaused = 2,
        SenderStopping = 3,
        SenderStopped = 4,
        SenderChangingTool = 5
    };

    enum DeviceState {
        DeviceUnknown = -1,
        DeviceIdle = 1,
        DeviceAlarm = 2,
        DeviceRun = 3,
        DeviceHome = 4,
        DeviceHold0 = 5,
        DeviceHold1 = 6,
        DeviceQueue = 7,
        DeviceCheck = 8,
        DeviceDoor0 = 9,
        DeviceDoor1 = 10,
        DeviceDoor2 = 11,
        DeviceDoor3 = 12,
        DeviceJog = 13,
        DeviceSleep =14
    };

    // Ui
    Ui::frmMain *ui;

    QMap<DeviceState, QString> m_deviceStatuses;
    QMap<DeviceState, QString> m_statusCaptions;
    QMap<DeviceState, QString> m_statusBackColors;
    QMap<DeviceState, QString> m_statusForeColors;

    QMenu *m_tableMenu;
    QMessageBox* m_senderErrorBox;
#ifdef WINDOWS
    QWinTaskbarButton *m_taskBarButton;
    QWinTaskbarProgress *m_taskBarProgress;
#endif

    // Parsers
    GcodeViewParse m_viewParser;
    GcodeViewParse m_probeParser;

    // State
    SenderState m_senderState;
    DeviceState m_deviceState;

    // Visualizer drawers
    // TODO: Add machine table visualizer
    OriginDrawer *m_originDrawer;
    GcodeDrawer *m_codeDrawer;    
    GcodeDrawer *m_probeDrawer;
    GcodeDrawer *m_currentDrawer;
    ToolDrawer m_toolDrawer;
    HeightMapBorderDrawer m_heightMapBorderDrawer;
    HeightMapGridDrawer m_heightMapGridDrawer;
    HeightMapInterpolationDrawer m_heightMapInterpolationDrawer;
    SelectionDrawer m_selectionDrawer;
    MachineBoundsDrawer m_machineBoundsDrawer;

    // Table models
    GCodeTableModel m_programModel;
    GCodeTableModel m_probeModel;
    GCodeTableModel m_programHeightmapModel;
    GCodeTableModel *m_currentModel;
    HeightMapTableModel m_heightMapModel;

    // Serial port
    QSerialPort m_serialPort;

    // Queues
    QList<CommandAttributes> m_commands;
    QList<CommandQueue> m_queue;    

    // Forms
    frmSettings *m_settings;
    frmAbout m_frmAbout;

    // Filenames
    QString m_settingsFileName;
    QString m_programFileName;
    QString m_heightMapFileName;
    QString m_lastFolder;
    QStringList m_recentFiles;
    QStringList m_recentHeightmaps;

    // Timers
    QTimer m_timerConnection;
    QTimer m_timerStateQuery;
    QBasicTimer m_timerToolAnimation;
    QTime m_startTime;

    // Stored parser params
    QString m_storedParserStatus;

    // Flags
    bool m_programLoading;
    bool m_settingsLoading;
    bool m_fileChanged;
    bool m_heightMapChanged;

    bool m_homing;
    bool m_updateSpindleSpeed;
    bool m_updateParserStatus;

    bool m_reseting;
    bool m_resetCompleted;
    bool m_aborting;
    bool m_statusReceived;

    bool m_heightMapMode;

    // Indices
    int m_fileCommandIndex;
    int m_fileProcessedCommandIndex;
    int m_probeIndex;

    // Current values
    int m_lastDrawnLineIndex;

    // Keyboard
    bool m_absoluteCoordinates;
    bool m_storedKeyboardControl;

    // Spindle
    bool m_spindleCW;

    // Jog
    QVector3D m_jogVector;

    // Script
    QScriptEngine m_scriptEngine;
    ScriptVars m_storedVars;
    ScriptFunctions m_scriptFunctions;

    // Drag & drop
    QPoint m_mousePressPos;
    
    // Settings
    void preloadSettings();
    void loadSettings();
    void saveSettings();
    void applySettings();

    // Plugins
    void loadPlugins();

    // Communication
    void openPort();
    void grblReset();
    int sendCommand(QString command, int tableIndex = -1, bool showInConsole = true, bool wait = false);
    void sendCommands(QString commands, int tableIndex = -1);
    void sendNextFileCommands();
    QString evaluateCommand(QString command);

    // Parser
    void updateParser();
    void storeParserState();
    void restoreParserState();
    void restoreOffsets();
    void storeOffsetsVars(QString response);

    // Files/models
    void loadFile(QString fileName);
    void loadFile(QList<QString> data);
    bool saveChanges(bool heightMapMode);
    bool saveProgramToFile(QString fileName, GCodeTableModel *model);
    void loadHeightMap(QString fileName);
    bool saveHeightMap(QString fileName);
    void clearTable();
    void resetHeightmap();
    void newFile();
    void newHeightmap();

    // Ui
    void setupCoordsTextboxes();
    void updateControlsState();
    void updateLayouts();
    void updateRecentFilesMenu();
    void updateOverride(SliderBox *slider, int value, char command);
    void updateJogTitle();
    void addRecentFile(QString fileName);
    void addRecentHeightmap(QString fileName);
    QRectF borderRectFromTextboxes();
    QRectF borderRectFromExtremes();
    void updateHeightMapBorderDrawer();
    bool updateHeightMapGrid();
    void updateHeightMapGrid(double arg1);
    void resizeTableHeightMapSections();
    bool eventFilter(QObject *obj, QEvent *event);

    // Utility
    int bufferLength();
    bool dataIsFloating(QString data);
    bool dataIsEnd(QString data);
    bool dataIsReset(QString data);
    QTime updateProgramEstimatedTime(QList<LineSegment *> lines);
    QList<LineSegment *> subdivideSegment(LineSegment *segment);
    void jogStep();
    void jogContinuous();
    double toMetric(double value);
    double toInches(double value);
    bool compareCoordinates(double x, double y, double z);
    bool isGCodeFile(QString fileName);
    bool isHeightmapFile(QString fileName);
    int buttonSize();
    void setSenderState(SenderState state);
    void setDeviceState(DeviceState state);
    void completeTransfer();
    QString getLineInitCommands(int row);

    static bool actionLessThan(const QAction *a1, const QAction *a2);
    static bool actionTextLessThan(const QAction *a1, const QAction *a2);
    static QScriptValue importExtension(QScriptContext *context, QScriptEngine *engine);
};

typedef QMap<QString, QList<QKeySequence>> ShortcutsMap;

#endif // FRMMAIN_H
