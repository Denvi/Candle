#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "connection/connection.h"
#include "machine/settings.h"

struct CommandAttributes {
    int length;
    int consoleIndex;
    int tableIndex;
    QString command;

    CommandAttributes() {
    }

    CommandAttributes(int len, int consoleIdx, int tableIdx, QString cmd) {
        length = len;
        consoleIndex = consoleIdx;
        tableIndex = tableIdx;
        command = cmd;
    }
};

struct CommandQueue {
    QString command;
    int tableIndex;
    bool showInConsole;

    CommandQueue() {
    }

    CommandQueue(QString cmd, int idx, bool show) {
        command = cmd;
        tableIndex = idx;
        showInConsole = show;
    }
};

enum SenderState {
    SenderUnknown = -1,
    SenderTransferring = 0,
    SenderPausing = 1,
    SenderPaused = 2,
    SenderStopping = 3,
    SenderStopped = 4,
    SenderChangingTool = 5,
    SenderPausing2 = 6
};

enum DeviceState {
    DeviceUnknown = -1,
    DeviceIdle = 1,
    DeviceAlarm = 2,
    DeviceRun = 3,
    DeviceHome = 4,
    DeviceHold0 = 5,
    DeviceHold1 = 6,
    DeviceQueue = 7,
    DeviceCheck = 8,
    DeviceDoor0 = 9,
    DeviceDoor1 = 10,
    DeviceDoor2 = 11,
    DeviceDoor3 = 12,
    DeviceJog = 13,
    DeviceSleep =14
};

enum SendCommandResult {
    SendDone = 0,
    SendEmpty = 1,
    SendQueue = 2
};

class Communicator : public QObject
{
public:
    Communicator(Connection *connection);    
    SendCommandResult sendCommand(QString command, int tableIndex = -1, bool showInConsole = true, bool wait = false);
    void sendRealtimeCommand(QString command);
    void sendCommands(QString commands, int tableIndex = -1);

private:
    Connection *m_connection;
    Settings *m_settings;
    QList<CommandAttributes> m_commands;
    QList<CommandQueue> m_queue;
    SenderState m_senderState;
    DeviceState m_deviceState;

    //slots:
    void onSerialPortReadyRead(QString);
    void setSenderState(int);
    void setDeviceState(int);

signals:
    void responseReceived(QString command, int tableIndex, QString response);
    void statusReceived(QString status);
    void senderStateChanged(int state);
    void deviceStateChanged(int state);
};

#endif // COMMUNICATOR_H
