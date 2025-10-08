// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QFileSystemWatcher>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QScriptEngineDebugger>
#include <QMainWindow>
#include <QAction>
#include "frmscript.h"
#include "ui_frmscript.h"
#include "loggingcategories.h"

frmScript::frmScript(QWidget *parent) : QFrame(parent), engines(this), ui(new Ui::frmScript)
{
    ui->setupUi(this);

    m_changed = false;
    m_fileName = "";

    // connect(&engines.js()->console(), &Console::message, this, &frmScript::logSent);
    // connect(&engines.js()->console(), &Console::message, this, &frmScript::logSent);
}

frmScript::~frmScript()
{
    delete ui;
}

void frmScript::addLog(const QString &type, const QString &msg)
{
    qDebug() << type << msg;
}

void frmScript::logSent(Console::Level level, const QString &msg)
{
    switch (level) {
    case Console::Level::Log:
        this->addLog("LOG", msg);
        qDebug() << msg;

        break;
    case Console::Level::Warn:
        this->addLog("WARN", msg);
        qWarning() << msg;

        break;
    case Console::Level::Error:
        this->addLog("ERROR", msg);
        qCritical() << msg;

        break;
    }
}

void frmScript::on_txtScript_textChanged()
{
    m_changed = true;
}

void frmScript::on_cmdNew_clicked()
{
    if (!saveChanges())
        return;

    ui->txtScript->clear();
    m_changed = false;
}

void frmScript::on_cmdOpen_clicked()
{
    if (!saveChanges())
        return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QString(), tr("Script files (*.js)"));

    if (fileName != "")
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, this->windowTitle(), tr("Can't open file:\n") + fileName);
            return;
        }

        QTextStream textStream(&file);
        ui->txtScript->setPlainText(textStream.readAll());
        m_changed = false;
    }
}

void frmScript::on_cmdSave_clicked()
{
    saveFile();
}

void frmScript::on_cmdStart_clicked()
{
    QScriptEngine se;

    emit beforeScriptStart(se);

    QString script = ui->txtScript->toPlainText();
    int engineIndex = ui->comboEngine->currentIndex();

    qDebug() << "`" + script + "`";

    switch (engineIndex) {
        case 0: // JS classic
        {
            auto sv = se.evaluate(script);
            if (sv.isError()) {
                qCritical(scriptLogCategory) << "Error evaluating script" << sv.toString() << se.uncaughtExceptionBacktrace();
            }
            break;
        }
        case 1: // JS new
            engines.js()->execute(script);
            return;
        case 2: // LUA new
            engines.lua()->execute(script);
            return;
        case 4: // autodetect new
            auto js = engines.js();
            auto lua = engines.lua();
            if (js->supported(script)) {
                js->execute(script);
            } else if (lua->supported(script)) {
                lua->execute(script);
            } else {
                qCritical(scriptLogCategory) << "No suitable engine found for the script";
            }
            return;
    }

}

void frmScript::on_cmdDebug_clicked()
{
    QScriptEngine se;
    QScriptEngineDebugger sd(this);

    sd.attachTo(&se);
    sd.standardWindow()->setWindowIcon(this->windowIcon());
    sd.action(QScriptEngineDebugger::InterruptAction)->trigger();

    emit beforeScriptStart(se);

    auto sv = se.evaluate(ui->txtScript->toPlainText());

    if (sv.isError()) {
        qCritical(scriptLogCategory) << "Error evaluating script" << sv.toString() << se.uncaughtExceptionBacktrace();
    }
}

bool frmScript::saveChanges()
{
    if (m_changed)
    {
        int res = QMessageBox::warning(this, this->windowTitle(), tr("Script was changed. Save?"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (res == QMessageBox::Cancel)
            return false;

        if (res == QMessageBox::No)
            return true;

        else if (res == QMessageBox::Yes && saveFile())
            return true;

        return false;
    }

    return true;
}

bool frmScript::saveFile()
{
    QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), m_lastFolder, tr("Script files (*.js)")));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        QDir dir;

        if (file.exists())
            dir.remove(file.fileName());
        if (!file.open(QIODevice::WriteOnly))
            return false;

        QTextStream textStream(&file);
        textStream << ui->txtScript->toPlainText();

        file.close();

        m_fileName = fileName;
        m_changed = false;
        return true;
    }

    return false;
}
