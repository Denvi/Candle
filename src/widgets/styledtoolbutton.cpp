// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "styledtoolbutton.h"
#include <QDebug>
#include <QEvent>

StyledToolButton::StyledToolButton(QWidget *parent) : QAbstractButton(parent)
{
    m_hovered = false;
    m_backColor = palette().color(QPalette::Button);
    m_foreColor = palette().color(QPalette::ButtonText);
    m_highlightColor = QColor(127, 211, 255).darker(120);
}

bool StyledToolButton::isHover()
{
    return m_hovered;
}

void StyledToolButton::enterEvent(QEvent *e)
{
    Q_UNUSED(e)

    m_hovered = true;
}

void StyledToolButton::leaveEvent(QEvent *e)
{
    Q_UNUSED(e)

    m_hovered = false;
}

void StyledToolButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    const int borderWidth = 4;
    const int borderRadius = 5;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    // Highlight
    QPen highlightPen;

    if ((!this->isEnabled() && !this->isChecked()) || (!this->isDown() && !this->isChecked() && !this->isHover())) {
        highlightPen.setColor(Qt::white);
    } else if (this->isDown() || this->isChecked()) {
        highlightPen.setColor(m_highlightColor);
    } else if (this->isHover()) {
        highlightPen.setColor(m_highlightColor.lighter(120));
    }

    highlightPen.setWidth(2);
    painter.setPen(highlightPen);
    painter.drawRoundedRect(1, 1, this->width() - 2, this->height() - 2, borderRadius - 1, borderRadius - 1);

    // Border
    QPen pen(this->isEnabled() ? palette().color(QPalette::Shadow) : palette().color(QPalette::Mid));

    if ((this->isDown() || this->isChecked()) && this->isEnabled()) pen.setColor(Qt::black);

    pen.setWidth(2);
    pen.setCapStyle(Qt::SquareCap);
    painter.setPen(pen);

    painter.drawLine(borderRadius, 0, width() - borderRadius, 0);
    painter.drawLine(borderRadius, height(), width() - borderRadius, height());
    painter.drawLine(0, borderRadius, 0, height() - borderRadius);
    painter.drawLine(width(), borderRadius, width(), height() - borderRadius);

    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawArc(0, 0, borderRadius * 2, borderRadius * 2, 90 * 16, 90 * 16);
    painter.drawArc(width() - borderRadius * 2, 0, borderRadius * 2, borderRadius * 2, 0 * 16, 90 * 16);
    painter.drawArc(0, height() - borderRadius * 2, borderRadius * 2, borderRadius * 2, 180 * 16, 90 * 16);
    painter.drawArc(width() - borderRadius * 2, height() - borderRadius * 2, borderRadius * 2, borderRadius * 2, 270 * 16, 90 * 16);

    // Background border
    QLinearGradient backGradient(width() / 2, height() / 2, width() / 2, height());
    backGradient.setColorAt(0, this->isEnabled() ? m_backColor : palette().color(QPalette::Button));
    backGradient.setColorAt(1, this->isEnabled() ? m_backColor.darker(130) : palette().color(QPalette::Button).darker(130));
    QBrush backBrush(backGradient);
    painter.setBrush(backBrush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(borderWidth - 1, borderWidth - 1, width() - borderWidth * 2 + 2, height() - borderWidth * 2 + 2, 2, 2);

    // Background
    painter.setBrush(this->isEnabled() ? m_backColor : palette().color(QPalette::Button));
    painter.setPen(Qt::NoPen);
    painter.drawRect(borderWidth, borderWidth, width() - borderWidth * 2, height() - borderWidth * 2);

    // Icon/text rect
    QRect innerRect(borderWidth, borderWidth, width() - borderWidth * 2, height() - borderWidth * 2);
    if (this->isDown() || this->isChecked()) {
        innerRect.setLeft(innerRect.left() + 2);
        innerRect.setTop(innerRect.top() + 2);
    }

    // Icon
    if (!this->icon().isNull()) {
        QSize iconSize = this->icon().actualSize(this->iconSize());
        painter.drawPixmap(QRect(innerRect.x() + (innerRect.width() - iconSize.width()) / 2,
                                 innerRect.y() + (innerRect.height() - iconSize.height()) / 2,
                                 iconSize.width(), iconSize.height()),
                           this->icon().pixmap(iconSize, this->isEnabled() ? QIcon::Normal : QIcon::Disabled));
    } else {
        // Text
        painter.setPen(this->isEnabled() ? m_foreColor : palette().color(QPalette::Mid));
        painter.drawText(innerRect, Qt::AlignCenter, this->text());
    }
}
QColor StyledToolButton::highlightColor() const
{
    return m_highlightColor;
}

void StyledToolButton::setHighlightColor(const QColor &highlightColor)
{
    m_highlightColor = highlightColor;
}

QColor StyledToolButton::foreColor() const
{
    return m_foreColor;
}

void StyledToolButton::setForeColor(const QColor &foreColor)
{
    m_foreColor = foreColor;
}

QColor StyledToolButton::backColor() const
{
    return m_backColor;
}

void StyledToolButton::setBackColor(const QColor &backColor)
{
    m_backColor = backColor;
}


