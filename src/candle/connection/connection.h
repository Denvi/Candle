#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QObject *parent = nullptr);
    virtual ~Connection() {}

    virtual bool openConnection() = 0;
    virtual void sendByteArray(QByteArray) = 0;
    virtual bool isConnected() = 0;
    virtual void sendLine(QString) = 0;
    virtual void closeConnection() = 0;

signals:
    void lineReceived(const QString &line);
    void error(const QString &text);
};

#endif
