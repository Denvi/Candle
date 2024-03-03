#ifndef SCRIPTFUNCTIONS_H
#define SCRIPTFUNCTIONS_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAction>

class frmMain;

class ScriptFunctions: public QObject
{
    Q_OBJECT
public:
    ScriptFunctions(QObject *parent = 0);
    
    void setFrmMain(frmMain *f);
    frmMain *getFrmMain();

public slots:
    void sendCommands(QString commands, int index = -100);
    int sendCommand(QString command, int index = -100, bool showInConsole = true);
    void sendRealtimeCommand(QChar command);
    
    void newFile();
    void loadFile(QString fileName);
    void loadFile(QVariantList data);
    bool saveFile();
    void saveFile(QString fileName);
    void debug(QString text);
    void console(QString text);

    int bufferLength();
    int commandsLength();
    int queueLength();

    void testDebug();

    int buttonSize();
    void addAction(QAction *action);
    void removeAction(QAction *action);    

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

private:
    frmMain *m_frmMain;
};

#endif
