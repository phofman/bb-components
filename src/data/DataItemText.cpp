#include "DataItemText.h"

DataItemText::DataItemText(const QString &mimeType, const QString &caption, const QString &content, const QUrl &source, const QUrl &detailsPage, QObject *parent)
    : DataItem(QLatin1String("text"), mimeType.length() > 0 ? mimeType : QLatin1String("text/plain"),
               caption, source, detailsPage, parent), content_(content)
{
    append(QLatin1String("content"), content);
}
