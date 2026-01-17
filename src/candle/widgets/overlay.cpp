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
    const QString updatingText = tr("Updating...");

    QPainter painter(this);
    QFontMetrics fm(painter.font());

    auto xbounds = QString("X: %1 ... %2").arg(m_parent->m_modelLowerBounds.x(), 0, 'f', 3)
        .arg(m_parent->m_modelUpperBounds.x(), 0, 'f', 3);
    auto ybounds = QString("Y: %1 ... %2").arg(m_parent->m_modelLowerBounds.y(), 0, 'f', 3)
        .arg(m_parent->m_modelUpperBounds.y(), 0, 'f', 3);
    auto zbounds = QString("Z: %1 ... %2").arg(m_parent->m_modelLowerBounds.z(), 0, 'f', 3)
        .arg(m_parent->m_modelUpperBounds.z(), 0, 'f', 3);
    auto ranges = QString("%1 / %2 / %3").arg(m_parent->m_modelRanges.x(), 0, 'f', 3)
        .arg(m_parent->m_modelRanges.y(), 0, 'f', 3).arg(m_parent->m_modelRanges.z(), 0, 'f', 3);
    auto vertices = QString(tr("Vertices: %1")).arg(m_parent->m_vertices);
    auto fps = QString("FPS: %1").arg(m_parent->m_fps);
    auto estimate = m_parent->m_spendTime.toString("hh:mm:ss") + " / " + m_parent->m_estimatedTime.toString("hh:mm:ss");
    auto buffer = m_parent->m_bufferState;

    double x = 10;
    double y = this->height() - fm.height() * 3 - 10;

    // painter.setBrush(QBrush(QColor(255, 255, 255, 196)));
    // painter.drawRect(5, 5, fm.horizontalAdvance(m_parent->m_parserStatus) + 10, fm.height() * 3 + 10);
    // painter.drawRect(5, y - fm.height(),
    //     qMax(qMax(qMax(fm.horizontalAdvance(xbounds), fm.horizontalAdvance(ybounds)), fm.horizontalAdvance(zbounds)),
    //         fm.horizontalAdvance(ranges)) + 10,
    //     fm.height() * 4 + 5
    // );
    // auto blockWidth = qMax(qMax(qMax(fm.horizontalAdvance(vertices), fm.horizontalAdvance(fps)),
    //     fm.horizontalAdvance(estimate)), fm.horizontalAdvance(buffer));
    // painter.drawRect(this->width() - 15 - blockWidth, y - fm.height(), blockWidth + 10, fm.height() * 4 + 5);

    QPen pen(m_parent->m_colorText);
    painter.setPen(pen);

    painter.drawText(QPoint(x, y), xbounds);
    painter.drawText(QPoint(x, y + fm.height()), ybounds);
    painter.drawText(QPoint(x, y + fm.height() * 2), zbounds);
    painter.drawText(QPoint(x, y + fm.height() * 3), ranges);

    painter.drawText(QPoint(x, fm.height() + 10), m_parent->m_parserStatus);
    painter.drawText(QPoint(x, fm.height() * 2 + 10), m_parent->m_speedState);
    painter.drawText(QPoint(x, fm.height() * 3 + 10), m_parent->m_pinState);

    painter.drawText(QPoint(this->width() - fm.width(vertices) - 10, y + fm.height() * 2), vertices);
    painter.drawText(QPoint(this->width() - fm.width(fps) - 10, y + fm.height() * 3), fps);
    painter.drawText(QPoint(this->width() - fm.width(estimate) - 10, y), estimate);
    painter.drawText(QPoint(this->width() - fm.width(buffer) - 10, y + fm.height()), buffer);

    if (m_parent->m_updating)
        painter.drawText(QPoint((this->width() - fm.width(updatingText)) / 2, y + fm.height() * 3), updatingText);

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