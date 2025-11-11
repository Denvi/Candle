#include "videosurface.h"
#include <QDebug>

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    QList<QVideoFrame::PixelFormat> formats;

    if (handleType == QAbstractVideoBuffer::NoHandle)
    {
        formats << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_RGB24
                << QVideoFrame::Format_BGR24;
    }

    return formats;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    if (!frame.isValid())
        return false;

    emit frameReady(frame.image().mirrored(false, true));

    return true;
}