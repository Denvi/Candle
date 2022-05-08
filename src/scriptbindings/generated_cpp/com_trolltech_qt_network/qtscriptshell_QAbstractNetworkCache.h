#ifndef QTSCRIPTSHELL_QABSTRACTNETWORKCACHE_H
#define QTSCRIPTSHELL_QABSTRACTNETWORKCACHE_H

#include <qabstractnetworkcache.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAbstractNetworkCache : public QAbstractNetworkCache
{
public:
    QtScriptShell_QAbstractNetworkCache(QObject*  parent = 0);
    ~QtScriptShell_QAbstractNetworkCache();

    qint64  cacheSize() const;
    void childEvent(QChildEvent*  event);
    void clear();
    void customEvent(QEvent*  event);
    QIODevice*  data(const QUrl&  url);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void insert(QIODevice*  device);
    QNetworkCacheMetaData  metaData(const QUrl&  url);
    QIODevice*  prepare(const QNetworkCacheMetaData&  metaData);
    bool  remove(const QUrl&  url);
    void timerEvent(QTimerEvent*  event);
    void updateMetaData(const QNetworkCacheMetaData&  metaData);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTNETWORKCACHE_H
