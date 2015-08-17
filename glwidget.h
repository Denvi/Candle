// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

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

    void setIsometricView();
    void setTopView();
    void setFrontView();
    void setLeftView();

    int fps();
    void setFps(int fps);

    QString parserStatus() const;
    void setParserStatus(const QString &parserStatus);

    QString bufferState() const;
    void setBufferState(const QString &bufferState);

    bool zBuffer() const;
    void setZBuffer(bool zBuffer);

    bool updatesEnabled() const;
    void setUpdatesEnabled(bool updatesEnabled);

    bool msaa() const;
    void setMsaa(bool msaa);

signals:
    void rotationChanged();

public slots:

private slots:
    void onFramesTimer();
    void viewAnimation();

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
    bool m_msaa;
    bool m_zBuffer;
    int m_frames = 0;
    int m_fps = 0;
    int m_targetFps;
    int m_animationFrame;
    QTime m_spendTime;
    QTime m_estimatedTime;    
//    QTimer m_changeViewTimer;
    QBasicTimer m_timerAnimation;
    double m_xRotTarget, m_yRotTarget;
    double m_xRotStored, m_yRotStored;
    bool m_animateView;
    QString m_parserStatus;
    QString m_bufferState;
    bool m_updatesEnabled;

    double normalizeAngle(double angle);
    double calculateVolume(QVector3D size);    
    void beginViewAnimation();
    void stopViewAnimation();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void updateProjection();
    void paintEvent(QPaintEvent *pe);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *we);

    void timerEvent(QTimerEvent *);
};

#endif // GLWIDGET_H
