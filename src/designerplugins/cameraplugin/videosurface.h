#pragma once

#include <QAbstractVideoSurface>
#include <QVideoFrame>

class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    VideoSurface(QObject *parent = nullptr) : QAbstractVideoSurface(parent) {}

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;

    bool present(const QVideoFrame &frame) override;

signals:
    void frameReady(const QImage &image);
};