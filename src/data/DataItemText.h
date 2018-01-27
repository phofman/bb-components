#ifndef DATAITEMTEXT_H
#define DATAITEMTEXT_H

#include "DataItem.h"


class DataItemText : public DataItem
{
public:
    DataItemText(const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent = NULL);
};

Q_DECLARE_METATYPE (DataItemText *)

#endif // DATAITEMTEXT_H
