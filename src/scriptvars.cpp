#include "scriptvars.h"

ScriptVars::ScriptVars()
{
    m_coords["M"] = QVector3D();
    m_coords["W"] = QVector3D();
    m_coords["G54"] = QVector3D();
    m_coords["G55"] = QVector3D();
    m_coords["G56"] = QVector3D();
    m_coords["G57"] = QVector3D();
    m_coords["G58"] = QVector3D();
    m_coords["G59"] = QVector3D();
    m_coords["G28"] = QVector3D();
    m_coords["G30"] = QVector3D();
    m_coords["G92"] = QVector3D();
    m_coords["TLO"] = QVector3D();
    m_coords["PRB"] = QVector3D();
}

double ScriptVars::Mx() const
{
    return m_coords["M"].x();
}

double ScriptVars::My() const
{
    return m_coords["M"].y();
}

double ScriptVars::Mz() const
{
    return m_coords["M"].z();
}

double ScriptVars::Wx() const
{
    return m_coords["W"].x();
}

double ScriptVars::Wy() const
{
    return m_coords["W"].y();
}

double ScriptVars::Wz() const
{
    return m_coords["W"].z();
}

double ScriptVars::G54x() const
{
    return m_coords["G54"].x();
}

double ScriptVars::G54y() const
{
    return m_coords["G54"].y();
}

double ScriptVars::G54z() const
{
    return m_coords["G54"].z();
}

double ScriptVars::G55x() const
{
    return m_coords["G55"].x();
}

double ScriptVars::G55y() const
{
    return m_coords["G55"].y();
}

double ScriptVars::G55z() const
{
    return m_coords["G55"].z();
}

double ScriptVars::G56x() const
{
    return m_coords["G56"].x();
}

double ScriptVars::G56y() const
{
    return m_coords["G56"].y();
}

double ScriptVars::G56z() const
{
    return m_coords["G56"].z();
}

double ScriptVars::G57x() const
{
    return m_coords["G57"].x();
}

double ScriptVars::G57y() const
{
    return m_coords["G57"].y();
}

double ScriptVars::G57z() const
{
    return m_coords["G57"].z();
}

double ScriptVars::G58x() const
{
    return m_coords["G58"].x();
}

double ScriptVars::G58y() const
{
    return m_coords["G58"].y();
}

double ScriptVars::G58z() const
{
    return m_coords["G58"].z();
}

double ScriptVars::G59x() const
{
    return m_coords["G59"].x();
}

double ScriptVars::G59y() const
{
    return m_coords["G59"].y();
}

double ScriptVars::G59z() const
{
    return m_coords["G59"].z();
}

double ScriptVars::G28x() const
{
    return m_coords["G28"].x();
}

double ScriptVars::G28y() const
{
    return m_coords["G28"].y();
}

double ScriptVars::G28z() const
{
    return m_coords["G28"].z();
}

double ScriptVars::G30x() const
{
    return m_coords["G30"].x();
}

double ScriptVars::G30y() const
{
    return m_coords["G30"].y();
}

double ScriptVars::G30z() const
{
    return m_coords["G30"].z();
}

double ScriptVars::G92x() const
{
    return m_coords["G92"].x();
}

double ScriptVars::G92y() const
{
    return m_coords["G92"].y();
}

double ScriptVars::G92z() const
{
    return m_coords["G92"].z();
}

double ScriptVars::TLOx() const
{
    return m_coords["TLO"].x();
}

double ScriptVars::TLOy() const
{
    return m_coords["TLO"].y();
}

double ScriptVars::TLOz() const
{
    return m_coords["TLO"].z();
}

double ScriptVars::PRBx() const
{
    return m_coords["PRB"].x();
}

double ScriptVars::PRBy() const
{
    return m_coords["PRB"].y();
}

double ScriptVars::PRBz() const
{
    return m_coords["PRB"].z();
}

void ScriptVars::setCoords(QString name, QVector3D coords)
{
    m_coords[name] = coords;
}

QVector3D ScriptVars::coords(QString name) const
{
    return m_coords.keys().contains(name) ? m_coords[name] : QVector3D();
}

double ScriptVars::x(QString name) const
{
    return coords(name).x();
}

double ScriptVars::y(QString name) const
{
    return coords(name).y();
}

double ScriptVars::z(QString name) const
{
    return coords(name).z();
}

double ScriptVars::x() const
{
    return coords(m_cs).x();
}

double ScriptVars::y() const
{
    return coords(m_cs).y();
}

double ScriptVars::z() const
{
    return coords(m_cs).z();
}

void ScriptVars::setCS(QString cs)
{
    m_cs = cs;
}

QString ScriptVars::CS() const
{
    return m_cs;
}