#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAction>
#include "scriptprogram.h"

class frmMain;

class ScriptApp: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int bufferLength READ bufferLength)
    Q_PROPERTY(int commandsLength READ commandsLength)
    Q_PROPERTY(int queueLength READ queueLength)
    Q_PROPERTY(int buttonSize READ buttonSize)
    Q_PROPERTY(QWidget* window READ window)
    Q_PROPERTY(int senderState READ senderState)
    Q_PROPERTY(int deviceState READ deviceState)
    Q_PROPERTY(int deviceState READ deviceState)
    Q_PROPERTY(ScriptProgram *program READ scriptProgram)

public:
    ScriptApp(frmMain *f);

public slots:
    void sendCommands(QString commands, int index = -100);
    void sendCommands(QStringList commands, int index = -100);
    void sendCommand(QString command, int index = -100, bool showInConsole = true, bool direct = false);
    void waitResponses();

    void storeParserState();
    void restoreParserState();

    bool newFile();
    bool loadFile(QString fileName);
    bool loadFile(QStringList data);
    bool saveFile();
    bool saveFile(QString fileName);

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
    ScriptProgram *m_scriptProgram;

    int bufferLength();
    int commandsLength();
    int queueLength();
    int buttonSize();
    QWidget* window();
    int senderState();
    int deviceState();
    ScriptProgram *scriptProgram();
};