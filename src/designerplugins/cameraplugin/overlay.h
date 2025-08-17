#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QPaintEvent>

class Overlay: public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPointF aimPosition READ aimPosition WRITE setAimPosition);
    Q_PROPERTY(int aimSize READ aimSize WRITE setAimSize);
    Q_PROPERTY(int aimLineWidth READ aimLineWidth WRITE setAimLineWidth);
    Q_PROPERTY(int aimColor READ aimColor WRITE setAimColor);

public:
    Overlay(QWidget *parent);

    void setAimPosition(QPointF aimPosition);
    QPointF aimPosition() const;

    void setAimSize(int aimSize);
    int aimSize() const;

    void setAimLineWidth(int aimLineWidth);
    int aimLineWidth() const;

    void setAimColor(int aimColor);
    int aimColor() const;

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QPointF m_aimPosition;
    int m_aimSize;
    int m_aimLineWidth;
    int m_aimColor;
};

#endif