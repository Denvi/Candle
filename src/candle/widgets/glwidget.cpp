// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "glwidget.h"
#include "../drawers/tooldrawer.h"
#include <QDebug>
#include <QtWidgets>
#include <QPainter>
#include <QEasingCurve>

#ifdef GLES
#include <GLES/gl.h>
#endif

#define ZOOMSTEP 1.1

#ifdef GLES
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_shaderProgram(0)
#else
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent), m_shaderProgram(0)
#endif

{
    m_frames = 0;
    m_fps = 0;

    m_animateView = false;
    m_updatesEnabled = false;

    m_rot = QPointF(90.0, 0.0);
    m_rotAnimationTarget = m_rot;

    m_zoom = 1;
    m_distance = 100;

    updateProjection();
    updateView();

    m_spendTime.setHMS(0, 0, 0);
    m_estimatedTime.setHMS(0, 0, 0);

    m_vsync = false;
    m_targetFps = 60;

    QTimer::singleShot(1000, this, SLOT(onFramesTimer()));
}

GLWidget::~GLWidget()
{
    if (m_shaderProgram) {
        delete m_shaderProgram;
    }
}

double GLWidget::calculateVolume(QVector3D size) {
    return size.x() * size.y() * size.z();
}

void GLWidget::addDrawable(ShaderDrawable *drawable)
{
    m_shaderDrawables.append(drawable);
}

void GLWidget::fitDrawable(ShaderDrawable *drawable)
{
    stopViewAnimation();

    if (drawable != NULL) {
        updateBounds(drawable);

        double a = m_viewRanges.y() / 2 / 0.25 * 1.3
                + (m_viewUpperBounds - m_viewLowerBounds).z() / 2;
        double b = m_viewRanges.x() / 2 / 0.25 * 1.3
                / ((double)this->width() / this->height())
                + (m_viewUpperBounds - m_viewLowerBounds).z() / 2;
        m_distance = qMax(a, b);

        if (m_distance == 0) m_distance = 200;

        m_lookAt = QVector3D(
                (m_viewUpperBounds.x() - m_viewLowerBounds.x()) / 2 + m_viewLowerBounds.x(),
                (m_viewUpperBounds.z() - m_viewLowerBounds.z()) / 2 + m_viewLowerBounds.z(),
                -((m_viewUpperBounds.y() - m_viewLowerBounds.y()) / 2 + m_viewLowerBounds.y())
        );

    } else {
        m_distance = 200;
        m_lookAt = QVector3D();
        m_viewLowerBounds = QVector3D();
        m_viewUpperBounds = QVector3D();
        m_viewRanges = QVector3D();
        m_modelLowerBounds = QVector3D();
        m_modelUpperBounds = QVector3D();
        m_modelRanges = QVector3D();
    }

    m_pan = QPointF();
    m_zoom = 1;

    updateProjection();
    updateView();
}

void GLWidget::updateBounds(ShaderDrawable *drawable)
{
    m_viewLowerBounds = Util::nAssign(drawable->getViewLowerBounds());
    m_viewUpperBounds = Util::nAssign(drawable->getViewUpperBounds());
    m_viewRanges = drawable->getViewRanges();

    m_modelLowerBounds = Util::nAssign(drawable->getModelLowerBounds());
    m_modelUpperBounds = Util::nAssign(drawable->getModelUpperBounds());
    m_modelRanges = drawable->getModelRanges();
}

bool GLWidget::antialiasing() const
{
    return m_antialiasing;
}

void GLWidget::setAntialiasing(bool antialiasing)
{
    m_antialiasing = antialiasing;
}

void GLWidget::onFramesTimer()
{
    m_fps = m_frames;
    m_frames = 0;

    QTimer::singleShot(1000, this, SLOT(onFramesTimer()));
}

void GLWidget::viewAnimation()
{
    double t = (double)m_animationFrame++ / (m_fps * 0.2);

    if (t >= 1) stopViewAnimation();

    QEasingCurve ec(QEasingCurve::OutExpo);
    double val = ec.valueForProgress(t);

    m_rot = m_rotAnimationStart + (m_rotAnimationTarget - m_rotAnimationStart) * val;

    updateView();
}

QString GLWidget::pinState() const
{
    return m_pinState;
}

void GLWidget::setPinState(const QString &pinState)
{
    m_pinState = pinState;
}

