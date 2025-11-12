#include "videosurface.h"
#include <QDebug>

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    QList<QVideoFrame::PixelFormat> formats;

    if (handleType == QAbstractVideoBuffer::NoHandle)
    {
        formats 
            << QVideoFrame::Format_ARGB32
            << QVideoFrame::Format_ARGB32_Premultiplied
            << QVideoFrame::Format_RGB32
            << QVideoFrame::Format_RGB24
            << QVideoFrame::Format_RGB565
            << QVideoFrame::Format_RGB555
            << QVideoFrame::Format_ARGB8565_Premultiplied
            << QVideoFrame::Format_BGRA32
            << QVideoFrame::Format_BGRA32_Premultiplied
            << QVideoFrame::Format_BGR32
            << QVideoFrame::Format_BGR24
            << QVideoFrame::Format_BGR565
            << QVideoFrame::Format_BGR555
            << QVideoFrame::Format_AYUV444
            << QVideoFrame::Format_YUV444
            << QVideoFrame::Format_YUV420P
            << QVideoFrame::Format_YV12
            << QVideoFrame::Format_UYVY
            << QVideoFrame::Format_YUYV
            << QVideoFrame::Format_NV12
            << QVideoFrame::Format_NV21
            << QVideoFrame::Format_Jpeg;
    }

    return formats;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    if (!frame.isValid())
        return false;

#ifdef Q_OS_WIN
    emit frameReady(frame.image().mirrored(false, true));
#else
    emit frameReady(frame.image());
#endif

    return true;
}