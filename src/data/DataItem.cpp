#include "DataItem.h"

#include <QDebug>

DataItem::DataItem(const QString &type, const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : QObject(parent), type_(type), caption_(caption), source_(source), detailsPage_(detailsPage)
{
}

QString DataItem::fileName() const
{
    QString p = source_.path();

    for(int i = p.length() - 1; i >= 0; i--)
    {
        if (p[i] == '/')
        {
            return p.right(p.length() - 1 - i);
        }
    }

    return p;
}
