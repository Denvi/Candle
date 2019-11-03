#include "scriptvars.h"

ScriptVars::ScriptVars()
{
    m_Mx = 10;
    m_My = 20;
    m_Mz = 30;

    m_Wx = 0;
    m_Wy = 0;
    m_Wz = 0;

    m_G54x = 0;
    m_G54y = 0;
    m_G54z = 0;

    m_G55x = 0;
    m_G55y = 0;
    m_G55z = 0;

    m_G56x = 0;
    m_G56y = 0;
    m_G56z = 0;

    m_G57x = 0;
    m_G57y = 0;
    m_G57z = 0;

    m_G58x = 0;
    m_G58y = 0;
    m_G58z = 0;

    m_G59x = 0;
    m_G59y = 0;
    m_G59z = 0;

    m_G28x = 0;
    m_G28y = 0;
    m_G28z = 0;

    m_G30x = 0;
    m_G30y = 0;
    m_G30z = 0;

    m_G92x = 0;
    m_G92y = 0;
    m_G92z = 0;

    m_TLOx = 0;
    m_TLOy = 0;
    m_TLOz = 0;

    m_PRBx = 0;
    m_PRBy = 0;
    m_PRBz = 0;    
}

void ScriptVars::setMx(double value)
{
    m_Mx = value;
}

double ScriptVars::Mx() const
{
    return m_Mx;
}

void ScriptVars::setMy(double value)
{
    m_My = value;
}

double ScriptVars::My() const
{
    return m_My;
}

void ScriptVars::setMz(double value)
{
    m_Mz = value;
}

double ScriptVars::Mz() const
{
    return m_Mz;
}

void ScriptVars::setWx(double value)
{
    m_Wx = value;
}

double ScriptVars::Wx() const
{
    return m_Wx;
}

void ScriptVars::setWy(double value)
{
    m_Wy = value;
}

double ScriptVars::Wy() const
{
    return m_Wy;
}

void ScriptVars::setWz(double value)
{
    m_Wz = value;
}

double ScriptVars::Wz() const
{
    return m_Wz;
}

void ScriptVars::setG54x(double value)
{
    m_G54x = value;
}

double ScriptVars::G54x() const
{
    return m_G54x;
}

void ScriptVars::setG54y(double value)
{
    m_G54y = value;
}

double ScriptVars::G54y() const
{
    return m_G54y;
}

void ScriptVars::setG54z(double value)
{
    m_G54z = value;
}

double ScriptVars::G54z() const
{
    return m_G54z;
}

void ScriptVars::setG55x(double value)
{
    m_G55x = value;
}

double ScriptVars::G55x() const
{
    return m_G55x;
}

void ScriptVars::setG55y(double value)
{
    m_G55y = value;
}

double ScriptVars::G55y() const
{
    return m_G55y;
}

void ScriptVars::setG55z(double value)
{
    m_G55z = value;
}

double ScriptVars::G55z() const
{
    return m_G55z;
}

void ScriptVars::setG56x(double value)
{
    m_G56x = value;
}

double ScriptVars::G56x() const
{
    return m_G56x;
}

void ScriptVars::setG56y(double value)
{
    m_G56y = value;
}

double ScriptVars::G56y() const
{
    return m_G56y;
}

void ScriptVars::setG56z(double value)
{
    m_G56z = value;
}

double ScriptVars::G56z() const
{
    return m_G56z;
}

void ScriptVars::setG57x(double value)
{
    m_G57x = value;
}

double ScriptVars::G57x() const
{
    return m_G57x;
}

void ScriptVars::setG57y(double value)
{
    m_G57y = value;
}

double ScriptVars::G57y() const
{
    return m_G57y;
}

void ScriptVars::setG57z(double value)
{
    m_G57z = value;
}

double ScriptVars::G57z() const
{
    return m_G57z;
}

void ScriptVars::setG58x(double value)
{
    m_G58x = value;
}

double ScriptVars::G58x() const
{
    return m_G58x;
}

void ScriptVars::setG58y(double value)
{
    m_G58y = value;
}

double ScriptVars::G58y() const
{
    return m_G58y;
}

void ScriptVars::setG58z(double value)
{
    m_G58z = value;
}

double ScriptVars::G58z() const
{
    return m_G58z;
}

void ScriptVars::setG59x(double value)
{
    m_G59x = value;
}

double ScriptVars::G59x() const
{
    return m_G59x;
}

void ScriptVars::setG59y(double value)
{
    m_G59y = value;
}

double ScriptVars::G59y() const
{
    return m_G59y;
}

void ScriptVars::setG59z(double value)
{
    m_G59z = value;
}

double ScriptVars::G59z() const
{
    return m_G59z;
}

void ScriptVars::setG28x(double value)
{
    m_G28x = value;
}

double ScriptVars::G28x() const
{
    return m_G28x;
}

void ScriptVars::setG28y(double value)
{
    m_G28y = value;
}

double ScriptVars::G28y() const
{
    return m_G28y;
}

void ScriptVars::setG28z(double value)
{
    m_G28z = value;
}

double ScriptVars::G28z() const
{
    return m_G28z;
}

void ScriptVars::setG30x(double value)
{
    m_G30x = value;
}

double ScriptVars::G30x() const
{
    return m_G30x;
}

void ScriptVars::setG30y(double value)
{
    m_G30y = value;
}

double ScriptVars::G30y() const
{
    return m_G30y;
}

void ScriptVars::setG30z(double value)
{
    m_G30z = value;
}

double ScriptVars::G30z() const
{
    return m_G30z;
}

void ScriptVars::setG92x(double value)
{
    m_G92x = value;
}

double ScriptVars::G92x() const
{
    return m_G92x;
}

void ScriptVars::setG92y(double value)
{
    m_G92y = value;
}

double ScriptVars::G92y() const
{
    return m_G92y;
}

void ScriptVars::setG92z(double value)
{
    m_G92z = value;
}

double ScriptVars::G92z() const
{
    return m_G92z;
}

void ScriptVars::setTLOx(double value)
{
    m_TLOx = value;
}

double ScriptVars::TLOx() const
{
    return m_TLOx;
}

void ScriptVars::setTLOy(double value)
{
    m_TLOy = value;
}

double ScriptVars::TLOy() const
{
    return m_TLOy;
}

void ScriptVars::setTLOz(double value)
{
    m_TLOz = value;
}

double ScriptVars::TLOz() const
{
    return m_TLOz;
}

void ScriptVars::setPRBx(double value)
{
    m_PRBx = value;
}

double ScriptVars::PRBx() const
{
    return m_PRBx;
}

void ScriptVars::setPRBy(double value)
{
    m_PRBy = value;
}

double ScriptVars::PRBy() const
{
    return m_PRBy;
}

void ScriptVars::setPRBz(double value)
{
    m_PRBz = value;
}

double ScriptVars::PRBz() const
{
    return m_PRBz;
}