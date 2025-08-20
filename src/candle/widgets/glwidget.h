// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#ifndef GLWIDGET_H
#define GLWIDGET_H

#ifndef GLES
#include <QGLWidget>
#else
#include <QOpenGLWidget>
#endif

#include <QTimer>
#include <QTime>
#include "../drawers/shaderdrawable.h"

#ifdef GLES
class GLWidget : public QOpenGLWidget
#else
class GLWidget : public QGLWidget, protected QOpenGLFunctions
#endif
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void addDrawable(ShaderDrawable *drawable);
    void updateBounds(ShaderDrawable *drawable);
    void fitDrawable(ShaderDrawable *drawable = NULL);
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

    QColor colorBackground() const;
    void setColorBackground(const QColor &colorBackground);

    QColor colorText() const;
    void setColorText(const QColor &colorText);

    double pointSize() const;
    void setPointSize(double pointSize);

    bool vsync() const;
    void setVsync(bool vsync);

    QString speedState() const;
    void setSpeedState(const QString &speedState);

    QString pinState() const;
    void setPinState(const QString &pinState);

signals:
    void rotationChanged();
    void resized();

public slots:

private slots:
    void onFramesTimer();
    void viewAnimation();

private:
    QPointF m_rot;
    QPointF m_storedRot;
    QPointF m_pan;
    QPointF m_storedPan;

    QVector3D m_lookAt;

    QPoint m_lastPos;
    double m_zoom;
    double m_distance;

    QVector3D m_viewLowerBounds;
    QVector3D m_viewUpperBounds;
    QVector3D m_viewRanges;

    QVector3D m_modelLowerBounds;
    QVector3D m_modelUpperBounds;
    QVector3D m_modelRanges;

    double m_lineWidth;
    double m_pointSize;
    bool m_antialiasing;
    bool m_msaa;
    bool m_vsync;
    bool m_zBuffer;
    int m_frames;
    int m_fps;
    int m_targetFps;
    int m_animationFrame;
    QTime m_spendTime;
    QTime m_estimatedTime;
    QBasicTimer m_timerPaint;

    QPointF m_rotAnimationStart;
    QPointF m_rotAnimationTarget;

    bool m_animateView;
    QString m_parserStatus;
    QString m_speedState;
    QString m_pinState;
    QString m_bufferState;
    bool m_updatesEnabled;

    double normalizeAngle(double angle);
    double calculateVolume(QVector3D size);
    void beginViewAnimation();
    void stopViewAnimation();

    QList<ShaderDrawable*> m_shaderDrawables;
    QOpenGLShaderProgram *m_shaderProgram;
    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_viewMatrix;

    double m_planeDepth;
    double m_windowSizeWorld;

    QColor m_colorBackground;
    QColor m_colorText;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void updateProjection();
    void updateView();
#ifdef GLES
    void paintGL();
#else
    void paintEvent(QPaintEvent *pe);
#endif

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *we);

    void timerEvent(QTimerEvent *);
};

#endif // GLWIDGET_H
