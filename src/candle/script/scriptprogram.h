#pragma once

#include <QObject>
#include <QVector3D>

class frmMain;

class ScriptProgram: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D lowerBounds READ lowerBounds)
    Q_PROPERTY(QVector3D upperBounds READ upperBounds)

public:
    ScriptProgram(frmMain *f);

public slots:

signals:

private:
    frmMain *m_frmMain;

    QVector3D lowerBounds();
    QVector3D upperBounds();
};