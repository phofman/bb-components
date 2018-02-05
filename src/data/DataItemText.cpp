#include "DataItemText.h"

DataItemText::DataItemText(const QString &caption, const QString &content, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : DataItem(QLatin1String("text"), caption, source, detailsPage, parent), content_(content)
{
    append(QLatin1String("content"), content);
}
