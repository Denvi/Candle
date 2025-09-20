#include "scriptsender.h"
#include "./frmmain.h"

ScriptSender::ScriptSender(frmMain* f) : QObject(f)
{
    m_frmMain = f;
}

int ScriptSender::state()
{
    return m_frmMain->m_senderState;
}