#include "DataItemPager.h"

DataItemPager::DataItemPager(int pageNumber, const QUrl &detailsPage, QObject *parent)
    : DataItem(QLatin1String("pager"), QLatin1String("--- ") + QString::number(pageNumber) + QLatin1String(" ---"),
               detailsPage, detailsPage, parent), pageNumber_(pageNumber)
{
}

int DataItemPager::pageNumber() const
{
    return pageNumber_;
}
