#ifndef DATAITEMPAGER_H
#define DATAITEMPAGER_H

#include "DataItem.h"


class DataItemPager : public DataItem
{
    Q_PROPERTY(int pageNumber READ pageNumber)

public:
    DataItemPager(int pageNumber, const QUrl &detailsPage, QObject *parent = NULL);

public:
    int pageNumber() const;

private:
    int pageNumber_;
};

Q_DECLARE_METATYPE (DataItemPager *)

#endif // DATAITEMPAGER_H
