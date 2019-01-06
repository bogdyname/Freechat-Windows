#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QMediaPlayer>
#imclude <QWidget>

class videoviewer
{
public:
    videoviewer();
};

class MyVideoSurface : public QAbstractVideoSurface
{
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const
    {
        Q_UNUSED(handleType);

        // Return the formats you will support
        return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB565;
    }

    bool present(const QVideoFrame &frame)
    {
        Q_UNUSED(frame);
        // Handle the frame and do your processing

        return true;
    }
};

class MyVideoProducer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)

public:
    QAbstractVideoSurface* videoSurface() const { return m_surface; }

    void setVideoSurface(QAbstractVideoSurface *surface)
    {
        if (m_surface != surface && m_surface && m_surface->isActive()) {
            m_surface->stop();
        }
        m_surface = surface;
        if (m_surface)
            m_surface->start(m_format);
    }

    // ...

public slots:
    void onNewVideoContentReceived(const QVideoFrame &frame)
    {
        if (m_surface)
            m_surface->present(frame);
    }

private:
    QAbstractVideoSurface *m_surface;
    QVideoSurfaceFormat m_format;
};

#endif // VIDEOVIEWER_H
