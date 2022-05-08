#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QScrollArea>
#include <QCameraInfo>
#include "overlay.h"

class QCamera;
class QCameraViewfinder;

class CameraWidget: public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList availableCameras READ availableCameras);
    Q_PROPERTY(QStringList availableResolutions READ availableResolutions);
    Q_PROPERTY(QString cameraName READ cameraName WRITE setCameraName);
    Q_PROPERTY(QVariantList resolution READ resolution WRITE setResolution);
    Q_PROPERTY(double zoom READ zoom WRITE setZoom);
    Q_PROPERTY(QVariantList pos READ pos WRITE setPos);
    Q_PROPERTY(QVariantList aimPos READ aimPos WRITE setAimPos);
    Q_PROPERTY(int aimSize READ aimSize WRITE setAimSize);
    Q_PROPERTY(int aimLineWidth READ aimLineWidth WRITE setAimLineWidth);
    Q_PROPERTY(int aimColor READ aimColor WRITE setAimColor);

public:
    CameraWidget(QWidget *parent = 0);

    QStringList availableCameras() const;
    QStringList availableResolutions() const;

    void setCameraName(QString cameraName);
    QString cameraName() const;

    void setResolution(QVariantList resolution);
    QVariantList resolution() const;

    void setZoom(double zoom);
    double zoom() const;

    void setPos(QVariantList pos);
    QVariantList pos() const;

    void setAimPos(QVariantList aimPos);
    QVariantList aimPos() const;

    void setAimSize(int aimSize);
    int aimSize() const;

    void setAimLineWidth(int aimLineWidth);
    int aimLineWidth() const;

    void setAimColor(int aimColor);
    int aimColor() const;

signals:

    void posChanged(QVariantList pos);
    void aimPosChanged(QVariantList aimPos);
    void aimSizeChanged(int aimSize);
    void aimLineWidthChanged(int aimLineWidth);
    void aimColorChanged(int aimColor);
    void zoomChanged(double zoom);

public slots:

    void start();
    void stop();

private:
    QCamera *m_camera;
    QCameraViewfinder *m_viewFinder;
    QScrollArea *m_scrollArea;
    Overlay *m_overlay;

    QString m_cameraName;
    QSize m_resolution;
    double m_zoom;

    QPoint m_mousePos;
    QPointF m_aimPos;

    QPoint m_pos;

    void setCamera(const QCameraInfo &cameraInfo);
    void resizeEvent(QResizeEvent *e);
    void updateSize();

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    void hideEvent(QHideEvent *e) override;
    void showEvent(QShowEvent *e) override;
};

#endif