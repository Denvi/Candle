#pragma once

#include <QWidget>
#include <QVector3D>
#include <QTime>

class GLWidget;

class Overlay : public QWidget
{
    Q_OBJECT
public:
    explicit Overlay(GLWidget *parent = 0);

private:
    GLWidget *m_parent;

protected:
    void paintEvent(QPaintEvent *pe) override;
};