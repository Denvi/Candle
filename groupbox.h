#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QWidget>
#include <QGroupBox>

class GroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit GroupBox(QWidget *parent = 0);

signals:
    void mouseMoved(int dx, int dy);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPoint m_previousPos;
};

#endif // GROUPBOX_H
