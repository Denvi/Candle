#include <QPainter>
#include "overlay.h"
#include "glwidget.h"

Overlay::Overlay(GLWidget *parent) : QWidget(parent), m_parent(parent)
{
    setStyleSheet("color:white; background:transparent;");
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Overlay::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);

    QPen pen(m_parent->m_colorText);
    painter.setPen(pen);

    QFontMetrics fm(painter.font());
    double x = 10;
    double y = this->height() - fm.height() * 3 - 10;

    painter.drawText(QPoint(x, y), QString("X: %1 ... %2").arg(m_parent->m_modelLowerBounds.x(), 0, 'f', 3)
        .arg(m_parent->m_modelUpperBounds.x(), 0, 'f', 3));
    painter.drawText(QPoint(x, y + fm.height()), QString("Y: %1 ... %2").arg(m_parent->m_modelLowerBounds.y(), 0, 'f', 3)
        .arg(m_parent->m_modelUpperBounds.y(), 0, 'f', 3));
    painter.drawText(QPoint(x, y + fm.height() * 2), QString("Z: %1 ... %2").arg(m_parent->m_modelLowerBounds.z(), 0, 'f', 3)
        .arg(m_parent->m_modelUpperBounds.z(), 0, 'f', 3));
    painter.drawText(QPoint(x, y + fm.height() * 3), QString("%1 / %2 / %3").arg(m_parent->m_modelRanges.x(), 0, 'f', 3)
        .arg(m_parent->m_modelRanges.y(), 0, 'f', 3).arg(m_parent->m_modelRanges.z(), 0, 'f', 3));

    painter.drawText(QPoint(x, fm.height() + 10), m_parent->m_parserStatus);
    painter.drawText(QPoint(x, fm.height() * 2 + 10), m_parent->m_speedState);
    painter.drawText(QPoint(x, fm.height() * 3 + 10), m_parent->m_pinState);

    QString str = QString(tr("Vertices: %1")).arg(m_parent->m_vertices);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + fm.height() * 2), str);
    str = QString("FPS: %1").arg(m_parent->m_fps);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + fm.height() * 3), str);

    str = m_parent->m_spendTime.toString("hh:mm:ss") + " / " + m_parent->m_estimatedTime.toString("hh:mm:ss");
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y), str);

    str = m_parent->m_bufferState;
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + fm.height()), str);

    QMatrix4x4 w;
    w.scale(width() / 2, -height() / 2);
    w.translate(1, -1);
    w *= m_parent->m_projectionMatrix * m_parent->m_viewMatrix;

    foreach (ShaderDrawable *drawable, m_parent->m_shaderDrawables) {
        if (drawable->visible()) {
            painter.save();
            drawable->drawPainter(painter, w * drawable->modelMatrix(), height() / m_parent->m_windowSizeWorld);
            painter.restore();
        }
    }    
}