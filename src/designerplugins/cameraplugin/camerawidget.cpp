#include "camerawidget.h"

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QImageEncoderSettings>
#include <QScrollBar>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>

CameraWidget::CameraWidget(QWidget *parent): QWidget(parent), m_camera(0), m_viewFinder(0), 
    m_resolution(QSize(1280, 720)), m_zoom(1.0), m_mousePos(QPoint(0, 0))
{
    m_viewFinder = new QCameraViewfinder(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);
    
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->horizontalScrollBar()->setEnabled(false);
    m_scrollArea->verticalScrollBar()->setEnabled(false);
    m_scrollArea->setWidget(m_viewFinder);

    layout->addWidget(m_scrollArea);
    layout->setMargin(0);

    m_overlay = new Overlay(m_viewFinder);
}

void CameraWidget::setCameraName(QString cameraName)
{
    m_cameraName = cameraName;

    if (m_cameraName.isEmpty()) {
        setCamera(QCameraInfo::defaultCamera());
        return;
    }

    foreach (const QCameraInfo &i, QCameraInfo::availableCameras()) {
        if (i.description() == m_cameraName) {
            setCamera(i);
            break;
        }
    }
}

QString CameraWidget::cameraName() const
{
    return m_cameraName;
}

QStringList CameraWidget::availableCameras() const
{
    QStringList l;

    foreach (const QCameraInfo &i, QCameraInfo::availableCameras()) l << i.description();

    return l;
}

QStringList CameraWidget::availableResolutions() const
{
    if (m_camera) {
        QStringList l;
        foreach (QSize s, m_camera->supportedViewfinderResolutions()) l.append(QString("%1x%2").arg(s.width()).arg(s.height()));
        return l;
    } else {
        return QStringList();
    }
}

void CameraWidget::setCamera(const QCameraInfo &cameraInfo)
{
    if (m_camera) {
        m_camera->stop();
        m_camera->deleteLater();
    }

    m_camera = new QCamera(cameraInfo);
    m_camera->setViewfinder(m_viewFinder);

    m_camera->load();
    m_camera->setCaptureMode(QCamera::CaptureViewfinder);

    QCameraViewfinderSettings fs = m_camera->viewfinderSettings();
    fs.setResolution(m_resolution);
    m_camera->setViewfinderSettings(fs);

    if (isVisible()) m_camera->start();

    updateSize();
}

void CameraWidget::start()
{
    if (m_camera) m_camera->start();
}

void CameraWidget::stop()
{
    if (m_camera) m_camera->stop();
}

void CameraWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    updateSize();

    setAimPos(QVariantList() << m_overlay->aimPosition().x() << m_overlay->aimPosition().y());
}

void CameraWidget::updateSize()
{
    QSize size = contentsRect().size();

    double aspect = (double)(size.width()) / (size.height());
    double cameraAspect = (double)m_resolution.width() / m_resolution.height();

    if (aspect >= cameraAspect) {
        m_viewFinder->resize(size.width() * m_zoom, size.width() / cameraAspect * m_zoom);
    } else {
        m_viewFinder->resize(size.height() * cameraAspect * m_zoom, size.height() * m_zoom);
    }

    m_overlay->resize(m_viewFinder->size());
}

void CameraWidget::setResolution(QVariantList resolution)
{
    qDebug() << "setResolution" << resolution;
    if (resolution.size() != 2) return;
    m_resolution = QSize(resolution.at(0).toInt(), resolution.at(1).toInt());
}

QVariantList CameraWidget::resolution() const
{
    return QVariantList() << m_resolution.width() << m_resolution.height();
}

void CameraWidget::setZoom(double zoom)
{
    qDebug() << "setZoom" << zoom;
    if (zoom >= 1) {
        m_zoom = zoom;
        updateSize();
    }
}

double CameraWidget::zoom() const
{
    return m_zoom;
}

void CameraWidget::setPos(QVariantList pos)
{
    if (pos.size() != 2) return;

    m_pos = QPoint(pos.at(0).toInt(), pos.at(1).toInt());

    m_scrollArea->horizontalScrollBar()->setValue(m_pos.x());
    m_scrollArea->verticalScrollBar()->setValue(m_pos.y());

    emit posChanged(pos);
}

