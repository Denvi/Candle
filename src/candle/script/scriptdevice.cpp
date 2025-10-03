#include "scriptdevice.h"
#include "../frmmain.h"
#include <QApplication>

ScriptDevice::ScriptDevice(frmMain *f) : QObject(f)
{
    m_frmMain = f;
}

void ScriptDevice::sendCommands(QString commands, int index)
{
    m_frmMain->sendCommands(commands, index);
}

void ScriptDevice::sendCommands(QStringList commands, int index)
{
    m_frmMain->sendCommands(commands.join("\n"), index);
}

void ScriptDevice::sendCommand(QString command, int index, bool showInConsole)
{
    m_frmMain->sendCommand(command, index, showInConsole, m_frmMain->m_queue.size());
}

void ScriptDevice::sendRuntimeCommand(QString command)
{
    m_frmMain->m_currentConnection->send(command.toLatin1());
}

void ScriptDevice::waitResponses()
{
    while (m_frmMain->m_queue.size() || m_frmMain->m_commands.size()) {
        QApplication::processEvents();
    }
}

void ScriptDevice::storeParserState()
{
    m_frmMain->storeParserState();
}

void ScriptDevice::restoreParserState()
{
    m_frmMain->restoreParserState();
}

void ScriptDevice::setWorkCoordinates(double x, double y, double z, double a)
{
    m_workCoordinates.setX(x);
    m_workCoordinates.setY(y);
    m_workCoordinates.setZ(z);
    m_workCoordinates.setA(a);
}

Coordinates* ScriptDevice::workCoordinates()
{
    return &m_workCoordinates;
}

void ScriptDevice::setMachineCoordinates(double x, double y, double z, double a)
{
    m_machineCoordinates.setX(x);
    m_machineCoordinates.setY(y);
    m_machineCoordinates.setZ(z);
    m_machineCoordinates.setA(a);
}

Coordinates* ScriptDevice::machineCoordinates()
{
    return &m_machineCoordinates;
}

void ScriptDevice::setProbeCoordinates(double x, double y, double z, double a)
{
    m_probeCoordinates.setX(x);
    m_probeCoordinates.setY(y);
    m_probeCoordinates.setZ(z);
    m_probeCoordinates.setA(a);
}

Coordinates* ScriptDevice::probeCoordinates()
{
    return &m_probeCoordinates;
}

int ScriptDevice::bufferLength()
{
    return m_frmMain->bufferLength();
}

int ScriptDevice::commandsLength()
{
    return m_frmMain->m_commands.length();
}

int ScriptDevice::queueLength()
{
    return m_frmMain->m_queue.length();
}

int ScriptDevice::state()
{
    return m_frmMain->m_deviceState;
}