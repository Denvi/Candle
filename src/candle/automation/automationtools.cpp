// This file is a part of "Candle" application.

#include "automationtools.h"

#include "../frmmain.h"
#include "../ui_frmmain.h"
#include "../connections/connection.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QBuffer>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QDoubleSpinBox>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QOpenGLWidget>
#include <QPainter>
#include <QPlainTextEdit>
#include <QScreen>
#include <QScrollBar>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>
#include <QElapsedTimer>
#include <QWindow>

// ---------------------------------------------------------------------------
// Construction and signals
// ---------------------------------------------------------------------------

AutomationTools::AutomationTools(frmMain *mainWindow, bool allowMotion, QObject *parent) :
    QObject(parent),
    m_main(mainWindow),
    m_allowMotion(allowMotion)
{
    connect(m_main, &frmMain::statusReceived, this, &AutomationTools::onStatusReceived);
}

void AutomationTools::onStatusReceived(QString status)
{
    m_lastStatus = status;
}

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------

QJsonObject AutomationTools::toolDesc(const QString &name, const QString &desc,
    const QJsonObject &props, const QStringList &required)
{
    QJsonObject tool;
    tool["name"] = name;
    tool["description"] = desc;

    QJsonObject schema;
    schema["type"] = QLatin1String("object");
    schema["properties"] = props;
    if (!required.isEmpty()) {
        QJsonArray req;
        foreach (const QString &r, required) req.append(r);
        schema["required"] = req;
    }
    tool["inputSchema"] = schema;

    return tool;
}

static QJsonObject textItem(const QString &text)
{
    QJsonObject item;
    item["type"] = QLatin1String("text");
    item["text"] = text;
    return item;
}

QJsonArray AutomationTools::textContent(const QString &text)
{
    QJsonArray content;
    content.append(textItem(text));
    return content;
}

QString AutomationTools::deviceStateName(int state) const
{
    switch (state) {
    case frmMain::DeviceIdle: return "Idle";
    case frmMain::DeviceAlarm: return "Alarm";
    case frmMain::DeviceRun: return "Run";
    case frmMain::DeviceHome: return "Home";
    case frmMain::DeviceHold0: return "Hold:paused";
    case frmMain::DeviceHold1: return "Hold:door";
    case frmMain::DeviceQueue: return "Queue";
    case frmMain::DeviceCheck: return "Check";
    case frmMain::DeviceDoor0: return "Door:0";
    case frmMain::DeviceDoor1: return "Door:1";
    case frmMain::DeviceDoor2: return "Door:2";
    case frmMain::DeviceDoor3: return "Door:3";
    case frmMain::DeviceJog: return "Jog";
    case frmMain::DeviceSleep: return "Sleep";
    default: return "Unknown";
    }
}

QString AutomationTools::senderStateName(int state) const
{
    switch (state) {
    case frmMain::SenderTransferring: return "Transferring";
    case frmMain::SenderPausing: return "Pausing";
    case frmMain::SenderPaused: return "Paused";
    case frmMain::SenderStopping: return "Stopping";
    case frmMain::SenderStopped: return "Stopped";
    case frmMain::SenderChangingTool: return "ChangingTool";
    default: return "Unknown";
    }
}

QWidget *AutomationTools::findWidget(const QString &objectName) const
{
    if (objectName.isEmpty())
        return nullptr;

    foreach (QWidget *w, QApplication::topLevelWidgets()) {
        if (QWidget *found = w->findChild<QWidget*>(objectName, Qt::FindChildrenRecursively))
            return found;
    }
    return nullptr;
}

QAction *AutomationTools::findAction(const QString &objectName) const
{
    if (objectName.isEmpty())
        return nullptr;

    foreach (QWidget *w, QApplication::topLevelWidgets()) {
        if (QAction *found = w->findChild<QAction*>(objectName, Qt::FindChildrenRecursively))
            return found;
    }
    return nullptr;
}

bool AutomationTools::isConnected() const
{
    return m_main->m_currentConnection && m_main->m_currentConnection->isConnected();
}

QWidgetList AutomationTools::openDialogs()
{
    QWidgetList dialogs;

    foreach (QWidget *w, QApplication::topLevelWidgets()) {
        if (!w->isVisible() || w->windowType() == Qt::Popup ||
            w->testAttribute(Qt::WA_DontShowOnScreen) ||
            w->width() <= 0 || w->height() <= 0)
            continue;
        // Only real user-facing windows: dialogs and message boxes.
        if (qobject_cast<QDialog*>(w))
            dialogs.append(w);
    }
    return dialogs;
}

QJsonArray AutomationTools::openDialogsInfo()
{
    QJsonArray arr;
    foreach (QWidget *d, openDialogs()) {
        QJsonObject o;
        o["class"] = QString::fromLatin1(d->metaObject()->className());
        if (!d->objectName().isEmpty()) o["name"] = d->objectName();
        if (!d->windowTitle().isEmpty()) o["title"] = d->windowTitle();

        QStringList labels, buttons;
        foreach (QLabel *l, d->findChildren<QLabel*>())
            if (!l->text().isEmpty() && l->isVisible()) labels << l->text();
        foreach (QAbstractButton *b, d->findChildren<QAbstractButton*>())
            if (!b->text().isEmpty() && b->isVisible()) buttons << b->text().remove('&');

        if (!labels.isEmpty()) o["text"] = labels.join("\n");
        if (!buttons.isEmpty()) o["buttons"] = QJsonArray::fromStringList(buttons);

        QRect pos(d->mapToGlobal(QPoint(0, 0)), d->size());
        QJsonArray rect;
        rect << pos.x() << pos.y() << pos.width() << pos.height();
        o["rect"] = rect;

        arr.append(o);
    }
    return arr;
}

