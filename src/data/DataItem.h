#ifndef DATAITEM_H
#define DATAITEM_H

#include <QList>
#include <QObject>
#include <QString>
#include <QUrl>

#include <QtCore/QMetaType>


class DataItem;
class DataItemImage;
typedef QList<DataItem *> DataItemsCollection;
typedef QList<DataItemImage *> DataItemImagesCollection;

class DataItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString caption READ caption)
    Q_PROPERTY(QUrl uri READ source)
    Q_PROPERTY(QUrl detailsPage READ detailsPage)
    Q_PROPERTY(QString fileName READ fileName)

private:
    QString type_;
    QString caption_;
    QUrl source_;
    QUrl detailsPage_;

public:
    DataItem(const QString &type, const QString &caption, const QUrl &source, const QUrl &detailsPage, QObject *parent = NULL);

    const QString &type() const     { return type_; }
    const QString &caption() const  { return caption_; }
    QUrl source() const             { return source_; }
    QUrl detailsPage() const        { return detailsPage_; }
    QString fileName() const;
};

Q_DECLARE_METATYPE (DataItem *)

#endif // DATAITEM_H
