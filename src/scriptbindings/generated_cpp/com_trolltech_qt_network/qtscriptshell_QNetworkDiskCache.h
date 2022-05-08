#ifndef QTSCRIPTSHELL_QNETWORKDISKCACHE_H
#define QTSCRIPTSHELL_QNETWORKDISKCACHE_H

#include <qnetworkdiskcache.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QNetworkDiskCache : public QNetworkDiskCache
{
public:
    QtScriptShell_QNetworkDiskCache(QObject*  parent = 0);
    ~QtScriptShell_QNetworkDiskCache();

    qint64  cacheSize() const;
    void childEvent(QChildEvent*  event);
    void clear();
    void customEvent(QEvent*  event);
    QIODevice*  data(const QUrl&  url);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    qint64  expire();
    void insert(QIODevice*  device);
    QNetworkCacheMetaData  metaData(const QUrl&  url);
    QIODevice*  prepare(const QNetworkCacheMetaData&  metaData);
    bool  remove(const QUrl&  url);
    void timerEvent(QTimerEvent*  event);
    void updateMetaData(const QNetworkCacheMetaData&  metaData);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKDISKCACHE_H
