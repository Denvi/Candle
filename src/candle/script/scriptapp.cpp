#include "scriptapp.h"
#include "frmmain.h"
#include <QApplication>
#include "loggingcategories.h"

ScriptApp::ScriptApp(frmMain *f): QObject(0), m_frmMain(f)
{
    m_scriptProgram = new ScriptProgram(f);
}

void ScriptApp::sendCommands(QString commands, int index)
{
    m_frmMain->sendCommands(commands, index);
}

void ScriptApp::sendCommands(QStringList commands, int index)
{
    m_frmMain->sendCommands(commands.join("\n"), index);
}

void ScriptApp::sendCommand(QString command, int index, bool showInConsole, bool direct)
{
    if (direct) {
        m_frmMain->m_serialPort.write((command + "\r").toLatin1());
    } else {
        m_frmMain->sendCommand(command, index, showInConsole, m_frmMain->m_queue.size());
    }
}

void ScriptApp::waitResponses()
{
    while (m_frmMain->m_queue.size() || m_frmMain->m_commands.size()) {
        QApplication::processEvents();
    }
}

void ScriptApp::storeParserState()
{
    m_frmMain->storeParserState();
}

void ScriptApp::restoreParserState()
{
    m_frmMain->restoreParserState();
}

bool ScriptApp::newFile()
{
    if (m_frmMain->m_senderState != frmMain::SenderState::SenderStopped) {
        qInfo(scriptLogCategory) << "Can't create new file while sender is streaming";
        return false;
    }

    if (!m_frmMain->saveChanges(false)) return false;

    m_frmMain->newFile();

    return true;
}

bool ScriptApp::loadFile(QString fileName)
{
    if (m_frmMain->m_senderState != frmMain::SenderState::SenderStopped) {
        qInfo(scriptLogCategory) << "Can't load file while sender is streaming";
        return false;
    }

    if (!m_frmMain->saveChanges(false)) return false;

    m_frmMain->loadFile(fileName);

    return true;
}

bool ScriptApp::loadFile(QStringList data)
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

bool ScriptApp::saveFile()
{
    return m_frmMain->saveChanges(false);
}

bool ScriptApp::saveFile(QString fileName)
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

int ScriptApp::bufferLength()
{
    return m_frmMain->bufferLength();
}

int ScriptApp::commandsLength()
{
    return m_frmMain->m_commands.length();
}

int ScriptApp::queueLength()
{
    return m_frmMain->m_queue.length();
}

int ScriptApp::buttonSize()
{
    return m_frmMain->buttonSize();
}

QWidget* ScriptApp::window()
{
    return m_frmMain;
}

int ScriptApp::senderState()
{
    return m_frmMain->m_senderState;
}

int ScriptApp::deviceState()
{
    return m_frmMain->m_deviceState;
}

ScriptProgram* ScriptApp::scriptProgram()
{
    return m_scriptProgram;
}

void ScriptApp::addAction(QAction *action)
{
    m_frmMain->addAction(action);
}

void ScriptApp::removeAction(QAction *action)
{
    m_frmMain->removeAction(action);
}