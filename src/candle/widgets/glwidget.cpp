// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "glwidget.h"
#include <QtWidgets>
#include <QEasingCurve>

#define ZOOMSTEP 1.1

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_shaderProgram(0)
{
    m_frames = 0;
    m_fps = 0;

    m_animateView = false;
    m_updatesEnabled = false;

    m_rot = QPointF(90.0, 0.0);
    m_rotAnimationTarget = m_rot;

    m_zoom = 1;
    m_distance = 100;
    m_perspective = false;

    m_gestureProcessing = false;

    updateProjection();
    updateView();

    m_spendTime.setHMS(0, 0, 0);
    m_estimatedTime.setHMS(0, 0, 0);

    m_vsync = false;
    m_targetFps = 60;

    m_updating = false;

    setAttribute(Qt::WA_AcceptTouchEvents, true);
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);

    QSurfaceFormat fmt = format();
    fmt.setSamples(8);
    fmt.setSwapInterval(0);
    setFormat(fmt);

    m_overlay = new Overlay(this);

    QTimer::singleShot(1000, this, &GLWidget::onFramesTimer);
}

GLWidget::~GLWidget()
{
    makeCurrent();

    for (auto drawable : m_shaderDrawables) {
        drawable->dispose();
    }

    doneCurrent();

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
        m_viewLowerBounds = Util::nAssign(drawable->getViewLowerBounds());
        m_viewUpperBounds = Util::nAssign(drawable->getViewUpperBounds());
        m_viewRanges = drawable->getViewRanges();

        m_modelLowerBounds = Util::nAssign(drawable->getModelLowerBounds());
        m_modelUpperBounds = Util::nAssign(drawable->getModelUpperBounds());
        m_modelRanges = drawable->getModelRanges();

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

void GLWidget::updateModelBounds(ShaderDrawable *drawable)
{
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

    QTimer::singleShot(1000, this, &GLWidget::onFramesTimer);
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

bool GLWidget::perspective() const
{
    return m_perspective;
}

void GLWidget::setPerspective(bool perspective)
{
    m_perspective = perspective;

    updateProjection();
    updateView();
}

bool GLWidget::updating() const
{
    return m_updating;
}

void GLWidget::setUpdating(bool updating)
{
    m_updating = updating;
}

bool GLWidget::vsync() const
{
    return m_vsync;
}

void GLWidget::setVsync(bool vsync)
{
    if (vsync != m_vsync)
    {
        m_vsync = vsync;
        QSurfaceFormat fmt = format();
        fmt.setSwapInterval(vsync ? 1 : 0);
        setFormat(fmt);
    }
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
    // Initialize functions
    initializeOpenGLFunctions();

    // Create shader program
    m_shaderProgram = new QOpenGLShaderProgram();

    if (m_shaderProgram) {
        // Compile vertex shader
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl");
        // Compile fragment shader
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl");
        // Link shader pipeline
        m_shaderProgram->link();
    }
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    updateProjection();

    m_overlay->resize(width, height);

    emit resized();
}

void GLWidget::updateProjection()
{
    // Reset projection
    m_projectionMatrix.setToIdentity();

    if (m_perspective) {
        const double zNear = 2.0;
        const double zFar = m_distance * 10;

        double asp = (double)width() / height();
        m_projectionMatrix.frustum(
            (-0.5 + m_pan.x()) * asp,
            (0.5 + m_pan.x()) * asp,
            -0.5 + m_pan.y(),
            0.5 + m_pan.y(),
            zNear,
            zFar
        );

        double z = m_distance + (m_viewUpperBounds + m_viewLowerBounds).z() / 2 * m_zoom;
        m_planeDepth = (1 / z - 1 / zNear) / (1 / zFar - 1 / zNear) * 2 - 1;
    } else {
        const float paddingScale = 1.3f;

        // Rollback plane to view
        if (qFuzzyIsNull(m_viewRanges.length())) {
            m_viewRanges = QVector3D(100, 100, 0) / paddingScale;
        }

        double screenToWorld = qMax(
            m_viewRanges.x() / width(),
            m_viewRanges.y() / height()
        ) * paddingScale;

        // 1000.0 - maximum z-coordinate
        double clip = qMax(1000.0, (double) m_viewRanges.length());

        m_projectionMatrix.ortho(
            (-width() / 2 + m_pan.x() * width()) * screenToWorld / m_zoom,
            (width() / 2 + m_pan.x() * width()) * screenToWorld / m_zoom,
            (-height() / 2 + m_pan.y() * height()) * screenToWorld / m_zoom,
            (height() / 2 + m_pan.y() * height()) * screenToWorld / m_zoom,
            -clip,
            clip
        );

        m_planeDepth = 0;
    }
}

void GLWidget::updateView()
{
    if (m_perspective) {
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
    } else {
        m_viewMatrix.setToIdentity();

        QPointF ang = m_rot * M_PI / 180;

        QVector3D eye = m_lookAt + QVector3D(
            cos(ang.x()) * sin(ang.y()),
            sin(ang.x()),
            cos(ang.x()) * cos(ang.y())
        );

        QVector3D up(fabs(m_rot.x()) == 90 ? -sin(ang.y() + (m_rot.x() < 0 ? M_PI : 0)) : 0,
            cos(ang.x()),
            fabs(m_rot.x()) == 90 ? -cos(ang.y() + (m_rot.x() < 0 ? M_PI : 0)) : 0);

        m_viewMatrix.lookAt(eye, m_lookAt, up.normalized());
        m_viewMatrix.rotate(-90, 1.0, 0.0, 0.0);
    }

    QMatrix4x4 ivp = (m_projectionMatrix * m_viewMatrix).inverted();
    m_windowSizeWorld = (ivp * QVector3D(0, 1, m_planeDepth) - ivp * QVector3D(0, 0, m_planeDepth)).length() * 2.0;
}

void GLWidget::paintGL()
{
    if (m_animateView) viewAnimation();

    // Segment counter
    int vertices = 0;

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

    glDisable(GL_MULTISAMPLE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    // Draw 2D
    m_vertices = vertices;
    m_overlay->update();

    m_frames++;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();

    m_storedRot = m_rot;
    m_storedPan = m_pan;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_gestureProcessing)
    {
        m_lastPos = event->pos();
        m_storedRot = m_rot;
        m_storedPan = m_pan;

        return;
    }

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
    if (we->angleDelta().manhattanLength() >= 120) {
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
    } else {
        m_pan.setX(m_pan.x() - we->angleDelta().x() * 1 / (double)width());
        m_pan.setY(m_pan.y() + we->angleDelta().y() * 1 / (double)height());

        updateProjection();
    }
}

bool GLWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        auto gestureEvent = static_cast<QGestureEvent*>(event);

        if (QGesture *gesture = gestureEvent->gesture(Qt::PinchGesture))
        {
            auto pinchGesture = static_cast<QPinchGesture *>(gesture);

            if (pinchGesture->state() == Qt::GestureStarted || pinchGesture->state() == Qt::GestureUpdated)
            {
                m_gestureProcessing = true;

                if ((m_zoom * pinchGesture->scaleFactor()) > 0.1 && (m_zoom * pinchGesture->scaleFactor()) < 10.0)
                {
                    auto relativeCenterPoint = this->mapFromGlobal(pinchGesture->centerPoint().toPoint());

                    m_pan.setX(m_pan.x() - ((double)relativeCenterPoint.x() / width() - 0.5 + m_pan.x())
                        * (1 - pinchGesture->scaleFactor()));
                    m_pan.setY(m_pan.y() + ((double)relativeCenterPoint.y() / height() - 0.5 - m_pan.y())
                        * (1 - pinchGesture->scaleFactor()));

                    m_zoom *= pinchGesture->scaleFactor();
                }

                updateProjection();
                updateView();
            }
            else if (pinchGesture->state() == Qt::GestureFinished || pinchGesture->state() == Qt::GestureCanceled)
            {
                m_gestureProcessing = false;
            }

        } else if (QGesture *gesture = gestureEvent->gesture(Qt::PanGesture))
        {
            auto panGesture = static_cast<QPanGesture *>(gesture);

            if (panGesture->state() == Qt::GestureStarted || panGesture->state() == Qt::GestureUpdated)
            {
                m_gestureProcessing = true;

                m_pan.setX(m_pan.x() - (panGesture->delta().x()) * 1 / (double)width());
                m_pan.setY(m_pan.y() + (panGesture->delta().y()) * 1 / (double)height());

                updateProjection();
            }
            else if (panGesture->state() == Qt::GestureFinished || panGesture->state() == Qt::GestureCanceled)
            {
                m_gestureProcessing = false;
            }
        }
    }

    return QOpenGLWidget::event(event);
}

void GLWidget::timerEvent(QTimerEvent *te)
{
    if (te->timerId() == m_timerPaint.timerId()) {
        update();
    } else {
        QOpenGLWidget::timerEvent(te);
    }
}

double GLWidget::normalizeAngle(double angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;

    return angle;
}
