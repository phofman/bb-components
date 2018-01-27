#ifndef DATAITEMVIDEO_H
#define DATAITEMVIDEO_H

#include "DataItem.h"


class DataItemVideo : public DataItem
{
    Q_PROPERTY(QString videoType READ videoType)
    Q_PROPERTY(int width READ width)
    Q_PROPERTY(int height READ height)
    Q_PROPERTY(DataItemImage *poster READ poster)

public:
    DataItemVideo(const QString &caption, const QUrl &source, const QUrl &detailsPage,
                  const QString &videoType, int width, int height, DataItemImage *poster = NULL, QObject *parent = NULL);

    QString videoType() const;
    int width() const;
    int height() const;
    DataItemImage *poster() const;

private:
    QString videoType_;
    int width_;
    int height_;
    DataItemImage *poster_;
};

Q_DECLARE_METATYPE (DataItemVideo *)

#endif // DATAITEMVIDEO_H
