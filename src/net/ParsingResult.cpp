#include "ParsingResult.h"

ParsingResult::ParsingResult(QObject *parent, int errorCode, const QString &message, int pageNumer, int prevPageNumber, int nextPageNumber)
    : QObject(parent)
{
    errorCode_ = errorCode;
    message_ = message;
    pageNumber_ = pageNumer;
    prevPageNumber_ = prevPageNumber;
    nextPageNumber_ = nextPageNumber;
}

int ParsingResult::errorCode() const
{
    return errorCode_;
}

QString ParsingResult::message() const
{
    return message_;
}

int ParsingResult::pageNumber() const
{
    return pageNumber_;
}

int ParsingResult::prevPageNumber() const
{
    return prevPageNumber_;
}

int ParsingResult::nextPageNumber() const
{
    return nextPageNumber_;
}

DataItemsCollection &ParsingResult::items()
{
    return items_;
}
