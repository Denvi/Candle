#include "overlay.h"
#include <QDebug>
#include <QPainter>
#include <QPen>

Overlay::Overlay(QWidget *parent): QWidget(parent)
{
    m_aimPosition = QPoint(0, 0);
    m_aimSize = 20;
    m_aimLineWidth = 2;
    m_aimColor = QColor(Qt::black).rgb();
}

void Overlay::setAimPosition(QPointF aimPosition)
{
    m_aimPosition = aimPosition;
}

QPointF Overlay::aimPosition() const
{
    return m_aimPosition;
}

void Overlay::setAimSize(int aimSize)
{
    m_aimSize = aimSize;
    update();
}

int Overlay::aimSize() const
{
    return m_aimSize;
}

void Overlay::setAimLineWidth(int aimLineWidth)
{
    m_aimLineWidth = aimLineWidth;
    update();
}

int Overlay::aimLineWidth() const
{
    return m_aimLineWidth;
}

void Overlay::setAimColor(int aimColor)
{
    m_aimColor = aimColor;
    update();
}

int Overlay::aimColor() const
{
    return m_aimColor;
}

void Overlay::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    QPen pen;
    pen.setWidth(m_aimLineWidth);
    pen.setColor(QColor::fromRgb(m_aimColor));

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(pen);
    p.drawLine(0, m_aimPosition.y(), width(), m_aimPosition.y());
    p.drawLine(m_aimPosition.x(), 0, m_aimPosition.x(), height());
    p.drawEllipse(m_aimPosition, m_aimSize / 2, m_aimSize / 2);
}