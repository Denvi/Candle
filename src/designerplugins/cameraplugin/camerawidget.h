#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QScrollArea>
#include <QCameraInfo>

class QCamera;
class QCameraViewfinder;

class CameraWidget: public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList availableCameras READ availableCameras);
    Q_PROPERTY(QVariantList availableResolutions READ availableResolutions);
    Q_PROPERTY(QString cameraName READ cameraName WRITE setCameraName);
    Q_PROPERTY(QVariantList resolution READ resolution WRITE setResolution);
    Q_PROPERTY(double zoom READ zoom WRITE setZoom);
    Q_PROPERTY(QVariantList pos READ pos WRITE setPos);

public:
    CameraWidget(QWidget *parent = 0);

    QStringList availableCameras() const;
    QVariantList availableResolutions() const;

    void setCameraName(QString cameraName);
    QString cameraName() const;

    void setResolution(QVariantList resolution);
    QVariantList resolution() const;

    void setZoom(double zoom);
    double zoom() const;

    void setPos(QVariantList pos);
    QVariantList pos() const;

signals:

    void posChanged(QVariantList pos);
    void zoomChanged(double zoom);

public slots:

    void start();
    void stop();

private:
    QCamera *m_camera;
    QCameraViewfinder *m_viewFinder;
    QScrollArea *m_scrollArea;

    QString m_cameraName;
    QSize m_resolution;
    double m_zoom;

    QPoint m_mousePos;

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