#ifndef DATAITEMGALLERY_H
#define DATAITEMGALLERY_H

#include "DataItem.h"


class DataItemGallery : public DataItem
{
    Q_PROPERTY(DataItemsCollection &images READ images)

public:
    DataItemGallery(const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent = NULL);

public:
    DataItemImagesCollection &images();

private:
    DataItemImagesCollection images_;
};

Q_DECLARE_METATYPE (DataItemGallery *)

#endif // DATAITEMGALLERY_H
