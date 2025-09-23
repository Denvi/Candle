#pragma once

#include <QObject>

class frmMain;

class ScriptSender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int state READ state)

public slots:

signals:
    void stateChanged(int state);

public:
    ScriptSender(frmMain *f);

private:
    frmMain *m_frmMain;

    int state();
};