bool AutomationTools::deviceReady() const
{
    return isConnected() && m_main->m_resetCompleted;
}

int AutomationTools::consoleLineCount() const
{
    return m_main->ui->txtConsole->document()->blockCount();
}

void AutomationTools::waitForResponse(int baseLine, int timeoutMs,
    std::function<bool (const QString &line)> isLast,
    std::function<void (const QStringList &lines, bool responded)> done)
{
    QTimer *timer = new QTimer(this);
    timer->setInterval(50);

    QSharedPointer<int> next(new int(baseLine));
    QSharedPointer<QStringList> lines(new QStringList());
    QSharedPointer<QElapsedTimer> elapsed(new QElapsedTimer());
    QSharedPointer<std::function<void (const QStringList &, bool)> > cb(new std::function<void (const QStringList &, bool)>(done));

    elapsed->start();

    connect(timer, &QTimer::timeout, this, [=]() {
        QTextDocument *doc = m_main->ui->txtConsole->document();

        while (*next < doc->blockCount()) {
            QString line = doc->findBlockByNumber(*next).text().trimmed();
            ++(*next);

            if (line.isEmpty())
                continue;
            lines->append(line);

            if (isLast(line)) {
                timer->stop();
                timer->deleteLater();
                (*cb)(*lines, true);
                return;
            }
        }

        if (elapsed->elapsed() >= timeoutMs) {
            timer->stop();
            timer->deleteLater();
            (*cb)(*lines, !lines->isEmpty());
        }
    });

    timer->start();
}

// ---------------------------------------------------------------------------
// State objects
// ---------------------------------------------------------------------------

static QJsonObject coordsObject(double x, double y, double z, double a)
{
    QJsonObject c;
    c["x"] = x;
    c["y"] = y;
    c["z"] = z;
    c["a"] = a;
    return c;
}

QJsonObject AutomationTools::machineStateObject() const
{
    QJsonObject state;
    state["connected"] = isConnected();
    state["device"] = deviceStateName(m_main->m_deviceState);
    state["sender"] = senderStateName(m_main->m_senderState);
    state["statusLine"] = m_lastStatus;
    state["mpos"] = coordsObject(m_main->ui->txtMPosX->value(), m_main->ui->txtMPosY->value(),
        m_main->ui->txtMPosZ->value(), m_main->ui->txtMPosA->value());
    state["wpos"] = coordsObject(m_main->ui->txtWPosX->value(), m_main->ui->txtWPosY->value(),
        m_main->ui->txtWPosZ->value(), m_main->ui->txtWPosA->value());

    if (m_main->m_currentConnection)
        state["connection"] = QString::fromLatin1(m_main->m_currentConnection->metaObject()->className());

    QJsonArray dialogs = openDialogsInfo();
    if (!dialogs.isEmpty())
        state["dialogs"] = dialogs;

    state["program"] = programSummaryObject();
    return state;
}

QJsonObject AutomationTools::programSummaryObject() const
{
    QJsonObject program;
    program["fileName"] = m_main->m_programFileName;
    program["lineCount"] = m_main->m_currentModel->rowCount();
    program["currentLine"] = m_main->m_lastDrawnLineIndex;

    QVector3D lb = m_main->m_currentDrawer->getModelLowerBounds();
    QVector3D ub = m_main->m_currentDrawer->getModelUpperBounds();

    QJsonObject lower;
    lower["x"] = lb.x(); lower["y"] = lb.y(); lower["z"] = lb.z();
    QJsonObject upper;
    upper["x"] = ub.x(); upper["y"] = ub.y(); upper["z"] = ub.z();

    program["lowerBounds"] = lower;
    program["upperBounds"] = upper;
    return program;
}

// ---------------------------------------------------------------------------
// Tool list
// ---------------------------------------------------------------------------

