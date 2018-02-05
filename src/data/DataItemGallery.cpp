#include "DataItemGallery.h"

DataItemGallery::DataItemGallery(const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : DataItem(QLatin1String("gallery"), QLatin1String(""), caption, source, detailsPage, parent)
{
}

DataItemImagesCollection &DataItemGallery::images()
{
    return images_;
}
