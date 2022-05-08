#ifndef QTSCRIPTSHELL_QSQLDRIVER_H
#define QTSCRIPTSHELL_QSQLDRIVER_H

#include <qsqldriver.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSqlDriver : public QSqlDriver
{
public:
    QtScriptShell_QSqlDriver(QObject*  parent = 0);
    ~QtScriptShell_QSqlDriver();

    bool  beginTransaction();
    bool  cancelQuery();
    void childEvent(QChildEvent*  event);
    void close();
    bool  commitTransaction();
    QSqlResult*  createResult() const;
    void customEvent(QEvent*  event);
    QString  escapeIdentifier(const QString&  identifier, QSqlDriver::IdentifierType  type) const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    QString  formatValue(const QSqlField&  field, bool  trimStrings = false) const;
    QVariant  handle() const;
    bool  hasFeature(QSqlDriver::DriverFeature  f) const;
    bool  isIdentifierEscaped(const QString&  identifier, QSqlDriver::IdentifierType  type) const;
    bool  isOpen() const;
    bool  open(const QString&  db, const QString&  user = QString(), const QString&  password = QString(), const QString&  host = QString(), int  port = -1, const QString&  connOpts = QString());
    QSqlIndex  primaryIndex(const QString&  tableName) const;
    QSqlRecord  record(const QString&  tableName) const;
    bool  rollbackTransaction();
    void setLastError(const QSqlError&  e);
    void setOpen(bool  o);
    void setOpenError(bool  e);
    QString  sqlStatement(QSqlDriver::StatementType  type, const QString&  tableName, const QSqlRecord&  rec, bool  preparedStatement) const;
    QString  stripDelimiters(const QString&  identifier, QSqlDriver::IdentifierType  type) const;
    bool  subscribeToNotification(const QString&  name);
    QStringList  subscribedToNotifications() const;
    QStringList  tables(QSql::TableType  tableType) const;
    void timerEvent(QTimerEvent*  event);
    bool  unsubscribeFromNotification(const QString&  name);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSQLDRIVER_H