QJsonArray AutomationTools::toolList() const
{
    static const char *const motionWarning =
        " Requires the app to be started with --mcp-allow-motion.";

    QJsonArray tools;

    {
        QJsonObject props;
        tools.append(toolDesc("machine_state",
            "Machine snapshot: connection, device/sender state, last GRBL status line, "
            "work and machine coordinates, loaded program summary.", props));
    }
    {
        QJsonObject props;
        QJsonObject lines;
        lines["type"] = "integer";
        lines["description"] = "How many trailing console lines to return (max 2000).";
        lines["default"] = 50;
        props["lines"] = lines;
        tools.append(toolDesc("console_tail",
            "Trailing lines of the GRBL console (sent commands and device responses).", props));
    }
    {
        QJsonObject props;
        QJsonObject cmd;
        cmd["type"] = "string";
        cmd["enum"] = QJsonArray() << "?" << "$G" << "$#" << "$$" << "$I" << "$N";
        cmd["description"] = "GRBL query command.";
        props["command"] = cmd;
        QJsonObject wait;
        wait["type"] = "integer";
        wait["description"] = "Milliseconds to wait for the response (max 15000).";
        wait["default"] = 2000;
        props["waitMs"] = wait;
        tools.append(toolDesc("grbl_query",
            "Send a read-only GRBL query (status report, parser state, settings...) and "
            "return the device response.", props, QStringList() << "command"));
    }
    {
        QJsonObject props;
        QJsonObject cmd;
        cmd["type"] = "string";
        cmd["description"] = "Single G-code/GRBL command.";
        props["command"] = cmd;
        QJsonObject cmds;
        cmds["type"] = "array";
        cmds["items"] = QJsonObject{{"type", "string"}};
        cmds["description"] = "Multiple commands, sent in order.";
        props["commands"] = cmds;
        QJsonObject wait;
        wait["type"] = "integer";
        wait["description"] = "Milliseconds to wait for 'ok'/'error' (max 15000, 0 = fire and forget).";
        wait["default"] = 1500;
        props["waitMs"] = wait;
        tools.append(toolDesc("gcode_send",
            QString::fromLatin1("Send G-code/GRBL commands to the device.") +
            QLatin1String(motionWarning), props));
    }
    {
        QJsonObject props;
        QJsonObject axis;
        axis["type"] = "string";
        axis["enum"] = QJsonArray() << "x" << "y" << "z" << "a";
        props["axis"] = axis;
        QJsonObject dist;
        dist["type"] = "number";
        dist["description"] = "Signed distance in millimeters.";
        props["distance"] = dist;
        QJsonObject feed;
        feed["type"] = "number";
        feed["description"] = "Jog feed rate in mm/min.";
        feed["default"] = 500;
        props["feed"] = feed;
        QJsonObject wait;
        wait["type"] = "integer";
        wait["description"] = "Milliseconds to wait for 'ok' (max 15000).";
        wait["default"] = 1500;
        props["waitMs"] = wait;
        tools.append(toolDesc("jog",
            QString::fromLatin1("Relative jog via GRBL $J= command.") +
            QLatin1String(motionWarning), props, QStringList() << "axis" << "distance"));
    }
    {
        QJsonObject props;
        QJsonObject action;
        action["type"] = "string";
        action["enum"] = QJsonArray() << "unlock" << "home" << "hold" << "resume" << "sleep" << "reset";
        props["action"] = action;
        tools.append(toolDesc("motion_control",
            QString::fromLatin1("Machine control: $X unlock, $H home, feed hold, "
            "resume, sleep, soft reset.") + QLatin1String(motionWarning), props,
            QStringList() << "action"));
    }
    {
        QJsonObject props;
        QJsonObject action;
        action["type"] = "string";
        action["enum"] = QJsonArray() << "start" << "pause" << "resume" << "abort" << "reset";
        props["action"] = action;
        tools.append(toolDesc("job_control",
            QString::fromLatin1("Program transfer control using the main window buttons.") +
            QLatin1String(motionWarning), props, QStringList() << "action"));
    }
    {
        QJsonObject props;
        QJsonObject path;
        path["type"] = "string";
        path["description"] = "Absolute path to a G-code file.";
        props["path"] = path;
        tools.append(toolDesc("file_load",
            "Load a G-code file into the program editor and visualizer.", props,
            QStringList() << "path"));
    }
    {
        QJsonObject props;
        tools.append(toolDesc("program_summary",
            "Loaded program: file name, line count, current line, model bounds.", props));
    }
    {
        QJsonObject props;
        QJsonObject from;
        from["type"] = "integer";
        from["description"] = "First line, 1-based.";
        from["default"] = 1;
        props["from"] = from;
        QJsonObject to;
        to["type"] = "integer";
        to["description"] = "Last line, 1-based inclusive (window capped at 1000 lines).";
        props["to"] = to;
        tools.append(toolDesc("program_lines", "Lines of the loaded program.", props));
    }
    {
        QJsonObject props;
        QJsonObject root;
        root["type"] = "string";
        root["description"] = "objectName of a subtree root (optional).";
        props["root"] = root;
        QJsonObject filter;
        filter["type"] = "string";
        filter["description"] = "Keep nodes whose objectName/text (or an ancestor's/descendant's) contains this substring.";
        props["filter"] = filter;
        QJsonObject max;
        max["type"] = "integer";
        max["description"] = "Node budget (default 1500).";
        max["default"] = 1500;
        props["maxNodes"] = max;
        tools.append(toolDesc("ui_tree",
            "Widget tree of all windows: objectName, class, text/value, rect, enabled/visible. "
            "Use objectNames with ui_click/ui_set.", props));
    }
    {
        QJsonObject props;
        QJsonObject name;
        name["type"] = "string";
        name["description"] = "objectName of a button/checkbox/action (from ui_tree).";
        props["objectName"] = name;
        QJsonObject text;
        text["type"] = "string";
        text["description"] = "Button text to click inside an open dialog (use when the dialog has no objectNames).";
        props["text"] = text;
        tools.append(toolDesc("ui_click",
            "Click a button/checkbox or trigger an action by objectName, or a dialog button "
            "by text (dialogs only). Motion-related targets require --mcp-allow-motion.", props));
    }
    {
        QJsonObject props;
        QJsonObject name;
        name["type"] = "string";
        name["description"] = "objectName of the widget.";
        props["objectName"] = name;
        QJsonObject value;
        value["description"] = "String for edit fields, boolean for checkboxes, number for spin/slider boxes.";
        props["value"] = value;
        tools.append(toolDesc("ui_set",
            "Set value of QLineEdit/QSpinBox/QDoubleSpinBox/QCheckBox/QComboBox/QSlider by objectName.",
            props, QStringList() << "objectName" << "value"));
    }
    {
        QJsonObject props;
        QJsonObject filter;
        filter["type"] = "string";
        filter["description"] = "Substring filter over objectName/text.";
        props["filter"] = filter;
        tools.append(toolDesc("action_list",
            "Menu/toolbar actions with objectName, text, shortcut and state. Trigger via action_trigger.", props));
    }
    {
        QJsonObject props;
        QJsonObject name;
        name["type"] = "string";
        name["description"] = "objectName of the QAction.";
        props["objectName"] = name;
        tools.append(toolDesc("action_trigger",
            "Trigger a QAction by objectName. Motion-related actions require --mcp-allow-motion.",
            props, QStringList() << "objectName"));
    }
    {
        QJsonObject props;
        QJsonObject widget;
        widget["type"] = "string";
        widget["description"] = "objectName of a widget to capture (default: main window; 'screen' for full screen).";
        props["widget"] = widget;
        QJsonObject save;
        save["type"] = "string";
        save["description"] = "Absolute PNG path; defaults to a file in the temp directory.";
        props["savePath"] = save;
        tools.append(toolDesc("screenshot",
            "PNG screenshot returned as image content (visualizer included) and saved to a file.", props));
    }

    return tools;
}

