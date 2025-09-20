#pragma once

#include <QObject>
#include "coordinates.h"

class frmMain;

class ScriptDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Coordinates* work READ workCoordinates)
    Q_PROPERTY(Coordinates* machine READ machineCoordinates)
    Q_PROPERTY(Coordinates* probe READ probeCoordinates)
    Q_PROPERTY(int state READ state)
    Q_PROPERTY(int bufferLength READ bufferLength)
    Q_PROPERTY(int commandsLength READ commandsLength)
    Q_PROPERTY(int queueLength READ queueLength)

public slots:
    void sendCommands(QString commands, int index = -100);
    void sendCommands(QStringList commands, int index = -100);
    void sendCommand(QString command, int index = -100, bool showInConsole = true, bool direct = false);
    void waitResponses();
    void storeParserState();
    void restoreParserState();

signals:
    void responseReceived(QString command, int tableIndex, QString response);
    void statusReceived(QString status);
    void stateChanged(int state);

public:
    ScriptDevice(frmMain *f);

    void setWorkCoordinates(double x, double y, double z, double a);
    Coordinates* workCoordinates();

    void setMachineCoordinates(double x, double y, double z, double a);
    Coordinates* machineCoordinates();

    void setProbeCoordinates(double x, double y, double z, double a);
    Coordinates* probeCoordinates();

private:
    frmMain *m_frmMain;

    Coordinates m_workCoordinates;
    Coordinates m_machineCoordinates;
    Coordinates m_probeCoordinates;

    int bufferLength();
    int commandsLength();
    int queueLength();
    int state();
};