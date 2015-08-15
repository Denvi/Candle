// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

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
#include <QtWinExtras/QtWinExtras>
#include "gcodeviewparse.h"
#include "gcodedrawer.h"
#include "tooldrawer.h"
#include "gcodetablemodel.h"
#include "frmsettings.h"
#include "frmabout.h"
#include "styledtoolbutton.h"
#include "shobjidl.h"

namespace Ui {
class frmMain;
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
};

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();    

    double toolZPosition();

private slots:
    void onSerialPortReadyRead();
    void onSerialPortError(QSerialPort::SerialPortError);
    void onTimerConnection();
    void onTimerStateQuery();
    void onCmdJogStepClicked();
    void onVisualizatorRotationChanged();
    void onScroolBarAction(int action);
    void onJogTimer();
//    void onClearJogBlock();

    void on_actFileExit_triggered();
    void on_cmdFileOpen_clicked();        
    void on_cmdFit_clicked();
    void on_cmdFileSend_clicked();
    void on_tblProgram_cellChanged(QModelIndex i1, QModelIndex i2);
    void on_actServiceSettings_triggered();
    void on_actFileOpen_triggered();
    void on_txtCommand_returnPressed();
    void on_cmdCommandSend_clicked();
    void on_cmdHome_clicked();
    void on_cmdTouch_clicked();
    void on_cmdZeroXY_clicked();
    void on_cmdZeroZ_clicked();
    void on_cmdReturnXY_clicked();
    void on_cmdReset_clicked();
    void on_cmdUnlock_clicked();
    void on_cmdTopZ_clicked();
    void on_cmdSpindle_toggled(bool checked);
    void on_txtSpindleSpeed_valueChanged(const QString &arg1);
    void on_txtSpindleSpeed_editingFinished();
    void on_sliSpindleSpeed_valueChanged(int value);
    void on_cmdYPlus_clicked();
    void on_cmdYMinus_clicked();
    void on_cmdXPlus_clicked();
    void on_cmdXMinus_clicked();
    void on_cmdZPlus_clicked();
    void on_cmdZMinus_clicked();
    void on_chkTestMode_clicked(bool checked);
    void on_cmdFilePause_clicked(bool checked);
    void on_cmdFileReset_clicked();
    void on_actFileNew_triggered();
    void on_cmdClearConsole_clicked();
    void on_actFileSaveAs_triggered();
    void on_actFileSave_triggered();
    void on_cmdTop_clicked();
    void on_cmdFront_clicked();
    void on_cmdLeft_clicked();
    void on_cmdIsometric_clicked();
    void on_actAbout_triggered();
    void on_txtFeed_editingFinished();
    void on_sliFeed_valueChanged(int value);
    void on_chkFeedOverride_toggled(bool checked);
    void on_grpFeed_toggled(bool checked);
    void on_grpSpindle_toggled(bool checked);
    void on_grpJog_toggled(bool checked);

    void on_chkKeyboardControl_toggled(bool checked);

protected:
    void showEvent(QShowEvent *se);
    void hideEvent(QHideEvent *he);
    void resizeEvent(QResizeEvent *re);
    void timerEvent(QTimerEvent *);
    void closeEvent(QCloseEvent *ce);

private:
    const int BUFFERLENGTH = 126;

    Ui::frmMain *ui;
    GcodeViewParse m_viewParser;
    GcodeDrawer *m_codeDrawer;
    ToolDrawer m_toolDrawer;
    GCodeTableModel m_tableModel;
    bool m_programLoading;
    QSerialPort m_serialPort;
    frmSettings m_frmSettings;
    frmAbout m_frmAbout;
    QString m_settingsFileName;
    QString m_programFileName;
    QTimer m_timerConnection;
    QTimer m_timerStateQuery;
    QBasicTimer m_timerToolAnimation;

    QStringList m_status;
    QStringList m_statusCaptions;
    QStringList m_statusBackColors;
    QStringList m_statusForeColors;

    QWinTaskbarButton *m_taskBarButton;
    QWinTaskbarProgress *m_taskBarProgress;

    double m_storedX = 0;
    double m_storedY = 0;
    double m_storedZ = 0;
    double m_safeZ = 0;
    double m_rapidSpeed = 0;

    bool m_settingZeroXY = false;
    bool m_settingZeroZ = false;
    bool m_homing = false;
    bool m_programSpeed = false;
    double m_arcPrecision;

    int m_lastDrawnLineIndex;

    QList<CommandAttributes> m_commands;
    QList<CommandQueue> m_queue;

    QTime m_startTime;
    bool m_transferringFile = false;
    bool m_transferCompleted = false;
    int m_fileCommandIndex;
    int m_fileProcessedCommandIndex;
    bool m_showAllCommands = false;

    bool m_reseting = false;
    bool m_resetCompleted = true;

    bool m_keyPressed = false;
    bool m_jogBlock = false;
    bool m_absoluteCoordinates;
    bool m_storedKeyboardControl;      

    void processFile(QString fileName);
    void clearTable();
    void loadSettings();
    void saveSettings();
    void updateControlsState();
    void openPort();
    void sendCommand(QString command, int tableIndex = -1);
    void grblReset();
    int bufferLength();
    void sendNextFileCommands();
    void applySettings();
    QTime updateProgramEstimatedTime(QList<LineSegment *> lines);
    bool saveProgramToFile(QString fileName);
    void placeVisualizerButtons();
    bool dataIsEnd(QString data);

    bool eventFilter(QObject *obj, QEvent *event);
    //    bool buttonLessThan(StyledToolButton *b1, StyledToolButton *b2);
    void blockJogForRapidMovement();
    bool keyIsMovement(int key);
};

#endif // FRMMAIN_H
