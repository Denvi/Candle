// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "glwidget.h"
#include "drawers/tooldrawer.h"
#include <QDebug>
#include <QtWidgets>
#include <QPainter>
#include <QEasingCurve>
#include <iostream>

#ifdef GLES
#include <GLES/gl.h>
#endif

#define ZOOMSTEP 1.1
#define DEFAULT_ZOOM 200
#define MIN_ZOOM  0.2

#ifdef GLES
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_shaderProgram(0)
#else
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent), m_shaderProgram(0)
#endif

{
    m_animateView = false;
    m_updatesEnabled = false;

    m_xRot = 90;
    m_yRot = 0;

    m_xRotTarget = 90;
    m_yRotTarget = 0;

    m_zoomDistance = DEFAULT_ZOOM;

    m_lookAt = QVector3D(0,0,0);
    
    m_perspective = true;

    m_fov = 30;
    m_near = 0.5;
    m_far = 5000.0;

    m_xMin = 0;
    m_xMax = 0;
    m_yMin = 0;
    m_yMax = 0;
    m_zMin = 0;
    m_zMax = 0;
    m_xSize = 0;
    m_ySize = 0;
    m_zSize = 0;

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

    m_zoomDistance = DEFAULT_ZOOM;

    if (drawable != NULL) {
        updateExtremes(drawable);

        double largestSize = qMax(qMax(m_xSize, m_ySize), m_zSize);       

        double newZoom = largestSize / (1.25 * tan((m_fov * 0.0174533) / 2.0));
        m_zoomDistance = newZoom > 0 ? qMax(newZoom, MIN_ZOOM) : DEFAULT_ZOOM;

        m_lookAt = QVector3D(
            m_xSize / 2 + m_xMin,
            m_ySize / 2 + m_yMin,
            m_zSize / 2 + m_zMin
        );
    } else {
        m_lookAt = QVector3D(0,0,0);

        m_xMin = 0;
        m_xMax = 0;
        m_yMin = 0;
        m_yMax = 0;
        m_zMin = 0;
        m_zMax = 0;

        m_xSize = 0;
        m_ySize = 0;
        m_zSize = 0;
    }

    updateProjection();
    updateView();
}

void GLWidget::updateExtremes(ShaderDrawable *drawable)
{
    if (!qIsNaN(drawable->getMinimumExtremes().x())) m_xMin = drawable->getMinimumExtremes().x(); else m_xMin = 0;
    if (!qIsNaN(drawable->getMaximumExtremes().x())) m_xMax = drawable->getMaximumExtremes().x(); else m_xMax = 0;
    if (!qIsNaN(drawable->getMinimumExtremes().y())) m_yMin = drawable->getMinimumExtremes().y(); else m_yMin = 0;
    if (!qIsNaN(drawable->getMaximumExtremes().y())) m_yMax = drawable->getMaximumExtremes().y(); else m_yMax = 0;
    if (!qIsNaN(drawable->getMinimumExtremes().z())) m_zMin = drawable->getMinimumExtremes().z(); else m_zMin = 0;
    if (!qIsNaN(drawable->getMaximumExtremes().z())) m_zMax = drawable->getMaximumExtremes().z(); else m_zMax = 0;

    m_xSize = m_xMax - m_xMin;
    m_ySize = m_yMax - m_yMin;
    m_zSize = m_zMax - m_zMin;
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

    m_xRot = m_xRotStored + double(m_xRotTarget - m_xRotStored) * val;
    m_yRot = m_yRotStored + double(m_yRotTarget - m_yRotStored) * val;

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
}

bool GLWidget::zBuffer() const
{
    return m_zBuffer;
}

void GLWidget::setZBuffer(bool zBuffer)
{
    m_zBuffer = zBuffer;
}

double GLWidget::fov() {
    return m_fov;
}

void GLWidget::setFov(double fov) {
    m_fov = fov;
    updateProjection();
}

double GLWidget::nearPlane() {
    return m_near;
}

