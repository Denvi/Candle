#include "scriptapp.h"
#include "frmmain.h"
#include <QApplication>
#include "loggingcategories.h"

ScriptApp::ScriptApp(frmMain *f): QObject(0), m_frmMain(f)
{
    m_scriptProgram = new ScriptProgram(f);
    m_scriptDevice = new ScriptDevice(f);
    m_scriptSender = new ScriptSender(f);
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

void ScriptApp::addAction(QAction *action)
{
    m_frmMain->addAction(action);
}

void ScriptApp::removeAction(QAction *action)
{
    m_frmMain->removeAction(action);
}

ScriptProgram* ScriptApp::program()
{
    return m_scriptProgram;
}

ScriptDevice* ScriptApp::device()
{
    return m_scriptDevice;
}

ScriptSender* ScriptApp::sender()
{
    return m_scriptSender;
}

int ScriptApp::buttonSize()
{
    return m_frmMain->buttonSize();
}

QWidget* ScriptApp::window()
{
    return m_frmMain;
}