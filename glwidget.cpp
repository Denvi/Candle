// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include "glwidget.h"
#include "tooldrawer.h"
#include <QDebug>
#include <QtWidgets>
#include <QPainter>
#include <QEasingCurve>

#define ZOOMSTEP 1.1

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    m_animateView = false;

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

    m_spendTime.setHMS(0, 0, 0);
    m_estimatedTime.setHMS(0, 0, 0);

    QTimer::singleShot(1000, this, SLOT(onFramesTimer()));
    setFps(60);
}

double GLWidget::calculateVolume(QVector3D size) {
    return size.x() * size.y() * size.z();
}

void GLWidget::addDrawable(GLDrawable *drawable)
{
    m_drawables.append(drawable);
}

void GLWidget::fitDrawables()
{
    GLDrawable *bigest = NULL;
    QVector3D maxSize(0, 0, 0);

    stopViewAnimation();

    foreach (GLDrawable *dr, m_drawables) {
        QVector3D size = dr->getSizes();
        //if (calculateVolume(size) > calculateVolume(maxSize)) {
        if (size.length() > maxSize.length() && strcmp(dr->metaObject()->className(), "ToolDrawer") == -1) {
            maxSize = size;
            bigest = dr;
        }
    }

    if (bigest != NULL) {

        double a = maxSize.y() / 2 / 0.25 * 1.3
                + (bigest->getMaximumExtremes().z() - bigest->getMinimumExtremes().z()) / 2;
        double b = maxSize.x() / 2 / 0.25 * 1.3
                / ((double)this->width() / this->height())
                + (bigest->getMaximumExtremes().z() - bigest->getMinimumExtremes().z()) / 2;
        m_distance = qMax(a, b);

        m_xLookAt = (bigest->getMaximumExtremes().x() - bigest->getMinimumExtremes().x()) / 2 + bigest->getMinimumExtremes().x();
        m_zLookAt = -((bigest->getMaximumExtremes().y() - bigest->getMinimumExtremes().y()) / 2 + bigest->getMinimumExtremes().y());
        m_yLookAt = (bigest->getMaximumExtremes().z() - bigest->getMinimumExtremes().z()) / 2 + bigest->getMinimumExtremes().z();
//        m_yLookAt = bigest->getMinimumExtremes().z();

        m_xMin = bigest->getMinimumExtremes().x();
        m_xMax = bigest->getMaximumExtremes().x();
        m_yMin = bigest->getMinimumExtremes().y();
        m_yMax = bigest->getMaximumExtremes().y();
        m_zMin = bigest->getMinimumExtremes().z();
        m_zMax = bigest->getMaximumExtremes().z();

        m_xSize = m_xMax - m_xMin;
        m_ySize = m_yMax - m_yMin;
        m_zSize = m_zMax - m_zMin;

    } else {
        m_distance = 200;
        m_xLookAt = 0;
        m_yLookAt = 0;
        m_zLookAt = 0;
    }

    m_xSize = m_xMax - m_xMin;
    m_ySize = m_yMax - m_yMin;
    m_zSize = m_zMax - m_zMin;

    m_xPan = 0;
    m_yPan = 0;

    m_zoom = 1;
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
    double t = (double)m_animationFrame++ / (m_targetFps * 0.2);

    if (t == 1) stopViewAnimation();

    QEasingCurve ec(QEasingCurve::OutExpo);
    double val = ec.valueForProgress(t);

    m_xRot = m_xRotStored + double(m_xRotTarget - m_xRotStored) * val;
    m_yRot = m_yRotStored + double(m_yRotTarget - m_yRotStored) * val;
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

void GLWidget::setFps(int fps)
{
    m_targetFps = fps;
    m_timerAnimation.stop();
    m_timerAnimation.start(1000 / fps, Qt::PreciseTimer, this);
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
    GLint bufs;
    GLint samples;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);

    qDebug("Have %d buffers and %d samples", bufs, samples);

//    qglClearColor(QColor(Qt::white));
}

void GLWidget::paintGL()
{    

}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    //updateProjection();
}

void GLWidget::updateProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double asp = (double)width() / height();
    glFrustum ((-0.5 + m_xPan) * asp, (0.5 + m_xPan) * asp, -0.5 + m_yPan, 0.5 + m_yPan, 2, m_distance * 2);
    //glOrtho((-10 + m_xPan) * asp, (10 + m_xPan) * asp, -10 + m_yPan, 10 + m_yPan, 0, m_distance * 2);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintEvent(QPaintEvent *pe)
{
    makeCurrent();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Draw 3D
    qglClearColor(QColor(Qt::white));

    if (m_antialiasing) {
        if (m_msaa) glEnable(GL_MULTISAMPLE); else {
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_LINE_SMOOTH);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
        }
    }
    if (m_zBuffer) glEnable(GL_DEPTH_TEST);

    updateProjection();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();   

    double r = m_distance;
    double angY = M_PI / 180 * m_yRot;
    double angX = M_PI / 180 * m_xRot;

