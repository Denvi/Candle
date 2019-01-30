// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "glwidget.h"
#include "drawers/tooldrawer.h"
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
    m_animateView = false;
    m_updatesEnabled = false;

    m_xRot = 90;
    m_yRot = 0;

    m_xRotTarget = 90;
    m_yRotTarget = 0;

    m_zoom = 1;

    m_xPan = 0;
    m_yPan = 0;
    m_distance = 100;

    m_xLookAt = 0;
    m_yLookAt = 0;
    m_zLookAt = 0;

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

    if (drawable != NULL) {
        updateExtremes(drawable);

        double a = m_ySize / 2 / 0.25 * 1.3
                + (m_zMax - m_zMin) / 2;
        double b = m_xSize / 2 / 0.25 * 1.3
                / ((double)this->width() / this->height())
                + (m_zMax - m_zMin) / 2;
        m_distance = qMax(a, b);

        if (m_distance == 0) m_distance = 200;

        m_xLookAt = (m_xMax - m_xMin) / 2 + m_xMin;
        m_zLookAt = -((m_yMax - m_yMin) / 2 + m_yMin);
        m_yLookAt = (m_zMax - m_zMin) / 2 + m_zMin;
    } else {
        m_distance = 200;
        m_xLookAt = 0;
        m_yLookAt = 0;
        m_zLookAt = 0;

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

    m_xPan = 0;
    m_yPan = 0;
    m_zoom = 1;

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

int GLWidget::fps()
{
    return m_targetFps;
}

void GLWidget::setIsometricView()
{
    m_xRotTarget = 45;
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
    m_projectionMatrix.frustum((-0.5 + m_xPan) * asp, (0.5 + m_xPan) * asp, -0.5 + m_yPan, 0.5 + m_yPan, 2, m_distance * 2);
}

void GLWidget::updateView()
{
    // Set view matrix
    m_viewMatrix.setToIdentity();

    double r = m_distance;
    double angY = M_PI / 180 * m_yRot;
    double angX = M_PI / 180 * m_xRot;

    QVector3D eye(r * cos(angX) * sin(angY) + m_xLookAt, r * sin(angX) + m_yLookAt, r * cos(angX) * cos(angY) + m_zLookAt);
    QVector3D center(m_xLookAt, m_yLookAt, m_zLookAt);
    QVector3D up(fabs(m_xRot) == 90 ? -sin(angY + (m_xRot < 0 ? M_PI : 0)) : 0, cos(angX), fabs(m_xRot) == 90 ? -cos(angY + (m_xRot < 0 ? M_PI : 0)) : 0);

    m_viewMatrix.lookAt(eye, center, up.normalized());

    m_viewMatrix.translate(m_xLookAt, m_yLookAt, m_zLookAt);
    m_viewMatrix.scale(m_zoom, m_zoom, m_zoom);
    m_viewMatrix.translate(-m_xLookAt, -m_yLookAt, -m_zLookAt);

    m_viewMatrix.rotate(-90, 1.0, 0.0, 0.0);
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
    m_xLastPan = m_xPan;
    m_yLastPan = m_yPan;
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
        m_xPan = m_xLastPan - (event->pos().x() - m_lastPos.x()) * 1 / (double)width();
        m_yPan = m_yLastPan + (event->pos().y() - m_lastPos.y()) * 1 / (double)height();

        updateProjection();
    }
}

void GLWidget::wheelEvent(QWheelEvent *we)
{
    if (m_zoom > 0.1 && we->delta() < 0) {
        m_xPan -= ((double)we->pos().x() / width() - 0.5 + m_xPan) * (1 - 1 / ZOOMSTEP);
        m_yPan += ((double)we->pos().y() / height() - 0.5 - m_yPan) * (1 - 1 / ZOOMSTEP);

        m_zoom /= ZOOMSTEP;
    }
    else if (m_zoom < 10 && we->delta() > 0)
    {
        m_xPan -= ((double)we->pos().x() / width() - 0.5 + m_xPan) * (1 - ZOOMSTEP);
        m_yPan += ((double)we->pos().y() / height() - 0.5 - m_yPan) * (1 - ZOOMSTEP);

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
