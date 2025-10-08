#pragma once

#include <QObject>
#include <QVector3D>

class frmMain;

class ScriptProgram: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D lowerBounds READ lowerBounds)
    Q_PROPERTY(QVector3D upperBounds READ upperBounds)
    Q_PROPERTY(QString fileName READ fileName)
    Q_PROPERTY(QStringList lines READ lines)

public slots:

signals:

public:
    ScriptProgram(frmMain *f);

private:
    frmMain *m_frmMain;

    QVector3D lowerBounds();
    QVector3D upperBounds();

    QString fileName() const;
    QStringList lines() const;
};