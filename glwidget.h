#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QTime>
#include "GLU.h"
#include "gldrawable.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void addDrawable(GLDrawable* drawable);    
    void fitDrawables();
    bool antialiasing() const;
    void setAntialiasing(bool antialiasing);

    QTime spendTime() const;
    void setSpendTime(const QTime &spendTime);

    QTime estimatedTime() const;
    void setEstimatedTime(const QTime &estimatedTime);

    double lineWidth() const;
    void setLineWidth(double lineWidth);

signals:

public slots:

private slots:
    void onFramesTimer();

private:
    double m_xRot, m_yRot, m_xLastRot, m_yLastRot;
    double m_xPan, m_yPan, m_xLastPan, m_yLastPan;
    double m_xLookAt, m_yLookAt, m_zLookAt;
    QPoint m_lastPos;
    double m_zoom;
    double m_distance;
    QList<GLDrawable*> m_drawables;
    double m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax, m_xSize, m_ySize, m_zSize;
    double m_lineWidth;
    bool m_antialiasing;
    int m_frames = 0;
    int m_fps = 0;
    QTime m_spendTime;
    QTime m_estimatedTime;

    double normalizeAngle(double angle);
    double calculateVolume(QVector3D size);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void updateProjection();
    void paintEvent(QPaintEvent *pe);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *we);
};

#endif // GLWIDGET_H
