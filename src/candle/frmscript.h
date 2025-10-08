// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#pragma once
#include <QFrame>
#include <QScriptEngine>
#include "enginecontainer.h"

namespace Ui {
class frmScript;
}

class frmScript : public QFrame
{
    Q_OBJECT

public:
    explicit frmScript(QWidget *parent = 0);
    ~frmScript();

signals:
    void beforeScriptStart(QScriptEngine &engine);

private slots:
    void on_cmdNew_clicked();
    void on_cmdOpen_clicked();
    void on_cmdSave_clicked();
    void on_cmdStart_clicked();
    void on_cmdDebug_clicked();
    void on_txtScript_textChanged();

private:
    Ui::frmScript *ui;
    EngineContainer engines;

    bool m_changed;
    QString m_fileName;
    QString m_lastFolder;

    bool saveChanges();
    bool saveFile();
    void logSent(Console::Level level, const QString &msg);
    void addLog(const QString &type, const QString &msg);
};
