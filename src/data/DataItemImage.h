#ifndef DATAITEMIMAGE_H
#define DATAITEMIMAGE_H

#include "DataItem.h"


class DataItemImage : public DataItem
{
public:
    DataItemImage(const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent = NULL);
};

Q_DECLARE_METATYPE (DataItemImage *)

#endif // DATAITEMIMAGE_H
