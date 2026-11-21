// This file is a part of "Candle" application.

#ifndef AUTOMATIONTOOLS_H
#define AUTOMATIONTOOLS_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QWidgetList>

#include <functional>

class frmMain;
class QWidget;
class QAction;

// Implements the MCP tools exposed to AI agents. Accesses frmMain internals
// as a friend; all UI work runs on the GUI thread (server is single-threaded).
class AutomationTools : public QObject
{
    Q_OBJECT

public:
    AutomationTools(frmMain *mainWindow, bool allowMotion, QObject *parent = nullptr);

    // Tool descriptors for MCP tools/list.
    QJsonArray toolList() const;

    // Executes MCP tools/call. The callback receives the result content array
    // and an error flag. It may be invoked asynchronously when the tool waits
    // for a device response; the server guarantees one call at a time.
    using ResultCallback = std::function<void (const QJsonArray &content, bool isError)>;
    void call(const QString &tool, const QJsonObject &args, ResultCallback done);

private slots:
    void onStatusReceived(QString status);

private:
    // Helpers
    static QJsonObject toolDesc(const QString &name, const QString &desc,
        const QJsonObject &props, const QStringList &required = QStringList());
    static QJsonArray textContent(const QString &text);

    QString deviceStateName(int state) const;
    QString senderStateName(int state) const;

    QWidget *findWidget(const QString &objectName) const;
    QAction *findAction(const QString &objectName) const;

    bool isConnected() const;
    bool deviceReady() const;

    // Open dialog/message windows (excluding Qt internal popups and windows
    // kept "visible" via WA_DontShowOnScreen).
    static QWidgetList openDialogs();
    static QJsonArray openDialogsInfo();

    int consoleLineCount() const;
    // Collects console output until the predicate sees a line or timeout.
    void waitForResponse(int baseLine, int timeoutMs,
        std::function<bool (const QString &line)> isLast,
        std::function<void (const QStringList &lines, bool responded)> done);

    QJsonObject machineStateObject() const;
    QJsonObject programSummaryObject() const;

    void runGcode(const QStringList &commands, int waitMs, ResultCallback done);

    frmMain *m_main;
    bool m_allowMotion;
    QString m_lastStatus;
};

#endif // AUTOMATIONTOOLS_H
