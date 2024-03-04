#ifndef SCRIPTING_H
#define SCRIPTING_H

#include "config/configuration.h"
#include "scriptfunctions.h"
#include "scriptvars.h"
#include <QObject>
#include <QScriptEngine>

class Scripting : public QObject
{
    Q_OBJECT

    friend class ScriptFunctions;

public:
    Scripting(Configuration *$configuration);
    void loadPlugins(QWidget *ui);

private:
    QScriptEngine m_scriptEngine;
    ScriptVars m_storedVars;
    ScriptFunctions m_scriptFunctions;
    Configuration *m_configuration;
    static QScriptValue importExtension(QScriptContext *context, QScriptEngine *engine);
    void onScriptException(const QScriptValue &exception);
};

#endif // SCRIPTING_H
