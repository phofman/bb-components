#ifndef PARSINGRESULT_H
#define PARSINGRESULT_H

#include <QObject>
#include <QString>

#include "DataItem.h"

class ParsingResult : public QObject
{
    Q_OBJECT

public:
    ParsingResult(QObject *parent, int errorCode, const QString &message,
                  int pageNumer = -1, int prevPageNumber = -1, int nextPageNumber = -1);

public:
    bool hasError() const;
    int errorCode() const;
    QString message() const;

    int pageNumber() const;
    int prevPageNumber() const;
    int nextPageNumber() const;
    DataItemsCollection &items();

private:
    int errorCode_;
    QString message_;
    int pageNumber_;
    int prevPageNumber_;
    int nextPageNumber_;
    DataItemsCollection items_;
};

Q_DECLARE_METATYPE(ParsingResult *)

#endif // PARSINGRESULT_H
