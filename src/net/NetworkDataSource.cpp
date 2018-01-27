#include "NetworkDataSource.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QSslSocket>
#include <QDebug>
#include <QUrl>

#define NETWORKDATASOURCE_USERDATA          1234


class PartialRequestUserData : public QObjectUserData
{
public:
    const ParsingResult *result;
    int marker;
    void *data;
};

NetworkDataSource::NetworkDataSource(QObject *parent)
    : QObject(parent), parsingOngoing_(0)
{
    networkManager_ = new QNetworkAccessManager(this);
}

NetworkDataSource::~NetworkDataSource()
{
    networkManager_->deleteLater();
    networkManager_ = NULL;
}

QUrl NetworkDataSource::createUri(int pageNumer) const
{
    Q_UNUSED(pageNumer);

    return QUrl();
}

void NetworkDataSource::loadContent(const QUrl &uri)
{
    parsingOngoing_.ref();

    QNetworkRequest request(uri);
    QNetworkReply* reply = networkManager_->get(request);
    //auto isSslSupported = QSslSocket::supportsSsl();

    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onPageLoaded()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}

void NetworkDataSource::loadPartial(const QUrl &uri, const ParsingResult *result, int marker, void *data)
{
    Q_UNUSED(result);
    Q_UNUSED(marker);
    Q_UNUSED(data);

    parsingOngoing_.ref();

    QNetworkRequest request(uri);
    QNetworkReply* reply = networkManager_->get(request);

    PartialRequestUserData *userData = new PartialRequestUserData();
    userData->result = result;
    userData->marker = marker;
    userData->data = data;
    reply->setUserData(NETWORKDATASOURCE_USERDATA, userData);

    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onPartialLoaded()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}

void NetworkDataSource::parseContent(const QByteArray &content)
{
#if DEBUG
    QString response = QString::fromUtf8(content);
    qDebug() << response;
#else
    Q_UNUSED(content);
#endif

    parsingCompleted(new ParsingResult(this, QNetworkReply::NoError, QLatin1String("OK")));
}

void NetworkDataSource::parsePartialContent(const QByteArray &content, const ParsingResult *result, int marker, void *data)
{
    Q_UNUSED(content);
    Q_UNUSED(marker);
    Q_UNUSED(data);

    parsingCompleted(result);
}

void NetworkDataSource::onPageLoaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray buffer;
    ParsingResult *result = NULL;

    if (reply != NULL)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            const int available = reply->bytesAvailable();

            if (available > 0)
            {
                buffer = reply->readAll();
                parseContent(buffer);
            }
            else
            {
                result = new ParsingResult(this, QNetworkReply::HostNotFoundError, QLatin1String("No data"));
                parsingCompleted(result);
            }
        }
        else
        {
            result = new ParsingResult(this, reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), reply->errorString());
            parsingCompleted(result);
        }

        reply->deleteLater();
    }
}

void NetworkDataSource::onPartialLoaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    PartialRequestUserData *userData = NULL;
    QByteArray buffer;

    if (reply)
    {
        userData = (PartialRequestUserData *)reply->userData(NETWORKDATASOURCE_USERDATA);
        reply->setUserData(NETWORKDATASOURCE_USERDATA, NULL);

        if (reply->error() == QNetworkReply::NoError)
        {
            const int available = reply->bytesAvailable();

            if (available > 0)
            {
                buffer = reply->readAll();
                parsePartialContent(buffer, userData->result, userData->marker, userData->data);
            }
            else
            {
                parsingCompleted(userData->result);
            }
        }
        else
        {
            parsingCompleted(userData->result);
        }

        delete userData;
        reply->deleteLater();
    }
}

void NetworkDataSource::parsingCompleted(const ParsingResult *result)
{
    if (!parsingOngoing_.deref())
    {
        //qDebug() << "Parsing completed, code:" << result->errorCode();
        emit completed((ParsingResult *)result);
    }
}
