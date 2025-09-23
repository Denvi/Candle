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