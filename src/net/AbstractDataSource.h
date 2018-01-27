#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include <QString>
#include <QUrl>
#include <QDebug>

#include "ParsingResult.h"



class AbstractDataSource
{
public:
    virtual ~AbstractDataSource()
    {
    }

public:
    /**
     * @brief Creates an URI address for a specific page of the content.
     */
    virtual QUrl createUri(int pageNumer = 0) const = 0;

    /**
     * @brief Loads data from specific address. Appropriate completion signal is emitted.
     */
    virtual void loadContent(const QUrl &uri) = 0;
};

#endif // IDATASOURCE_H
