#include "scriptfunctions.h"
#include "frmmain.h"

ScriptFunctions::ScriptFunctions(QObject *parent): QObject(parent), m_frmMain(0)
{
}

void ScriptFunctions::setFrmMain(frmMain *f)
{
    m_frmMain = f;
}

frmMain* ScriptFunctions::getFrmMain()
{
    return m_frmMain;
}

void ScriptFunctions::sendCommands(QString commands, int id)
{
    m_frmMain->sendCommands(commands, -(100 + id));
}

void ScriptFunctions::sendCommand(QString command, int id)
{
    m_frmMain->sendCommand(command, -(100 + id));
}

int ScriptFunctions::buttonSize()
{
    return m_frmMain->buttonSize();
}

void ScriptFunctions::addAction(QAction *action)
{
    m_frmMain->addAction(action);
}

void ScriptFunctions::removeAction(QAction *action)
{
    m_frmMain->removeAction(action);
}