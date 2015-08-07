#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSettings>
#include <QTimer>
#include <QBasicTimer>
#include <QStringList>
#include <QList>
#include "gcodeviewparse.h"
#include "gcodedrawer.h"
#include "tooldrawer.h"
#include "gcodetablemodel.h"
#include "frmsettings.h"

namespace Ui {
class frmMain;
}

struct CommandAttributes {
    int length;
    int consoleIndex;
    int tableIndex;
    QString command;
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
    void on_cmdSpindle_clicked(bool checked);
    void on_txtSpindleSpeed_valueChanged(const QString &arg1);
    void on_txtSpindleSpeed_editingFinished();
    void on_sliSpindleSpeed_valueChanged(int value);
    void on_cmdYPlus_clicked();
    void on_cmdYMinus_clicked();
    void on_cmdXPlus_clicked();
    void on_cmdXMinus_clicked();
    void on_cmdZPlus_clicked();
    void on_cmdZMinus_clicked();
    void on_chkTestMode_clicked();
    void on_cmdFilePause_clicked(bool checked);
    void on_cmdFileReset_clicked();


    void on_actFileNew_triggered();

protected:
    void showEvent(QShowEvent *se);
    void resizeEvent(QResizeEvent *re);
    void timerEvent(QTimerEvent *);

private:
    const int BUFFERLENGTH = 127;

    Ui::frmMain *ui;
    GcodeViewParse m_viewParser;
    GcodeDrawer *m_codeDrawer;
    ToolDrawer m_toolDrawer;
    GCodeTableModel m_tableModel;
    bool m_programLoading;
    QSerialPort m_serialPort;
    frmSettings m_frmSettings;
    QString m_settingsFileName;
    QTimer m_timerConnection;
    QTimer m_timerStateQuery;
    QBasicTimer m_timerToolAnimation;

    QStringList m_status = {"Idle", "Alarm", "Run", "Home", "Hold", "Queue", "Check"};
    QStringList m_statusCaptions = {"Готов", "Тревога", "Работа", "Домой", "Пауза", "Очередь", "Проверка"};
    QStringList m_statusBackColors = {"palette(button)", "red", "lime", "lime", "yellow", "yellow", "palette(button)"};
    QStringList m_statusForeColors = {"palette(text)", "white", "black", "black", "black", "black", "palette(text)"};

    double m_storedX = 0;
    double m_storedY = 0;
    double m_storedZ = 0;
    double m_safeZ = 0;

    bool m_settingZeroXY = false;
    bool m_settingZeroZ = false;
    bool m_homing = false;
    bool m_programSpeed = false;

    int m_lastDrawnLineIndex;

    QList<CommandAttributes> m_commands;
    QList<QString> m_queue;

    bool m_transferringFile = false;
    bool m_transferCompleted = false;
    int m_fileCommandIndex;
    bool m_showAllCommands = false;

    void processFile(QString fileName);
    void clearTable();
    void loadSettings();
    void saveSettings();
    void updateControlsState();
    void openPort();
    void sendCommand(QString command, int tableIndex = 0);
    void grblReset();
    int bufferLength();
    void sendNextFileCommands();
    void applySettings();
};

#endif // FRMMAIN_H
