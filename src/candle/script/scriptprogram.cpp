#include "scriptprogram.h"
#include "frmmain.h"

ScriptProgram::ScriptProgram(frmMain *f) : QObject(f)
{
    m_frmMain = f;
}

QVector3D ScriptProgram::lowerBounds()
{
    return m_frmMain->m_currentDrawer->getModelLowerBounds();
}

QVector3D ScriptProgram::upperBounds()
{
    return m_frmMain->m_currentDrawer->getModelUpperBounds();
}

QString ScriptProgram::fileName() const
{
    return m_frmMain->m_programFileName;
}

QStringList ScriptProgram::lines() const
{
    auto r = QStringList();

    for (auto it = m_frmMain->m_currentModel->data().constBegin(); it != m_frmMain->m_currentModel->data().constEnd(); it++)
        r.append((*it).command);

    return r;
}