void GLWidget::setNearPlane(double near) {
    m_near = near;
    updateProjection();
}

double GLWidget::farPlane() {
    return m_far;
}

void GLWidget::setFarPlane(double far) {
    m_far = far;
    updateProjection();
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
    m_xRotTarget = 90;
    m_yRotTarget = m_yRot > 180 ? 360 : 0;
    beginViewAnimation();
}

void GLWidget::setFrontView()
{
    m_xRotTarget = 0;
    m_yRotTarget = m_yRot > 180 ? 360 : 0;
    beginViewAnimation();
}

void GLWidget::setLeftView()
{
    m_xRotTarget = 0;
    m_yRotTarget = m_yRot > 270 ? 450 : 90;
    beginViewAnimation();
}

void GLWidget::toggleProjectionType() {
    m_perspective = !m_perspective;
    updateProjection();
    updateView();
}

int GLWidget::fps()
{
    return m_targetFps;
}

void GLWidget::setIsometricView()
{
    m_perspective = false;
    updateProjection();
    m_xRotTarget = 35.264;
    m_yRotTarget = m_yRot > 180 ? 405 : 45;
    beginViewAnimation();
}

void GLWidget::beginViewAnimation() {
    m_xRotStored = m_xRot;
    m_yRotStored = m_yRot;
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
    m_timerPaint.stop();
    m_timerPaint.start(m_vsync ? 0 : 1000 / fps, Qt::PreciseTimer, this);
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
    // Reset projection
    m_projectionMatrix.setToIdentity();

    double asp = (double)width() / height();
    double orthoSize = m_zoomDistance * tan((m_fov * 0.0174533) / 2.0);

    // perspective / orthographic projection
    if (m_perspective)
        m_projectionMatrix.perspective(m_fov, asp, m_near, m_far);
    else
        m_projectionMatrix.ortho(-orthoSize * asp, orthoSize * asp, -orthoSize, orthoSize, -m_far/2.0, m_far/2.0);
}

void GLWidget::updateView()
{
    // Set view matrix
    m_viewMatrix.setToIdentity();

    double angY = M_PI / 180 * m_yRot;
    double angX = M_PI / 180 * m_xRot;

    QVector3D eye(cos(angX) * sin(angY), sin(angX), cos(angX) * cos(angY));
    QVector3D up(fabs(m_xRot) == 90 ? -sin(angY + (m_xRot < 0 ? M_PI : 0)) : 0, cos(angX), fabs(m_xRot) == 90 ? -cos(angY + (m_xRot < 0 ? M_PI : 0)) : 0);
    
    m_viewMatrix.lookAt(eye * m_zoomDistance, QVector3D(0,0,0), up.normalized());

    m_viewMatrix.rotate(-90, 1.0, 0.0, 0.0);
    m_viewMatrix.translate(-m_lookAt);
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
        m_shaderProgram->setUniformValue("mvp_matrix", m_projectionMatrix * m_viewMatrix);
        m_shaderProgram->setUniformValue("mv_matrix", m_viewMatrix);

        // Update geometries in current opengl context
        foreach (ShaderDrawable *drawable, m_shaderDrawables)
            if (drawable->needsUpdateGeometry()) drawable->updateGeometry(m_shaderProgram);

        // Draw geometries
        foreach (ShaderDrawable *drawable, m_shaderDrawables) {
            drawable->draw(m_shaderProgram);
            if (drawable->visible()) vertices += drawable->getVertexCount();
        }

        m_shaderProgram->release();
    }

    // Draw 2D
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);

    painter.endNativePainting();

    QPen pen(m_colorText);
    painter.setPen(pen);

    double x = 10;
    double y = this->height() - 60;

    painter.drawText(QPoint(x, y), QString("X: %1 ... %2").arg(m_xMin, 0, 'f', 3).arg(m_xMax, 0, 'f', 3));
    painter.drawText(QPoint(x, y + 15), QString("Y: %1 ... %2").arg(m_yMin, 0, 'f', 3).arg(m_yMax, 0, 'f', 3));
    painter.drawText(QPoint(x, y + 30), QString("Z: %1 ... %2").arg(m_zMin, 0, 'f', 3).arg(m_zMax, 0, 'f', 3));
    painter.drawText(QPoint(x, y + 45), QString("%1 / %2 / %3").arg(m_xSize, 0, 'f', 3).arg(m_ySize, 0, 'f', 3).arg(m_zSize, 0, 'f', 3));

    QFontMetrics fm(painter.font());

    painter.drawText(QPoint(x, fm.height() + 10), m_parserStatus);
    painter.drawText(QPoint(x, fm.height() * 2 + 10), m_speedState);
    painter.drawText(QPoint(x, fm.height() * 3 + 10), m_pinState);

    QString str = QString(tr("Vertices: %1")).arg(vertices);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + 30), str);
    str = QString("FPS: %1").arg(m_fps);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + 45), str);

    str = m_spendTime.toString("hh:mm:ss") + " / " + m_estimatedTime.toString("hh:mm:ss");
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y), str);

    str = m_bufferState;
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + 15), str);

    m_frames++;

