#pragma once

#include <QTextEdit>
#include <QCompleter>
#include "jshighlighter.h"
#include "customwidgetsshared.h"

class CUSTOMWIDGETS_DLLSPEC ScriptEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit ScriptEdit(QWidget *parent = nullptr);
    explicit ScriptEdit(const QString& text, QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *e) override;
    void insertFromMimeData(const QMimeData *source) override;

private slots:
    void insertCompletion(const QString &completion);

private:
    JSHighlighter *m_highlighter;
    QCompleter *m_completer;

    QStringList m_apiEntries = {
        // Global
        "print",

        // Script
        "script",
        "importExtension",

        // App
        "app",
        "newFile",
        "loadFile",
        "loadFile",
        "saveFile",
        "addAction",
        "removeAction",
        "window",
        "dataLocation",
        "profileName",

        // Settings
        "settings",
        "port",
        "baud",
        "toolDiameter",
        "toolLength",
        "antialiasing",
        "zBuffer",
        "lineWidth",
        "arcLength",
        "arcDegree",
        "arcDegreeMode",
        "showProgramCommands",
        "showUICommands",
        "spindleSpeedMin",
        "spindleSpeedMax",
        "laserPowerMin",
        "laserPowerMax",
        "queryStateTime",
        "toolType",
        "toolAngle",
        "fps",
        "vsync",
        "msaa",
        "autoCompletion",
        "simplify",
        "simplifyPrecision",
        "fontSize",
        "grayscaleSegments",
        "grayscaleSCode",
        "drawModeVectors",
        "ignoreErrors",
        "autoLine",
        "useStartCommands",
        "startCommands",
        "useEndCommands",
        "endCommands",
        "toolChangeCommands",
        "toolChangePause",
        "toolChangeUseCommands",
        "toolChangeUseCommandsConfirm",
        "language",
        "units",
        "rapidSpeed",
        "acceleration",
        "machineBounds",
        "homingEnabled",
        "softLimitsEnabled",
        "axisAEnabled",
        "axisAX",

        // Storage
        "storage",
        "group",
        "setValue",
        "value",
        "contains",
        "remove",

        // Storage group
        "childKeys",
        "childGroups",

        // Program
        "program",
        "lowerBounds"
        "upperBounds",

        // Device
        "device",
        "work",
        "machine",
        "probe",
        "state",
        "bufferLength",
        "commandLength",
        "queueLength",
        "sendCommand",
        "sendCommands",
        "waitResponses",
        "storeParserState",
        "restoreParserState",
 
        // Sender
        "sender",
    };

    void handleTabKey();
    void handleBackTabKey();
    void handleEnterKey();

    QString textUnderCursor() const;
};