#include "DataItemVideo.h"
#include "DataItemImage.h"

DataItemVideo::DataItemVideo(const QString &caption, const QUrl &source, const QUrl &detailsPage,
                             const QString &videoType, int width, int height, DataItemImage *poster, QObject *parent)
    : DataItem(QLatin1String("video"), videoType.length() > 0 ? videoType : QLatin1String("video/mpeg"),
               caption, source, detailsPage, parent)
{
    videoType_ = videoType;
    width_ = width;
    height_ = height;
    poster_ = poster;

    if (poster != NULL)
    {
        poster->setParent(this);
        append(QLatin1String("poster-uri"), poster->source());
        append(QLatin1String("poster-mimeType"), poster->mimeType());
    }
}

QString DataItemVideo::videoType() const
{
    return videoType_;
}

int DataItemVideo::width() const
{
    return width_;
}
int DataItemVideo::height() const
{
    return height_;
}

DataItemImage *DataItemVideo::poster() const
{
    return poster_;
}
