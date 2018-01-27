#include "DataItem.h"

#include <QDebug>

DataItem::DataItem(const QString &type, const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : QObject(parent), type_(type), caption_(caption), source_(source), detailsPage_(detailsPage)
{
}