//    qDebug() << angY << angX << cos(angX) << sin(angX);
//    qDebug() << r * cos(angX) * sin(angY) + m_xLookAt << r * sin(angX) + m_yLookAt << r * cos(angX) * cos(angY) + m_zLookAt;

    gluLookAt(r * cos(angX) * sin(angY) + m_xLookAt, r * sin(angX) + m_yLookAt, r * cos(angX) * cos(angY) + m_zLookAt,
              m_xLookAt, m_yLookAt, m_zLookAt,
              fabs(m_xRot) == 90 ? -sin(angY + (m_xRot < 0 ? M_PI : 0)) : 0, cos(angX), fabs(m_xRot) == 90 ? -cos(angY + (m_xRot < 0 ? M_PI : 0)) : 0);

    glTranslatef(m_xLookAt, m_yLookAt, m_zLookAt);
    glScalef(m_zoom, m_zoom, m_zoom);
    glTranslatef(-m_xLookAt, -m_yLookAt, -m_zLookAt);

    glRotatef(-90, 1.0, 0.0, 0.0);

    glLineWidth(m_lineWidth);

//    glBegin(GL_LINES);
//    glColor3f(1.0, 1.0, 0.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(m_xLookAt, -m_zLookAt, m_yLookAt);
//    glEnd();

    // Draw X-axis
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(9, 0, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(10, 0, 0);
    glVertex3f(8, 0.5, 0);
    glVertex3f(8, -0.5, 0);
    glVertex3f(10, 0, 0);
    glEnd();

    // Draw Y-axis
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 9, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 10, 0);
    glVertex3f(-0.5, 8, 0);
    glVertex3f(0.5, 8, 0);
    glVertex3f(0, 10, 0);
    glEnd();

    // Draw Z-axis
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 9);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 10);
    glVertex3f(-0.5, 0, 8);
    glVertex3f(0.5, 0, 8);
    glVertex3f(0, 0, 10);
    glEnd();

    // Draw 2x2 XY rect
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glEnd();

    // Draw drawables
    int lines = 0;
    foreach (GLDrawable *dr, m_drawables) {
        lines += dr->getLinesCount();
        dr->draw();
    }

    // Draw 2D
    glShadeModel(GL_FLAT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    QPainter painter(this);

    double x = 10;
    double y = this->height() - 60;

    painter.drawText(QPoint(x, y), QString("X: %1 ... %2").arg(m_xMin, 0, 'f', 3).arg(m_xMax, 0, 'f', 3));
    painter.drawText(QPoint(x, y + 15), QString("Y: %1 ... %2").arg(m_yMin, 0, 'f', 3).arg(m_yMax, 0, 'f', 3));
    painter.drawText(QPoint(x, y + 30), QString("Z: %1 ... %2").arg(m_zMin, 0, 'f', 3).arg(m_zMax, 0, 'f', 3));
    painter.drawText(QPoint(x, y + 45), QString("%1 / %2 / %3").arg(m_xSize, 0, 'f', 3).arg(m_ySize, 0, 'f', 3).arg(m_zSize, 0, 'f', 3));        

    QFontMetrics fm(painter.font());

    painter.drawText(QPoint(x, fm.height() + 10), m_parserStatus);

    QString str = QString(tr("Lines: %1")).arg(lines);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + 30), str);
    str = QString("FPS: %1").arg(m_fps);
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + 45), str);

    str = m_spendTime.toString("hh:mm:ss") + " / " + m_estimatedTime.toString("hh:mm:ss");
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y), str);

    str = m_bufferState;
    painter.drawText(QPoint(this->width() - fm.width(str) - 10, y + 15), str);

//    QGLWidget::paintEvent(pe);

    m_frames++;
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
    if (event->buttons() & Qt::MiddleButton && !(event->modifiers() & Qt::ShiftModifier) || event->buttons() & Qt::LeftButton) {

        stopViewAnimation();

        m_yRot = normalizeAngle(m_yLastRot - (event->pos().x() - m_lastPos.x()) * 0.5);
        m_xRot = m_xLastRot + (event->pos().y() - m_lastPos.y()) * 0.5;

        if (m_xRot < -90) m_xRot = -90;
        if (m_xRot > 90) m_xRot = 90;

        emit rotationChanged();
        //qDebug() << m_yRot << m_xRot;
    }

    if (event->buttons() & Qt::MiddleButton && event->modifiers() & Qt::ShiftModifier || event->buttons() & Qt::RightButton) {
        m_xPan = m_xLastPan - (event->pos().x() - m_lastPos.x()) * 1 / (double)width();
        m_yPan = m_yLastPan + (event->pos().y() - m_lastPos.y()) * 1 / (double)height();

        //updateProjection();
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

//    qDebug() << m_zoom;

    //updateProjection();
    //updateGL();
//    update();
}

void GLWidget::timerEvent(QTimerEvent *te)
{
    if (te->timerId() == m_timerAnimation.timerId()) {
        if (m_animateView) viewAnimation();
        if (m_updatesEnabled) update();
    } else {
        QGLWidget::timerEvent(te);
    }
}

double GLWidget::normalizeAngle(double angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;

    return angle;
}