// ---------------------------------------------------------------------------
// Tool invocation
// ---------------------------------------------------------------------------

static QString jsonCompact(const QJsonValue &value)
{
    QJsonDocument doc = value.isArray()
        ? QJsonDocument(value.toArray())
        : QJsonDocument(value.toObject());
    return QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
}

void AutomationTools::call(const QString &tool, const QJsonObject &args, ResultCallback done)
{
    static const QStringList motionTools = {
        "gcode_send", "jog", "motion_control", "job_control"
    };
    static const QStringList safeWidgets = {
        "cmdTop", "cmdFront", "cmdLeft", "cmdIsometric", "cmdFit", "cmdPerspective", "cmdClearConsole"
    };
    static const QStringList safeActionPrefixes = { "actView", "actHelp", "actJog" };

    if (motionTools.contains(tool) && !m_allowMotion) {
        done(textContent("Motion tools are locked. Restart Candle with --mcp-allow-motion "
            "to enable gcode_send/jog/motion_control/job_control."), true);
        return;
    }

    if (tool == "machine_state") {
        done(textContent(jsonCompact(machineStateObject())), false);
        return;
    }

    if (tool == "console_tail") {
        int count = qBound(1, args.value("lines").toInt(50), 2000);
        int total = m_main->ui->txtConsole->document()->blockCount();
        QStringList lines;
        for (int i = qMax(0, total - count); i < total; i++)
            lines.append(m_main->ui->txtConsole->document()->findBlockByNumber(i).text());
        done(textContent(jsonCompact(QJsonArray::fromStringList(lines))), false);
        return;
    }

    if (tool == "grbl_query") {
        static const QStringList allowed = { "?", "$G", "$#", "$$", "$I", "$N" };
        QString command = args.value("command").toString();
        if (!allowed.contains(command)) {
            done(textContent("Query must be one of: ?, $G, $#, $$, $I, $N."), true);
            return;
        }
        if (!deviceReady()) {
            done(textContent(isConnected() ?
                "Device is not ready (reset in progress)." :
                "Not connected to the device."), true);
            return;
        }

        int waitMs = qBound(0, args.value("waitMs").toInt(2000), 15000);
        int base = consoleLineCount();

        if (command == "?") {
            // Status reports bypass the console; wait for a fresh status line.
            QSharedPointer<QString> before(new QString(m_lastStatus));
            QSharedPointer<QElapsedTimer> elapsed(new QElapsedTimer());
            elapsed->start();

            int timeout = waitMs ? waitMs : 1500;
            m_main->m_currentConnection->send(command);

            QTimer *timer = new QTimer(this);
            timer->setInterval(50);
            QSharedPointer<ResultCallback> cb(new ResultCallback(done));
            connect(timer, &QTimer::timeout, this, [=]() {
                if (m_lastStatus != *before || elapsed->elapsed() >= timeout) {
                    timer->stop();
                    timer->deleteLater();
                    if (m_lastStatus == *before)
                        (*cb)(textContent("No status response."), true);
                    else
                        (*cb)(textContent(m_lastStatus), false);
                }
            });
            timer->start();
            return;
        }

        m_main->sendCommand(command, -3, true, false);

        waitForResponse(base, waitMs ? waitMs : 1500,
            [](const QString &line) {
                return line == "ok" || line.startsWith("error");
            },
            [done, command, waitMs](const QStringList &lines, bool responded) {
                if (!waitMs) {
                    done(textContent(QString("Sent '%1' (no wait).").arg(command)), false);
                    return;
                }
                if (!responded) {
                    done(textContent(QString("No response to '%1'.").arg(command)), true);
                    return;
                }
                QStringList out = lines;
                if (!out.isEmpty() && (out.last() == "ok" || out.last().startsWith("error")))
                    out.removeLast();
                done(textContent(jsonCompact(QJsonArray::fromStringList(out))), false);
            });
        return;
    }

    if (tool == "gcode_send") {
        QStringList commands;
        if (args.contains("commands"))
            foreach (const QJsonValue &v, args.value("commands").toArray())
                commands.append(v.toString());
        if (args.contains("command"))
            commands.append(args.value("command").toString());
        commands.removeAll(QString());

        if (commands.isEmpty()) {
            done(textContent("Provide 'command' or 'commands'."), true);
            return;
        }
        if (!deviceReady()) {
            done(textContent(isConnected() ?
                "Device is not ready (reset in progress)." :
                "Not connected to the device."), true);
            return;
        }

        runGcode(commands, args.value("waitMs").toInt(1500), done);
        return;
    }

    if (tool == "jog") {
        QString axis = args.value("axis").toString().toLower();
        if (axis.isEmpty() || !QString("xyza").contains(axis)) {
            done(textContent("axis must be x, y, z or a."), true);
            return;
        }
        double distance = args.value("distance").toDouble();
        if (distance == 0.0 || qAbs(distance) > 10000.0) {
            done(textContent("distance must be a non-zero signed value in millimeters (|d| <= 10000)."), true);
            return;
        }
        double feed = args.value("feed").toDouble(500.0);
        if (feed <= 0) {
            done(textContent("feed must be positive."), true);
            return;
        }
        if (!deviceReady()) {
            done(textContent(isConnected() ?
                "Device is not ready (reset in progress)." :
                "Not connected to the device."), true);
            return;
        }

        runGcode(QStringList() << QString("$J=G21G91%1%2F%3")
            .arg(axis.toUpper())
            .arg(QString::number(distance, 'f', 3))
            .arg(QString::number(feed, 'f', 0)),
            args.value("waitMs").toInt(1500), done);
        return;
    }

    if (tool == "motion_control") {
        QString action = args.value("action").toString();
        if (!deviceReady()) {
            done(textContent(isConnected() ?
                "Device is not ready (reset in progress)." :
                "Not connected to the device."), true);
            return;
        }

        if (action == "unlock" || action == "home" || action == "sleep") {
            QString command = action == "unlock" ? "$X" : (action == "home" ? "$H" : "$SLP");
            runGcode(QStringList() << command, 3000, done);
            return;
        }
        if (action == "hold") {
            m_main->m_currentConnection->send("!");
            done(textContent("Feed hold sent."), false);
            return;
        }
        if (action == "resume") {
            m_main->m_currentConnection->send("~");
            done(textContent("Resume sent."), false);
            return;
        }
        if (action == "reset") {
            m_main->grblReset();
            done(textContent("Soft reset sent."), false);
            return;
        }
        done(textContent("Unknown action (use unlock/home/hold/resume/sleep/reset)."), true);
        return;
    }

    if (tool == "job_control") {
        QString action = args.value("action").toString();
        QAbstractButton *button = nullptr;

        if (action == "start") button = m_main->ui->cmdFileSend;
        else if (action == "pause" || action == "resume") button = m_main->ui->cmdFilePause;
        else if (action == "abort") button = m_main->ui->cmdFileAbort;
        else if (action == "reset") button = m_main->ui->cmdFileReset;
        else {
            done(textContent("Unknown action (use start/pause/resume/abort/reset)."), true);
            return;
        }

        if (!button->isEnabled()) {
            done(textContent(QString("'%1' is not available: %2")
                .arg(action, !isConnected() ? "not connected" :
                    (m_main->m_currentModel->rowCount() <= 1 && action == "start" ?
                        "no program loaded" : "control disabled in current state"))), true);
            return;
        }

        button->click();
        done(textContent(QString("%1 command %2.").arg(action,
            action == "start" ? "transfer started" : "sent")), false);
        return;
    }

    if (tool == "file_load") {
        QString path = args.value("path").toString();
        QFileInfo info(path);
        if (path.isEmpty() || !info.exists() || !info.isFile()) {
            done(textContent("File not found: " + path), true);
            return;
        }
        m_main->loadFile(info.absoluteFilePath());
        done(textContent(jsonCompact(programSummaryObject())), false);
        return;
    }

    if (tool == "program_summary") {
        done(textContent(jsonCompact(programSummaryObject())), false);
        return;
    }

    if (tool == "program_lines") {
        int rowCount = m_main->m_currentModel->rowCount();
        int from = qBound(1, args.value("from").toInt(1), qMax(1, rowCount));
        int to = args.contains("to") ? args.value("to").toInt() : from + 99;
        to = qBound(from, to, rowCount);
        if (to - from + 1 > 1000) to = from + 999;

        QJsonArray lines;
        for (int i = from; i <= to; i++)
            lines.append(QString::fromUtf8(m_main->m_currentModel->commandAt(i - 1)));

        QJsonObject out;
        out["from"] = from;
        out["to"] = to;
        out["lineCount"] = rowCount;
        out["lines"] = lines;
        done(textContent(jsonCompact(out)), false);
        return;
    }

    if (tool == "ui_tree") {
        QString filter = args.value("filter").toString();
        QString rootName = args.value("root").toString();
        int budget = qBound(1, args.value("maxNodes").toInt(1500), 10000);
        bool truncated = false;

        QWidget *root = rootName.isEmpty() ? nullptr : findWidget(rootName);
        if (!rootName.isEmpty() && !root) {
            done(textContent("Widget not found: " + rootName), true);
            return;
        }

        // depth-first walk; returns whether the node or its subtree matches filter
        // hiddenAncestor marks children of a hidden widget: they are listed
        // (so hidden panels stay discoverable) but their subtrees are not expanded.
        std::function<QJsonObject (QWidget*, QWidget*, bool)> walk =
            [&](QWidget *w, QWidget *origin, bool hiddenAncestor) -> QJsonObject {
            QJsonObject node;
            bool hidden = hiddenAncestor || !w->isVisible();
            bool selfMatch = true;

            if (!filter.isEmpty()) {
                QString text = w->objectName();
                text += " " + QString::fromLatin1(w->metaObject()->className());
                if (QAbstractButton *b = qobject_cast<QAbstractButton*>(w)) text += " " + b->text();
                else if (QLabel *l = qobject_cast<QLabel*>(w)) text += " " + l->text();
                else if (QLineEdit *e = qobject_cast<QLineEdit*>(w)) text += " " + e->text();
                selfMatch = text.contains(filter, Qt::CaseInsensitive);
            }

            node["name"] = w->objectName();
            node["class"] = QString::fromLatin1(w->metaObject()->className());

            if (QAbstractButton *b = qobject_cast<QAbstractButton*>(w)) {
                node["text"] = b->text();
                if (b->isCheckable())
                    node["checked"] = b->isChecked();
            } else if (QLabel *l = qobject_cast<QLabel*>(w)) {
                if (!l->text().isEmpty()) node["text"] = l->text();
            } else if (QLineEdit *e = qobject_cast<QLineEdit*>(w)) {
                node["value"] = e->text();
            } else if (QComboBox *c = qobject_cast<QComboBox*>(w)) {
                node["value"] = c->currentText();
            } else if (QDoubleSpinBox *d = qobject_cast<QDoubleSpinBox*>(w)) {
                node["value"] = d->value();
            } else if (QSpinBox *s = qobject_cast<QSpinBox*>(w)) {
                node["value"] = s->value();
            } else if (QSlider *sl = qobject_cast<QSlider*>(w)) {
                node["value"] = sl->value();
            }

            if (!w->isEnabled()) node["enabled"] = false;
            if (hidden) node["visible"] = false;
            if (w->isWindow() && !w->windowTitle().isEmpty()) node["title"] = w->windowTitle();

            QPoint pos = w->mapTo(origin, QPoint(0, 0));
            QJsonArray rect;
            rect << pos.x() << pos.y() << w->width() << w->height();
            node["rect"] = rect;

            bool subtreeMatch = selfMatch;

            // !hiddenAncestor: children of hidden widgets are listed once but
            // their own children are not expanded (bounds the tree size).
            if (budget > 0 && !hiddenAncestor) {
                QJsonArray children;
                foreach (QObject *child, w->children()) {
                    QWidget *cw = qobject_cast<QWidget*>(child);
                    if (!cw)
                        continue;
                    if (budget <= 0) {
                        truncated = true;
                        break;
                    }
                    budget--;
                    QJsonObject cn = walk(cw, origin, hidden);
                    bool matched = cn.value("_m").toBool();
                    cn.remove("_m");
                    if (matched) {
                        subtreeMatch = true;
                        children.append(cn);
                    } else if (selfMatch) {
                        children.append(cn); // keep full subtree of an explicitly matched node
                    }
                }
                if (!children.isEmpty())
                    node["children"] = children;
            } else if (budget <= 0) {
                truncated = true;
            }

            node["_m"] = subtreeMatch || selfMatch;
            return node;
        };

        QJsonArray windows;
        if (root) {
            budget--;
            QJsonObject n = walk(root, root, false);
            n.remove("_m");
            done(textContent(jsonCompact(n)), false);
            return;
        }

        foreach (QWidget *w, QApplication::topLevelWidgets()) {
            if (w->windowType() == Qt::Popup)
                continue; // internal combo/menu popups are noise
            if (budget <= 0) {
                truncated = true;
                break;
            }
            budget--;
            QJsonObject n = walk(w, w, false);
            if (n.value("_m").toBool()) {
                n.remove("_m");
                windows.append(n);
            }
        }

        QJsonObject out;
        out["windows"] = windows;
        if (truncated)
            out["truncated"] = true;
        done(textContent(jsonCompact(out)), false);
        return;
    }

    if (tool == "ui_click") {
        QString name = args.value("objectName").toString();
        QString text = args.value("text").toString();

        // Buttons in dialogs (QMessageBox etc.) have no objectName; allow
        // clicking them by visible text, restricted to dialog windows so this
        // can never hit the main window's motion buttons.
        if (name.isEmpty() && !text.isEmpty()) {
            QAbstractButton *hit = nullptr;
            foreach (QWidget *d, openDialogs()) {
                foreach (QAbstractButton *b, d->findChildren<QAbstractButton*>()) {
                    if (!b->isVisible() || !b->isEnabled())
                        continue;
                    QString bt = b->text();
                    bt.remove('&');
                    if (bt.compare(text, Qt::CaseInsensitive) == 0) { hit = b; break; }
                }
                if (hit) break;
            }
            if (!hit) {
                done(textContent("No enabled dialog button with text: " + text), true);
                return;
            }
            hit->click();
            done(textContent(QString("Clicked dialog button '%1' (%2).")
                .arg(text, QString::fromLatin1(hit->window()->metaObject()->className()))), false);
            return;
        }

        QWidget *w = findWidget(name);
        QAction *a = w ? nullptr : findAction(name);

        if (!w && !a) {
            done(textContent("Widget/action not found: " + name), true);
            return;
        }

        QString target = name;
        bool safe = safeWidgets.contains(target);
        if (!safe && !m_allowMotion) {
            done(textContent(QString("Clicking '%1' could move the machine or start a job. "
                "Restart Candle with --mcp-allow-motion to allow this.").arg(name)), true);
            return;
        }

        if (w) {
            if (QAbstractButton *b = qobject_cast<QAbstractButton*>(w)) {
                if (!b->isEnabled()) {
                    done(textContent(QString("'%1' is disabled.").arg(name)), true);
                    return;
                }
                b->click();
                done(textContent(QString("Clicked %1 (%2).").arg(name,
                    QString::fromLatin1(w->metaObject()->className()))), false);
                return;
            }
            done(textContent(QString("'%1' is %2, not clickable. Use ui_set for value widgets.")
                .arg(name, QString::fromLatin1(w->metaObject()->className()))), true);
            return;
        }

        if (!a->isEnabled()) {
            done(textContent(QString("Action '%1' is disabled.").arg(name)), true);
            return;
        }
        a->trigger();
        done(textContent(QString("Triggered %1.").arg(name)), false);
        return;
    }

    if (tool == "ui_set") {
        QString name = args.value("objectName").toString();
        QWidget *w = findWidget(name);
        if (!w) {
            done(textContent("Widget not found: " + name), true);
            return;
        }

        QJsonValue value = args.value("value");

        if (QDoubleSpinBox *d = qobject_cast<QDoubleSpinBox*>(w)) {
            d->setValue(value.toDouble());
        } else if (QSpinBox *s = qobject_cast<QSpinBox*>(w)) {
            s->setValue(value.toInt());
        } else if (QCheckBox *cb = qobject_cast<QCheckBox*>(w)) {
            cb->setChecked(value.toBool());
        } else if (QComboBox *c = qobject_cast<QComboBox*>(w)) {
            if (c->isEditable() && c->lineEdit())
                c->lineEdit()->setText(value.toString());
            else
                c->setCurrentText(value.toString());
        } else if (QSlider *sl = qobject_cast<QSlider*>(w)) {
            sl->setValue(value.toInt());
        } else if (QLineEdit *e = qobject_cast<QLineEdit*>(w)) {
            e->setText(value.toString());
        } else if (QAbstractButton *b = qobject_cast<QAbstractButton*>(w)) {
            if (!b->isCheckable()) {
                done(textContent(QString("'%1' is not settable. Use ui_click.").arg(name)), true);
                return;
            }
            b->setChecked(value.toBool());
        } else {
            done(textContent(QString("Unsupported widget type for ui_set: %1")
                .arg(QString::fromLatin1(w->metaObject()->className()))), true);
            return;
        }

        done(textContent(QString("Set %1.").arg(name)), false);
        return;
    }

    if (tool == "action_list") {
        QString filter = args.value("filter").toString();
        QJsonArray actions;

        foreach (QAction *a, m_main->findChildren<QAction*>(QString(), Qt::FindChildrenRecursively)) {
            if (a->objectName().isEmpty())
                continue;
            QString text = a->text();
            text.remove('&');
            if (!filter.isEmpty() &&
                !a->objectName().contains(filter, Qt::CaseInsensitive) &&
                !text.contains(filter, Qt::CaseInsensitive))
                continue;

            QJsonObject o;
            o["name"] = a->objectName();
            o["text"] = text;
            if (a->isCheckable()) o["checked"] = a->isChecked();
            if (!a->isEnabled()) o["enabled"] = false;
            if (!a->shortcut().isEmpty())
                o["shortcut"] = a->shortcut().toString(QKeySequence::NativeText);
            actions.append(o);

            if (actions.size() >= 400)
                break;
        }

        done(textContent(jsonCompact(actions)), false);
        return;
    }

    if (tool == "action_trigger") {
        QString name = args.value("objectName").toString();
        QAction *a = findAction(name);
        if (!a) {
            done(textContent("Action not found: " + name), true);
            return;
        }
        bool safe = false;
        foreach (const QString &prefix, safeActionPrefixes)
            if (name.startsWith(prefix)) safe = true;
        if (!safe && !m_allowMotion) {
            done(textContent(QString("Triggering '%1' is gated. "
                "Restart Candle with --mcp-allow-motion to allow this.").arg(name)), true);
            return;
        }
        if (!a->isEnabled()) {
            done(textContent(QString("Action '%1' is disabled.").arg(name)), true);
            return;
        }
        a->trigger();
        done(textContent(QString("Triggered %1.").arg(name)), false);
        return;
    }

    if (tool == "screenshot") {
        QString widget = args.value("widget").toString();
        QString savePath = args.value("savePath").toString();

        QImage image;

        if (widget == "screen") {
            QScreen *screen = QApplication::primaryScreen();
            if (!screen) {
                done(textContent("No primary screen."), true);
                return;
            }
            image = screen->grabWindow(0).toImage();
        } else if (!widget.isEmpty()) {
            QWidget *target = findWidget(widget);
            if (!target) {
                done(textContent("Widget not found: " + widget), true);
                return;
            }
            image = target->grab().toImage();
        } else {
            // Main window plus any open dialogs, painted into a shared canvas
            // so modal popups (program end, errors) are visible to the agent.
            QWidgetList windows = openDialogs();
            QRect canvas(m_main->mapToGlobal(QPoint(0, 0)), m_main->size());
            foreach (QWidget *d, windows)
                canvas = canvas.united(QRect(d->mapToGlobal(QPoint(0, 0)), d->size()));
            canvas.setWidth(qMin(canvas.width(), 8192));
            canvas.setHeight(qMin(canvas.height(), 4096));

            qreal dpr = m_main->devicePixelRatioF();
            image = QImage(canvas.size() * dpr, QImage::Format_ARGB32_Premultiplied);
            image.setDevicePixelRatio(dpr);
            image.fill(QColor(0x40, 0x40, 0x40));

            {
                QPainter painter(&image);

                QPoint mainTl = m_main->mapToGlobal(QPoint(0, 0)) - canvas.topLeft();
                painter.translate(mainTl);
                m_main->render(&painter);

                // QOpenGLWidget contents do not go through the backing store;
                // paste the visualizer framebuffer over its rect.
                foreach (QOpenGLWidget *gl, m_main->findChildren<QOpenGLWidget*>()) {
                    if (!gl->isVisible())
                        continue;
                    QImage fb = gl->grabFramebuffer();
                    if (fb.isNull())
                        continue;
                    QPoint tl = gl->mapTo(m_main, QPoint(0, 0));
                    painter.drawImage(QRect(tl, gl->size()), fb);
                }

                painter.translate(-mainTl);
                foreach (QWidget *d, windows) {
                    QPoint tl = d->mapToGlobal(QPoint(0, 0)) - canvas.topLeft();
                    painter.drawImage(QRect(tl, d->size()), d->grab().toImage());
                }
            }
        }

        QByteArray png;
        QBuffer buffer(&png);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
        buffer.close();

        QString path = savePath;
        if (path.isEmpty()) {
            QDir dir(QDir::tempPath());
            dir.mkpath("candle-mcp");
            path = dir.absoluteFilePath(QString("candle-mcp/screenshot-%1.png")
                .arg(QDateTime::currentMSecsSinceEpoch()));
        }
        QFile file(path);
        bool saved = file.open(QIODevice::WriteOnly) && file.write(png) == png.size();

        QJsonObject info;
        info["savedTo"] = saved ? path : QString("(failed to save file)");
        info["width"] = image.width();
        info["height"] = image.height();
        info["bytes"] = png.size();

        QJsonArray content;
        content.append(textItem(jsonCompact(info)));

        QJsonObject imageItem;
        imageItem["type"] = QLatin1String("image");
        imageItem["data"] = QString::fromLatin1(png.toBase64());
        imageItem["mimeType"] = QLatin1String("image/png");
        content.append(imageItem);

        done(content, !saved);
        return;
    }

    done(textContent("Unknown tool: " + tool), true);
}

void AutomationTools::runGcode(const QStringList &commands, int waitMs, ResultCallback done)
{
    int base = consoleLineCount();

    foreach (const QString &command, commands)
        m_main->sendCommand(command, -1, true, false);

    if (waitMs <= 0) {
        QJsonObject out;
        out["sent"] = QJsonArray::fromStringList(commands);
        out["responded"] = false;
        done(textContent(jsonCompact(out)), false);
        return;
    }

    waitForResponse(base, qBound(0, waitMs, 15000),
        [](const QString &line) {
            return line == "ok" || line.startsWith("error") || line.startsWith("ALARM:");
        },
        [done, commands](const QStringList &lines, bool responded) {
            QJsonObject out;
            out["sent"] = QJsonArray::fromStringList(commands);
            out["response"] = QJsonArray::fromStringList(lines);
            out["responded"] = responded;
            done(textContent(jsonCompact(out)), !responded);
        });
}
