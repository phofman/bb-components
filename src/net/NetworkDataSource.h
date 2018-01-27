#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include "AbstractDataSource.h"

class NetworkDataSource : public QObject, public AbstractDataSource
{
    Q_OBJECT

public:
    explicit NetworkDataSource(QObject *parent = NULL);
    virtual ~NetworkDataSource();

    virtual QUrl createUri(int pageNumer = 0) const;
    virtual void loadContent(const QUrl &uri);

protected:
    void loadPartial(const QUrl &uri, const ParsingResult *result, int marker, void *data);

    virtual void parseContent(const QByteArray &content);
    virtual void parsePartialContent(const QByteArray &content, const ParsingResult *result, int marker, void *data);
    void parsingCompleted(const ParsingResult *result);

private slots:
    void onPageLoaded();
    void onPartialLoaded();

signals:
    void completed(ParsingResult *result);

private:
    QAtomicInt parsingOngoing_;
    QNetworkAccessManager *networkManager_;
};

#endif // REQUESTMANAGER_H
