// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

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

#include "tables/gcodetablemodel.h"
#include "tables/heightmaptablemodel.h"

#include "utils/interpolation.h"

#include "widgets/styledtoolbutton.h"
#include "widgets/sliderbox.h"

#include "frmsettings.h"
#include "frmabout.h"

#include "scriptvars.h"

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
    bool queue;
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

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

    Q_INVOKABLE void sendCommand(QString command, int tableIndex = -1, bool showInConsole = true, bool queue = false);
    Q_INVOKABLE void applySettings();    

    double toolZPosition();

signals:

    void responseReceived(QString command, int tableIndex, QString response);
    void settingsLoaded();
    void settingsAboutToSave();
    void settingsChanged();

private slots:
    void updateHeightMapInterpolationDrawer(bool reset = false);
    void placeVisualizerButtons();

    void onSerialPortReadyRead();
    void onSerialPortError(QSerialPort::SerialPortError);
    void onTimerConnection();
    void onTimerStateQuery();
    void onVisualizatorRotationChanged();
    void onScroolBarAction(int action);
    void onJogTimer();
    void onTableInsertLine();
    void onTableDeleteLines();
    void onActRecentFileTriggered();
    void onCboCommandReturnPressed();
    void onTableCurrentChanged(QModelIndex idx1, QModelIndex idx2);
    void onCmdUserClicked(bool checked);
    void onOverridingToggled(bool checked);
    void onOverrideChanged();
    void onActSendFromLineTriggered();
    void onSlbSpindleValueUserChanged();
    void onSlbSpindleValueChanged();
    void onDockTopLevelChanged(bool topLevel);

    void on_actFileExit_triggered();
    void on_cmdFileOpen_clicked();
    void on_cmdFit_clicked();
    void on_cmdFileSend_clicked();
    void onTableCellChanged(QModelIndex i1, QModelIndex i2);
    void on_actServiceSettings_triggered();
    void on_actFileOpen_triggered();
    void on_cmdCommandSend_clicked();
    void on_cmdHome_clicked();
    void on_cmdTouch_clicked();
    void on_cmdZeroXY_clicked();
    void on_cmdZeroZ_clicked();
    void on_cmdRestoreOrigin_clicked();
    void on_cmdReset_clicked();
    void on_cmdUnlock_clicked();
    void on_cmdSafePosition_clicked();
    void on_cmdSpindle_toggled(bool checked);
    void on_chkTestMode_clicked(bool checked);
    void on_cmdFilePause_clicked(bool checked);
    void on_cmdFileReset_clicked();
    void on_actFileNew_triggered();
    void on_cmdClearConsole_clicked();
    void on_actFileSaveAs_triggered();
    void on_actFileSave_triggered();
    void on_actFileSaveTransformedAs_triggered();
    void on_cmdTop_clicked();
    void on_cmdFront_clicked();
    void on_cmdLeft_clicked();
    void on_cmdIsometric_clicked();
    void on_actAbout_triggered();
    void on_grpOverriding_toggled(bool checked);
    void on_grpSpindle_toggled(bool checked);
    void on_grpJog_toggled(bool checked);
    void on_grpUserCommands_toggled(bool checked);
    void on_chkKeyboardControl_toggled(bool checked);
    void on_tblProgram_customContextMenuRequested(const QPoint &pos);
    void on_actRecentClear_triggered();
    void on_grpHeightMap_toggled(bool arg1);
    void on_chkHeightMapBorderShow_toggled(bool checked);
    void on_txtHeightMapBorderX_valueChanged(double arg1);
    void on_txtHeightMapBorderWidth_valueChanged(double arg1);
    void on_txtHeightMapBorderY_valueChanged(double arg1);
    void on_txtHeightMapBorderHeight_valueChanged(double arg1);
    void on_chkHeightMapGridShow_toggled(bool checked);
    void on_txtHeightMapGridX_valueChanged(double arg1);
    void on_txtHeightMapGridY_valueChanged(double arg1);
    void on_txtHeightMapGridZBottom_valueChanged(double arg1);
    void on_txtHeightMapGridZTop_valueChanged(double arg1);
    void on_cmdHeightMapMode_toggled(bool checked);
    void on_chkHeightMapInterpolationShow_toggled(bool checked);
    void on_cmdHeightMapLoad_clicked();
    void on_txtHeightMapInterpolationStepX_valueChanged(double arg1);
    void on_txtHeightMapInterpolationStepY_valueChanged(double arg1);
    void on_chkHeightMapUse_clicked(bool checked);
    void on_cmdHeightMapCreate_clicked();
    void on_cmdHeightMapBorderAuto_clicked();
    void on_cmdFileAbort_clicked();
    void on_cmdSpindle_clicked(bool checked);   
    void on_mnuViewWindows_aboutToShow();
    void on_mnuViewPanels_aboutToShow();

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

    void on_dockVisualizer_visibilityChanged(bool visible);

    void on_actViewLockWindows_toggled(bool checked);

protected:
    void showEvent(QShowEvent *se);
    void hideEvent(QHideEvent *he);
    void resizeEvent(QResizeEvent *re);
    void timerEvent(QTimerEvent *);
    void closeEvent(QCloseEvent *ce);
    void dragEnterEvent(QDragEnterEvent *dee);
    void dropEvent(QDropEvent *de);
    void mousePressEvent(QMouseEvent *e);
    QMenu *createPopupMenu() override;