QString GLWidget::speedState() const
{
    return m_speedState;
}

void GLWidget::setSpeedState(const QString &additionalStatus)
{
    m_speedState = additionalStatus;
}

bool GLWidget::vsync() const
{
    return m_vsync;
}

void GLWidget::setVsync(bool vsync)
{
    m_vsync = vsync;
}

bool GLWidget::msaa() const
{
    return m_msaa;
}

void GLWidget::setMsaa(bool msaa)
{
    m_msaa = msaa;
}

bool GLWidget::updatesEnabled() const
{
    return m_updatesEnabled;
}

void GLWidget::setUpdatesEnabled(bool updatesEnabled)
{
    m_updatesEnabled = updatesEnabled;

    if (updatesEnabled) {
        m_timerPaint.start(m_vsync ? 0 : 1000 / m_targetFps, Qt::PreciseTimer, this);
    } else {
        m_timerPaint.stop();
    }
}

bool GLWidget::zBuffer() const
{
    return m_zBuffer;
}

void GLWidget::setZBuffer(bool zBuffer)
{
    m_zBuffer = zBuffer;
}

QString GLWidget::bufferState() const
{
    return m_bufferState;
}

void GLWidget::setBufferState(const QString &bufferState)
{
    m_bufferState = bufferState;
}

QString GLWidget::parserStatus() const
{
    return m_parserStatus;
}

void GLWidget::setParserStatus(const QString &parserStatus)
{
    m_parserStatus = parserStatus;
}


double GLWidget::lineWidth() const
{
    return m_lineWidth;
}

void GLWidget::setLineWidth(double lineWidth)
{
    m_lineWidth = lineWidth;
}

void GLWidget::setTopView()
{
    m_rotAnimationTarget = QPointF(90, m_rot.y() > 180 ? 360 : 0);
    beginViewAnimation();
}

void GLWidget::setFrontView()
{
    m_rotAnimationTarget = QPointF(0, m_rot.y() > 180 ? 360 : 0);
    beginViewAnimation();
}

void GLWidget::setLeftView()
{
    m_rotAnimationTarget = QPointF(0, m_rot.y() > 270 ? 450 : 90);
    beginViewAnimation();
}

int GLWidget::fps()
{
    return m_targetFps;
}

void GLWidget::setIsometricView()
{
    m_rotAnimationTarget = QPointF(45, m_rot.y() > 180 ? 405 : 45);
    beginViewAnimation();
}

void GLWidget::beginViewAnimation() {
    m_rotAnimationStart = m_rot;
    m_animationFrame = 0;
    m_animateView = true;
}

void GLWidget::stopViewAnimation() {
    m_animateView = false;
}
QColor GLWidget::colorText() const
{
    return m_colorText;
}

void GLWidget::setColorText(const QColor &colorText)
{
    m_colorText = colorText;
}

QColor GLWidget::colorBackground() const
{
    return m_colorBackground;
}

void GLWidget::setColorBackground(const QColor &colorBackground)
{
    m_colorBackground = colorBackground;
}

void GLWidget::setFps(int fps)
{
    if (fps <= 0) return;
    m_targetFps = fps;
    setUpdatesEnabled(m_updatesEnabled);
}

QTime GLWidget::estimatedTime() const
{
    return m_estimatedTime;
}

void GLWidget::setEstimatedTime(const QTime &estimatedTime)
{
    m_estimatedTime = estimatedTime;
}

QTime GLWidget::spendTime() const
{
    return m_spendTime;
}

void GLWidget::setSpendTime(const QTime &spendTime)
{
    m_spendTime = spendTime;
}

void GLWidget::initializeGL()
{
#ifndef GLES
    // Initialize functions
    initializeOpenGLFunctions();
#endif

    // Create shader program
    m_shaderProgram = new QOpenGLShaderProgram();

    if (m_shaderProgram) {
        // Compile vertex shader
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl");
        // Compile fragment shader
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl");
        // Link shader pipeline
        m_shaderProgram->link();
        qDebug() << "shader program created";
    }
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    updateProjection();
    emit resized();
}

