#ifndef QTSCRIPTSHELL_QMIMEDATA_H
#define QTSCRIPTSHELL_QMIMEDATA_H

#include <qmimedata.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMimeData : public QMimeData
{
public:
    QtScriptShell_QMimeData();
    ~QtScriptShell_QMimeData();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    QStringList  formats() const;
    bool  hasFormat(const QString&  mimetype) const;
    QVariant  retrieveData(const QString&  mimetype, QVariant::Type  preferredType) const;
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMIMEDATA_H
