#include "scriptfunctions.h"
#include "frmmain.h"
#include <QApplication>
#include "loggingcategories.h"

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

void ScriptFunctions::sendCommands(QStringList commands, int index)
{
    m_frmMain->sendCommands(commands.join("\n"), index);
}

void ScriptFunctions::sendCommand(QString command, int index, bool showInConsole, bool direct)
{
    if (direct) {
        m_frmMain->m_serialPort.write((command + "\r").toLatin1());
    } else {
        m_frmMain->sendCommand(command, index, showInConsole, m_frmMain->m_queue.size());
    }
}

void ScriptFunctions::waitResponses()
{
    while (m_frmMain->m_queue.size() || m_frmMain->m_commands.size()) {
        QApplication::processEvents();
    }
}

void ScriptFunctions::storeParserState()
{
    m_frmMain->storeParserState();
}

void ScriptFunctions::restoreParserState()
{
    m_frmMain->restoreParserState();
}

bool ScriptFunctions::newFile()
{
    if (m_frmMain->m_senderState != frmMain::SenderState::SenderStopped) {
        qInfo(scriptLogCategory) << "Can't create new file while sender is streaming";
        return false;
    }

    if (!m_frmMain->saveChanges(false)) return false;

    m_frmMain->newFile();

    return true;
}

bool ScriptFunctions::loadFile(QString fileName)
{
    if (m_frmMain->m_senderState != frmMain::SenderState::SenderStopped) {
        qInfo(scriptLogCategory) << "Can't load file while sender is streaming";
        return false;
    }

    if (!m_frmMain->saveChanges(false)) return false;

    m_frmMain->loadFile(fileName);

    return true;
}

bool ScriptFunctions::loadFile(QStringList data)
{
    if (m_frmMain->m_senderState != frmMain::SenderState::SenderStopped) {
        qInfo(scriptLogCategory) << "Can't load file while sender is streaming";
        return false;
    }

    if (!m_frmMain->saveChanges(false)) return false;

    m_frmMain->newFile();
    m_frmMain->loadFile(data);

    m_frmMain->m_fileChanged = true;

    return true;
}

bool ScriptFunctions::saveFile()
{
    return m_frmMain->saveChanges(false);
}

bool ScriptFunctions::saveFile(QString fileName)
{
    if (m_frmMain->saveProgramToFile(fileName, &m_frmMain->m_programModel)) {
        m_frmMain->m_programFileName = fileName;
        m_frmMain->m_fileChanged = false;

        m_frmMain->addRecentFile(fileName);
        m_frmMain->updateRecentFilesMenu();

        m_frmMain->updateControlsState();

        return true;
    }

    return false;
}

int ScriptFunctions::bufferLength()
{
    return m_frmMain->bufferLength();
}

int ScriptFunctions::commandsLength()
{
    return m_frmMain->m_commands.length();
}

int ScriptFunctions::queueLength()
{
    return m_frmMain->m_queue.length();
}

int ScriptFunctions::buttonSize()
{
    return m_frmMain->buttonSize();
}

QWidget* ScriptFunctions::window()
{
    return m_frmMain;
}

int ScriptFunctions::senderState()
{
    return m_frmMain->m_senderState;
}

int ScriptFunctions::deviceState()
{
    return m_frmMain->m_deviceState;
}

void ScriptFunctions::addAction(QAction *action)
{
    m_frmMain->addAction(action);
}

void ScriptFunctions::removeAction(QAction *action)
{
    m_frmMain->removeAction(action);
}