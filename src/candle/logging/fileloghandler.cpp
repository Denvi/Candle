// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QMutex>
#include <QStandardPaths>

static constexpr int INTERVAL = 500;

static QtMessageHandler originalHandler;
static QString logFileName;
static QElapsedTimer intervalTimer;
static QTimer pendingTimer;
static QStringList pendingMessages;
static QMutex mutex;

static QMap<QtMsgType, QString> messageTypeMap = {
    {QtMsgType::QtCriticalMsg, "CRITICAL"},
    {QtMsgType::QtDebugMsg, "DEBUG"},
    {QtMsgType::QtFatalMsg, "FATAL"},
    {QtMsgType::QtInfoMsg, "INF"},
    {QtMsgType::QtSystemMsg, "SYS"},
    {QtMsgType::QtWarningMsg, "WARN"}
};

static void writeToFile()
{
    QMutexLocker lock(&mutex);

    if (pendingMessages.isEmpty())
        return;

    QFile file(logFileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << pendingMessages.join('\n') << Qt::endl;
        file.close();
    }

    pendingMessages.clear();
}

static void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString message = QString("[%1] [%2] [%3] %4")
        .arg(timestamp)
        .arg(messageTypeMap[type])
        .arg(context.category ? context.category : "unknown")
        .arg(msg);

    {
        QMutexLocker lock(&mutex);
        pendingMessages.append(message);
    }

    if (!intervalTimer.isValid() || intervalTimer.hasExpired(INTERVAL)) {
        pendingTimer.stop();
        intervalTimer.start();
        writeToFile();
    } else {
        pendingTimer.start();
    }

    if (originalHandler)
        originalHandler(type, context, msg);
}

void installFileLogHandler()
{
    auto logDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    logFileName = logDir + "/candle.log";

    QDir().mkpath(logDir);
    QFile file(logFileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        file.close();
    }

    pendingTimer.setSingleShot(true);
    pendingTimer.setInterval(INTERVAL * 2);
    pendingTimer.connect(&pendingTimer, &QTimer::timeout, [] {
        writeToFile();
        intervalTimer.start();
    });

    originalHandler = qInstallMessageHandler(logToFile);
}