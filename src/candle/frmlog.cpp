// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QFileSystemWatcher>
#include <QTextStream>
#include <QStandardPaths>
#include "frmlog.h"
#include "ui_frmlog.h"

frmLog::frmLog(QWidget *parent) : QFrame(parent), ui(new Ui::frmLog)
{
    ui->setupUi(this);

    m_logFileName = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/candle.log";
    loadLogFile();

    QFileSystemWatcher *watcher = new QFileSystemWatcher(this);
    watcher->addPath(m_logFileName);
    connect(watcher, &QFileSystemWatcher::fileChanged, this, &frmLog::onLogFileChanged);
}

frmLog::~frmLog()
{
    delete ui;
}

void frmLog::onLogFileChanged(const QString &path)
{
    if (path == m_logFileName)
    {
        loadLogFile();
    }
}

void frmLog::loadLogFile()
{
    QFile file(m_logFileName);

    if (!file.exists())
        return;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString content = stream.readAll();
        ui->txtLog->setPlainText(content);

        QTextCursor cursor = ui->txtLog->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->txtLog->setTextCursor(cursor);
    }
}
