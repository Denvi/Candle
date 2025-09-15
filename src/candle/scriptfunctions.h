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
    Q_PROPERTY(int bufferLength READ bufferLength)
    Q_PROPERTY(int commandsLength READ commandsLength)
    Q_PROPERTY(int queueLength READ queueLength)
    Q_PROPERTY(int buttonSize READ buttonSize)
    Q_PROPERTY(QWidget* window READ window)
    Q_PROPERTY(int senderState READ senderState)
    Q_PROPERTY(int deviceState READ deviceState)

public:
    ScriptFunctions(QObject *parent = 0);

    void setFrmMain(frmMain *f);
    frmMain *getFrmMain();

public slots:
    void sendCommands(QString commands, int index = -100);
    void sendCommands(QStringList commands, int index = -100);
    void sendCommand(QString command, int index = -100, bool showInConsole = true, bool direct = false);
    void waitResponses();

    void storeParserState();
    void restoreParserState();

    void newFile();
    void loadFile(QString fileName);
    void loadFile(QVariantList data);
    bool saveFile();
    void saveFile(QString fileName);

    void addAction(QAction *action);
    void removeAction(QAction *action);

    void loadProgram(QStringList program);

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

    int bufferLength();
    int commandsLength();
    int queueLength();
    int buttonSize();
    QWidget* window();
    int senderState();
    int deviceState();
};

#endif