void GLWidget::updateProjection()
{
    const double zNear = 2.0;
    const double zFar = m_distance * 2;

    // Reset projection
    m_projectionMatrix.setToIdentity();

    double asp = (double)width() / height();
    m_projectionMatrix.frustum((-0.5 + m_pan.x()) * asp, (0.5 + m_pan.x()) * asp,
                               -0.5 + m_pan.y(), 0.5 + m_pan.y(), zNear, zFar);

    // Update xy-plane z-depth
    double z = m_distance + (m_viewUpperBounds + m_viewLowerBounds).z() / 2 * m_zoom;
    m_planeDepth = (1 / z - 1 / zNear) / (1 / zFar - 1 / zNear) * 2 - 1;
}

void GLWidget::updateView()
{
    // Set view matrix
    m_viewMatrix.setToIdentity();

    QPointF ang = m_rot * M_PI / 180;

    QVector3D eye = m_lookAt + QVector3D(
            cos(ang.x()) * sin(ang.y()),
            sin(ang.x()),
            cos(ang.x()) * cos(ang.y())
    ) * m_distance;

    QVector3D up(fabs(m_rot.x()) == 90 ? -sin(ang.y() + (m_rot.x() < 0 ? M_PI : 0)) : 0,
                 cos(ang.x()),
                 fabs(m_rot.x()) == 90 ? -cos(ang.y() + (m_rot.x() < 0 ? M_PI : 0)) : 0);

    m_viewMatrix.lookAt(eye, m_lookAt, up.normalized());

    m_viewMatrix.translate(m_lookAt);
    m_viewMatrix.scale(m_zoom);
    m_viewMatrix.translate(-m_lookAt);

    m_viewMatrix.rotate(-90, 1.0, 0.0, 0.0);

    // Update visualizer window size in world coordinates
    QMatrix4x4 ivp = (m_projectionMatrix * m_viewMatrix).inverted();
    m_windowSizeWorld = (ivp * QVector3D(0, 1, m_planeDepth) - ivp * QVector3D(0, 0, m_planeDepth)).length() * 2.0;
}

#ifdef GLES
void GLWidget::paintGL() {
#else
void GLWidget::paintEvent(QPaintEvent *pe) {
    Q_UNUSED(pe)
#endif
    QPainter painter(this);

    // Segment counter
    int vertices = 0;

    painter.beginNativePainting();

    // Clear viewport
    glClearColor(m_colorBackground.redF(), m_colorBackground.greenF(), m_colorBackground.blueF(), 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Shader drawable points
    glEnable(GL_PROGRAM_POINT_SIZE);

    // Update settings
    if (m_antialiasing) {
        if (m_msaa) glEnable(GL_MULTISAMPLE); else {
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_LINE_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_POINT_SMOOTH);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
        }
    }
    if (m_zBuffer) glEnable(GL_DEPTH_TEST);

    if (m_shaderProgram) {
        // Draw 3d
        m_shaderProgram->bind();

        // Set modelview-projection matrix
        m_shaderProgram->setUniformValue("p_matrix", m_projectionMatrix);
        m_shaderProgram->setUniformValue("v_matrix", m_viewMatrix);

        // Update geometries in current opengl context
        foreach (ShaderDrawable *drawable, m_shaderDrawables) {
            if (drawable->needsUpdateGeometry()) drawable->updateGeometry(m_shaderProgram);
        }

        // Draw geometries
        foreach (ShaderDrawable *drawable, m_shaderDrawables) {
            if (drawable->visible()) {
                if (drawable->windowScaling()) {
                    drawable->setWorldScale(m_windowSizeWorld * drawable->windowScale());
                }
                m_shaderProgram->setUniformValue("m_matrix", drawable->modelMatrix());
                drawable->draw(m_shaderProgram);
                vertices += drawable->getVertexCount();
            }
        }

        m_shaderProgram->release();
    }

    // Draw 2D
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);

    painter.endNativePainting();
    painter.setRenderHint(QPainter::Antialiasing);

    QMatrix4x4 w;
    w.scale(width() / 2, -height() / 2);
    w.translate(1, -1);
    w *= m_projectionMatrix * m_viewMatrix;

    foreach (ShaderDrawable *drawable, m_shaderDrawables) {
        if (drawable->visible()) {
            painter.save();
            drawable->drawPainter(painter, w * drawable->modelMatrix(), height() / m_windowSizeWorld);
            painter.restore();
        }
    }

    QPen pen(m_colorText);
    painter.setPen(pen);

    QFontMetrics fm(painter.font());
    double x = 10;
    double y = this->height() - fm.height() * 3 - 10;

    painter.drawText(QPoint(x, y), QString("X: %1 ... %2").arg(m_modelLowerBounds.x(), 0, 'f', 3)
        .arg(m_modelUpperBounds.x(), 0, 'f', 3));
    painter.drawText(QPoint(x, y + fm.height()), QString("Y: %1 ... %2").arg(m_modelLowerBounds.y(), 0, 'f', 3)
        .arg(m_modelUpperBounds.y(), 0, 'f', 3));
    painter.drawText(QPoint(x, y + fm.height() * 2), QString("Z: %1 ... %2").arg(m_modelLowerBounds.z(), 0, 'f', 3)
        .arg(m_modelUpperBounds.z(), 0, 'f', 3));
    painter.drawText(QPoint(x, y + fm.height() * 3), QString("%1 / %2 / %3").arg(m_modelRanges.x(), 0, 'f', 3)
        .arg(m_modelRanges.y(), 0, 'f', 3).arg(m_modelRanges.z(), 0, 'f', 3));


    painter.drawText(QPoint(x, fm.height() + 10), m_parserStatus);
    painter.drawText(QPoint(x, fm.height() * 2 + 10), m_speedState);
    painter.drawText(QPoint(x, fm.height() * 3 + 10), m_pinState);

    QString str = QString(tr("Vertices: %1")).arg(vertices);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + fm.height() * 2), str);
    str = QString("FPS: %1").arg(m_fps);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + fm.height() * 3), str);

    str = m_spendTime.toString("hh:mm:ss") + " / " + m_estimatedTime.toString("hh:mm:ss");
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y), str);

    str = m_bufferState;
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + fm.height()), str);

    m_frames++;

