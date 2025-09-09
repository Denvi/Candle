// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

QtMessageHandler originalHandler;
QString logFileName;

QMap<QtMsgType, QString> messageTypeMap = {
    {QtMsgType::QtCriticalMsg, "CRITICAL"},
    {QtMsgType::QtDebugMsg, "DEBUG"},
    {QtMsgType::QtFatalMsg, "FATAL"},
    {QtMsgType::QtInfoMsg, "INF"},
    {QtMsgType::QtSystemMsg, "SYS"},
    {QtMsgType::QtWarningMsg, "WARN"}
};

void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString message = QString("[%1] [%2] [%3] %6")
        .arg(timestamp)
        .arg(messageTypeMap[type])
        .arg(context.category)
        .arg(msg);

    QFile file(logFileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << message << Qt::endl;
        file.close();
    }

    if (originalHandler)
        originalHandler(type, context, msg);
}

void installFileLogHandler()
{
    logFileName = qApp->applicationDirPath() + "/candle.log";

    QFile file(logFileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        file.close();
    }

    originalHandler = qInstallMessageHandler(logToFile);
}