QVariantList CameraWidget::pos() const
{
    return QVariantList() << m_pos.x() << m_pos.y();
}

void CameraWidget::setAimPos(QVariantList aimPos)
{
    if (aimPos.size() != 2) return;

    if (qIsNaN(aimPos.at(0).toDouble()) || qIsNaN(aimPos.at(1).toDouble())) return;

    m_overlay->setAimPosition(QPointF(aimPos.at(0).toDouble(), aimPos.at(1).toDouble()));
    m_overlay->update();

    emit aimPosChanged(aimPos);
}

QVariantList CameraWidget::aimPos() const
{
    QPointF p = m_overlay->aimPosition();

    return QVariantList() << p.x() << p.y();
}

void CameraWidget::setAimSize(int aimSize)
{
    m_overlay->setAimSize(aimSize);

    emit aimSizeChanged(aimSize);
}

int CameraWidget::aimSize() const
{
    return m_overlay->aimSize();
}

void CameraWidget::setAimLineWidth(int aimLineWidth)
{
    m_overlay->setAimLineWidth(aimLineWidth);

    emit aimLineWidthChanged(aimLineWidth);
}

int CameraWidget::aimLineWidth() const
{
    return m_overlay->aimLineWidth();
}

void CameraWidget::setAimColor(int aimColor)
{
    m_overlay->setAimColor(aimColor);

    emit aimColorChanged(aimColor);
}

int CameraWidget::aimColor() const
{
    return m_overlay->aimColor();
}

void CameraWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton) {
        m_mousePos = e->pos();
        m_aimPos = m_overlay->aimPosition();
    }

    QWidget::mousePressEvent(e);
}

void CameraWidget::mouseMoveEvent(QMouseEvent *e)
{

    if (e->buttons() == Qt::LeftButton && e->modifiers() == Qt::ShiftModifier) {

        QPointF d = QPointF((double)(e->pos() - m_mousePos).x() / m_overlay->width(), 
            (double)(e->pos() - m_mousePos).y() / m_overlay->height());

        QPointF o = m_aimPos + d;
        setAimPos(QVariantList() << o.x() << o.y());

    } else if (e->buttons() == Qt::LeftButton) {
        QPoint d = e->pos() - m_mousePos;

        setPos(QVariantList() << m_scrollArea->horizontalScrollBar()->value() - d.x() 
            << m_scrollArea->verticalScrollBar()->value() - d.y());

        m_mousePos = e->pos();
    }

    QWidget::mouseMoveEvent(e);
}

void CameraWidget::wheelEvent(QWheelEvent *e)
{
    double f =  e->delta() > 0 ? 1.25 : 0.8;

    double prevZoom = m_zoom;
    m_zoom = qBound<double>(1, m_zoom * f, 8);

    QPointF deltaPos = e->posF() / prevZoom - m_scrollArea->widget()->pos() / prevZoom;
    QPointF delta = deltaPos * m_zoom - deltaPos * prevZoom;
    QPoint d = delta.toPoint();

    updateSize();

    setPos(QVariantList() << m_scrollArea->horizontalScrollBar()->value() + d.x() <<
        m_scrollArea->verticalScrollBar()->value() + d.y());

    setAimPos(QVariantList() << m_overlay->aimPosition().x() << m_overlay->aimPosition().y());

    emit zoomChanged(m_zoom);
}

void CameraWidget::hideEvent(QHideEvent *e)
{
    QWidget::hideEvent(e);

    if (m_camera && m_camera->state() == QCamera::ActiveState) {
        m_camera->stop();
    }
}

void CameraWidget::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);

    if (m_camera && m_camera->state() == QCamera::LoadedState) {
        setCameraName(m_cameraName);
    }

    m_scrollArea->horizontalScrollBar()->setValue(m_pos.x());
    m_scrollArea->verticalScrollBar()->setValue(m_pos.y());
}