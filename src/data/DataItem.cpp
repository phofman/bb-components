#include "DataItem.h"

#include <QDebug>

DataItem::DataItem(const QString &type, const QString &mimeType, const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : QObject(parent), type_(type), caption_(caption), source_(source), detailsPage_(detailsPage),
      fileName_(getFileName(source)), mimeType_(mimeType.length() > 0 ? mimeType : getDefaultMimeType(fileName_))
{
    map_[QLatin1String("type")] = type;
    map_[QLatin1String("mimeType")] = mimeType_;
    map_[QLatin1String("caption")] = caption;
    map_[QLatin1String("fileName")] = fileName_;
    map_[QLatin1String("uri")] = source;
    map_[QLatin1String("source")] = source;
    map_[QLatin1String("details")] = detailsPage;
    map_[QLatin1String("detailsUri")] = detailsPage;
}

QString DataItem::getFileName(const QUrl &url)
{
    QString p = url.path();

    for(int i = p.length() - 1; i >= 0; i--)
    {
        if (p[i] == '/')
        {
            return p.right(p.length() - 1 - i);
        }
    }

    return p;
}

void DataItem::append(const QString& name, const QVariant& value)
{
    map_[name] = value;
}

const QString DataItem::getDefaultMimeType(const QString &fileName)
{
    if (fileName.endsWith(QLatin1String(".png"), Qt::CaseInsensitive))
        return QLatin1String("image/png");
    if (fileName.endsWith(QLatin1String(".jpg"), Qt::CaseInsensitive))
        return QLatin1String("image/jpg");
    if (fileName.endsWith(QLatin1String(".gif"), Qt::CaseInsensitive))
        return QLatin1String("image/gif");
    if (fileName.endsWith(QLatin1String(".bmp"), Qt::CaseInsensitive))
        return QLatin1String("image/bmp");
    if (fileName.endsWith(QLatin1String(".ico"), Qt::CaseInsensitive))
        return QLatin1String("image/ico");

    if (fileName.endsWith(QLatin1String(".mp3"), Qt::CaseInsensitive))
        return QLatin1String("audio/mpeg3");
    if (fileName.endsWith(QLatin1String(".wav"), Qt::CaseInsensitive))
        return QLatin1String("audio/wav");
    if (fileName.endsWith(QLatin1String(".mp4"), Qt::CaseInsensitive))
        return QLatin1String("video/mp4");

    return QString(QLatin1String("text/plain"));
}
