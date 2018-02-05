#ifndef DATAITEMTEXT_H
#define DATAITEMTEXT_H

#include "DataItem.h"


class DataItemText : public DataItem
{
    Q_PROPERTY(QString content READ content)

public:
    DataItemText(const QString &mimeType, const QString &caption, const QString &content, const QUrl &source, const QUrl &detailsPage, QObject *parent = NULL);

public:
    const QString &content() const { return content_; }

private:
    QString content_;
};

Q_DECLARE_METATYPE (DataItemText *)

#endif // DATAITEMTEXT_H