#ifdef GLES
    update();
#endif
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
    m_xLastRot = m_xRot;
    m_yLastRot = m_yRot;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::MiddleButton && !(event->modifiers() & Qt::ShiftModifier)) || event->buttons() & Qt::LeftButton) {

        stopViewAnimation();

        m_yRot = normalizeAngle(m_yLastRot - (event->pos().x() - m_lastPos.x()) * 0.5);
        m_xRot = m_xLastRot + (event->pos().y() - m_lastPos.y()) * 0.5;

        if (m_xRot < -90) m_xRot = -90;
        if (m_xRot > 90) m_xRot = 90;

        updateView();
        emit rotationChanged();
    }

    if ((event->buttons() & Qt::MiddleButton && event->modifiers() & Qt::ShiftModifier) || event->buttons() & Qt::RightButton) {

        // Get world to clip
        QMatrix4x4 mvp(m_projectionMatrix * m_viewMatrix);
        // Get clip to world
        QMatrix4x4 mvpi(mvp.inverted());

        QVector4D centerVector(mvp * QVector4D(m_lookAt.x(),m_lookAt.y(),m_lookAt.z(), 1.0));

        // Get last mouse XY in clip
        QVector4D lastMouseInWorld(
            (m_lastPos.x() / (double)width()) * 2.0 - 1.0,
            -((m_lastPos.y() / (double)height()) * 2.0 - 1.0),
            0, 1.0
        );
        // Project last mouse pos to world
        lastMouseInWorld = mvpi * lastMouseInWorld * centerVector.w();

        // Get current mouse XY in clip
        QVector4D currentMouseInWorld(
            (event->pos().x() / (double)width()) * 2.0 - 1.0,
            -((event->pos().y() / (double)height()) * 2.0 - 1.0),
            0, 1.0
        );
        // Project current mouse pos to world
        currentMouseInWorld = mvpi * currentMouseInWorld * centerVector.w();

        //currentMouseInWorld /= currentMouseInWorld.w();

        // Get difference
        QVector4D difference = currentMouseInWorld - lastMouseInWorld;

        // Subtract difference from center point
        m_lookAt -= QVector3D(difference.x(), difference.y(), difference.z());

        m_lastPos = event->pos();

        updateView();
    }
}

void GLWidget::wheelEvent(QWheelEvent *we)
{
    if (m_zoomDistance > MIN_ZOOM && we->delta() < 0)
        m_zoomDistance /= ZOOMSTEP;
    else if (we->delta() > 0)
        m_zoomDistance *= ZOOMSTEP;

    if (!m_perspective) updateProjection();
    else updateView();
}

void GLWidget::timerEvent(QTimerEvent *te)
{
    if (te->timerId() == m_timerPaint.timerId()) {
        if (m_animateView) viewAnimation();
#ifndef GLES
        if (m_updatesEnabled) update();
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
