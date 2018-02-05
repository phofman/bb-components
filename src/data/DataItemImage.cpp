#include "DataItemImage.h"

DataItemImage::DataItemImage(const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : DataItem(QLatin1String("image"), QLatin1String(""), caption, source, detailsPage, parent)
{
}
