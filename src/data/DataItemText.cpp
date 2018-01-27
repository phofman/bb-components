#include "DataItemText.h"

DataItemText::DataItemText(const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : DataItem(QLatin1String("text"), caption, source, detailsPage, parent)
{
}