#ifdef GLES
    update();
#endif
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();

    m_storedRot = m_rot;
    m_storedPan = m_pan;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::MiddleButton && !(event->modifiers() & Qt::ShiftModifier)) 
        || (event->buttons() & Qt::LeftButton && !(event->modifiers() & Qt::ShiftModifier))) {

        stopViewAnimation();

        m_rot.setY(normalizeAngle(m_storedRot.y() - (event->pos().x() - m_lastPos.x()) * 0.5));
        m_rot.setX(m_storedRot.x() + (event->pos().y() - m_lastPos.y()) * 0.5);

        m_rot.setX(qBound<double>(-90, m_rot.x(), 90));

        updateView();
        emit rotationChanged();
    }

    if ((event->buttons() & Qt::MiddleButton && event->modifiers() & Qt::ShiftModifier) 
        || event->buttons() & Qt::RightButton
        || (event->buttons() & Qt::LeftButton && (event->modifiers() & Qt::ShiftModifier))) {
        m_pan.setX(m_storedPan.x() - (event->pos().x() - m_lastPos.x()) * 1 / (double)width());
        m_pan.setY(m_storedPan.y() + (event->pos().y() - m_lastPos.y()) * 1 / (double)height());

        updateProjection();
    }
}

void GLWidget::wheelEvent(QWheelEvent *we)
{
    if (m_zoom > 0.1 && we->delta() < 0) {
        m_pan.setX(m_pan.x() - ((double)we->pos().x() / width() - 0.5 + m_pan.x()) * (1 - 1 / ZOOMSTEP));
        m_pan.setY(m_pan.y() + ((double)we->pos().y() / height() - 0.5 - m_pan.y()) * (1 - 1 / ZOOMSTEP));

        m_zoom /= ZOOMSTEP;
    }
    else if (m_zoom < 10 && we->delta() > 0)
    {
        m_pan.setX(m_pan.x() - ((double)we->pos().x() / width() - 0.5 + m_pan.x()) * (1 - ZOOMSTEP));
        m_pan.setY(m_pan.y() + ((double)we->pos().y() / height() - 0.5 - m_pan.y()) * (1 - ZOOMSTEP));

        m_zoom *= ZOOMSTEP;
    }

    updateProjection();
    updateView();
}

void GLWidget::timerEvent(QTimerEvent *te)
{
    if (te->timerId() == m_timerPaint.timerId()) {
        if (m_animateView) viewAnimation();
#ifndef GLES
        update();
#endif
    } else {
#ifdef GLES
        QOpenGLWidget::timerEvent(te);
#else
        QGLWidget::timerEvent(te);
#endif
    }
}

double GLWidget::normalizeAngle(double angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;

    return angle;
}
