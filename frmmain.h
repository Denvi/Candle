#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSettings>
#include <QTimer>
#include "gcodeviewparse.h"
#include "gcodedrawer.h"
#include "tooldrawer.h"
#include "gcodetablemodel.h"
#include "frmsettings.h"

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();    

private slots:
    void onSerialPortReadyRead();
    void onSerialPortError(QSerialPort::SerialPortError);
    void onTimerConnection();

    void on_actFileExit_triggered();
    void on_cmdFileOpen_clicked();        
    void on_cmdFit_clicked();
    void on_cmdFileSend_clicked();
    void on_tblProgram_cellChanged(QModelIndex i1, QModelIndex i2);
    void on_cmdFileNew_clicked();
    void on_actServiceSettings_triggered();


    void on_cmdCommandSend_clicked();

    void on_txtCommand_returnPressed();

protected:
    void showEvent(QShowEvent *se);
    void resizeEvent(QResizeEvent *re);

private:
    Ui::frmMain *ui;
    GcodeViewParse m_viewParser;
    GcodeDrawer m_codeDrawer;
    ToolDrawer m_toolDrawer;
    GCodeTableModel m_tableModel;
    bool m_programLoading;
    QSerialPort m_serialPort;
    frmSettings m_frmSettings;
    QString m_settingsFileName;
    QTimer m_timerConnection;

    void processFile(QString fileName);
    void clearTable();
    void loadSettings();
    void saveSettings();
};

#endif // FRMMAIN_H
