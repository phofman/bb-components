#include "DataItem.h"

#include <QDebug>

DataItem::DataItem(const QString &type, const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : QObject(parent), type_(type), caption_(caption), source_(source), detailsPage_(detailsPage)
{
    fileName_ = getFileName(source_);

    map_[QLatin1String("type")] = type;
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
