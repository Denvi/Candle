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

void ScriptFunctions::sendCommands(QString commands, int index)
{
    m_frmMain->sendCommands(commands, index);
}

void ScriptFunctions::sendCommand(QString command, int index)
{
    m_frmMain->sendCommand(command, index);
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