private:
    static const int BUFFERLENGTH = 127;

    Ui::frmMain *ui;

    GcodeViewParse m_viewParser;
    GcodeViewParse m_probeParser;

    OriginDrawer *m_originDrawer;

    GcodeDrawer *m_codeDrawer;    
    GcodeDrawer *m_probeDrawer;
    GcodeDrawer *m_currentDrawer;

    ToolDrawer m_toolDrawer;
    HeightMapBorderDrawer m_heightMapBorderDrawer;
    HeightMapGridDrawer m_heightMapGridDrawer;
    HeightMapInterpolationDrawer m_heightMapInterpolationDrawer;

    SelectionDrawer m_selectionDrawer;

    GCodeTableModel m_programModel;
    GCodeTableModel m_probeModel;
    GCodeTableModel m_programHeightmapModel;

    HeightMapTableModel m_heightMapModel;

    bool m_programLoading;
    bool m_settingsLoading;

    QSerialPort m_serialPort;

    frmSettings *m_settings;
    frmAbout m_frmAbout;

    QString m_settingsFileName;
    QString m_programFileName;
    QString m_heightMapFileName;
    QString m_lastFolder;

    bool m_fileChanged;
    bool m_heightMapChanged;

    QTimer m_timerConnection;
    QTimer m_timerStateQuery;
    QBasicTimer m_timerToolAnimation;

    QStringList m_status;
    QStringList m_statusCaptions;
    QStringList m_statusBackColors;
    QStringList m_statusForeColors;

#ifdef WINDOWS
    QWinTaskbarButton *m_taskBarButton;
    QWinTaskbarProgress *m_taskBarProgress;
#endif

    QMenu *m_tableMenu;
    QList<CommandAttributes> m_commands;
    QList<CommandQueue> m_queue;
    QTime m_startTime;

    QMessageBox* m_senderErrorBox;

    // Stored origin
    double m_storedX;
    double m_storedY;
    double m_storedZ;
    QString m_storedCS;
    QString m_storedParserStatus;

    // Console window
    int m_storedConsoleMinimumHeight;
    int m_storedConsoleHeight;
    int m_consolePureHeight;

    // Flags
    bool m_homing;
    bool m_updateSpindleSpeed;
    bool m_updateParserStatus;
    bool m_updateFeed;

    bool m_reseting;
    bool m_resetCompleted;
    bool m_aborting;
    bool m_statusReceived;

    bool m_processingFile;
    bool m_transferCompleted;
    bool m_fileEndSent;

    bool m_heightMapMode;
    bool m_cellChanged;

    // Indices
    int m_fileCommandIndex;
    int m_fileProcessedCommandIndex;
    int m_probeIndex;

    // Current values
    int m_lastDrawnLineIndex;
    int m_lastGrblStatus;
    double m_originalFeed;

    // Keyboard
    bool m_keyPressed;
    bool m_jogBlock;
    bool m_absoluteCoordinates;
    bool m_storedKeyboardControl;

    // Spindle
    bool m_spindleCW;
    bool m_spindleCommandSpeed;

    // Jog
    QVector3D m_jogVector;

    // Recent files
    QStringList m_recentFiles;
    QStringList m_recentHeightmaps;

    // Script
    QScriptEngine m_scriptEngine;
    ScriptVars m_storedVars;

    // Drag & drop
    QPoint m_mousePressPos;

    void loadFile(QString fileName);
    void loadFile(QList<QString> data);
    void clearTable();
    void preloadSettings();
    void loadSettings();
    void saveSettings();
    bool saveChanges(bool heightMapMode);
    void updateControlsState();
    void openPort();
    QString evaluateCommand(QString command);
    void grblReset();
    int bufferLength();
    void sendNextFileCommands();
    void updateParser();
    bool dataIsFloating(QString data);
    bool dataIsEnd(QString data);
    bool dataIsReset(QString data);

    QTime updateProgramEstimatedTime(QList<LineSegment *> lines);
    bool saveProgramToFile(QString fileName, GCodeTableModel *model);

    bool eventFilter(QObject *obj, QEvent *event);
    bool keyIsMovement(int key);
    void updateLayouts();
    void updateRecentFilesMenu();
    void addRecentFile(QString fileName);
    void addRecentHeightmap(QString fileName);
    double toMetric(double value);

    QRectF borderRectFromTextboxes();
    QRectF borderRectFromExtremes();
    void updateHeightMapBorderDrawer();
    bool updateHeightMapGrid();
    void loadHeightMap(QString fileName);
    bool saveHeightMap(QString fileName);

    GCodeTableModel *m_currentModel;
    QList<LineSegment *> subdivideSegment(LineSegment *segment);
    void resizeTableHeightMapSections();
    void updateHeightMapGrid(double arg1);
    void resetHeightmap();
    void storeParserState();
    void restoreParserState();
    void storeOffsets();
    void restoreOffsets();
    void storeOffsetsVars(QString response);
    bool isGCodeFile(QString fileName);
    bool isHeightmapFile(QString fileName);
    bool compareCoordinates(double x, double y, double z);
    void updateOverride(SliderBox *slider, int value, char command);
    void jogStep();
    void updateJogTitle();
    void setupCoordsTextboxes();

    void loadPlugins();

    static bool actionLessThan(const QAction *a1, const QAction *a2);
    static bool actionTextLessThan(const QAction *a1, const QAction *a2);
};

typedef QMap<QString, QList<QKeySequence>> ShortcutsMap;

#endif // FRMMAIN_H
