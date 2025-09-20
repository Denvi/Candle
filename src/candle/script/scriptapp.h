#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAction>
#include "scriptprogram.h"
#include "scriptdevice.h"
#include "scriptsender.h"

class frmMain;

class ScriptApp: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int buttonSize READ buttonSize)
    Q_PROPERTY(QWidget* window READ window)

    Q_PROPERTY(ScriptProgram *program READ program)
    Q_PROPERTY(ScriptDevice *device READ device)
    Q_PROPERTY(ScriptSender *sender READ sender)

public slots:
    bool newFile();
    bool loadFile(QString fileName);
    bool loadFile(QStringList data);
    bool saveFile();
    bool saveFile(QString fileName);
    void addAction(QAction *action);
    void removeAction(QAction *action);

signals:
    void settingsAboutToLoad();
    void settingsLoaded();
    void settingsAboutToSave();
    void settingsSaved();
    void settingsAboutToShow();
    void settingsAccepted();
    void settingsRejected();
    void settingsSetByDefault();
    void pluginsLoaded();

public:
    ScriptApp(frmMain *f);

    ScriptProgram* program();
    ScriptDevice* device();
    ScriptSender* sender();

private:
    frmMain *m_frmMain;
    ScriptProgram *m_scriptProgram;
    ScriptDevice *m_scriptDevice;
    ScriptSender *m_scriptSender;

    int buttonSize();
    QWidget* window();
};