#include <QtTest>
#include <QCoreApplication>
#include <QtNetwork/QNetworkReply>

#include "HtmlDocument.h"
#include "HtmlNode.h"

#include "DataItem.h"

#include "NetworkDataSource.h"
#include "ParsingResult.h"
#include "util.h"

#include "gumbo.h"


class TestHtml : public QObject
{
    Q_OBJECT

public:
    TestHtml();
    ~TestHtml();

private slots:
    void test_parseHtml();
    void test_loadAnything();
    void test_getFileName();
};

TestHtml::TestHtml()
{
    qRegisterMetaType<ParsingResult *>();
}

TestHtml::~TestHtml()
{
}

void TestHtml::test_parseHtml()
{
    HtmlDocument doc (QLatin1String("<html><head><title>Test Runner Application</title></head></html>"));

    HtmlNode *titleNode = doc.rootNode().findByTag(GUMBO_TAG_TITLE);
    QVERIFY(titleNode != NULL);
    QVERIFY(titleNode->innerText() == QLatin1String("Test Runner Application"));
}

void TestHtml::test_loadAnything()
{
    NetworkDataSource source;
    QSignalSpy spy(&source, SIGNAL(completed(ParsingResult *)));

    source.loadContent(QUrl(QLatin1String("https://onet.pl")));

    QTRY_COMPARE(spy.count(), 1);
    QCOMPARE(spy.count(), 1);

    ParsingResult *result = spy.at(0).at(0).value<ParsingResult *>();

    QVERIFY(result != NULL);

    qDebug() << "Message:" << result->message();
    qDebug() << "Code:" << result->errorCode();
    QVERIFY(result->errorCode() == QNetworkReply::NoError);
}

void TestHtml::test_getFileName()
{
    DataItem item1(QLatin1String("x"), QLatin1String(""), QLatin1String("y"), QUrl("http://onet.pl/image/fav.ico?v=1"), QUrl("http://onet.pl"));
    QVERIFY(item1.fileName() == QLatin1String("fav.ico"));
    QVERIFY(item1.mimeType() == QLatin1String("image/ico"));

    DataItem item2(QLatin1String("x"), QLatin1String(""), QLatin1String("y"), QUrl("http://onet.pl/image/priv/fav2.ico#details"), QUrl("http://onet.pl"));
    QVERIFY(item2.fileName() == QLatin1String("fav2.ico"));
    QVERIFY(item2.mimeType() == QLatin1String("image/ico"));

    DataItem item3(QLatin1String("x"), QLatin1String(""), QLatin1String("y"), QUrl("http://onet.pl/image/priv/fav3.gif#details"), QUrl("http://onet.pl"));
    QVERIFY(item3.fileName() == QLatin1String("fav3.gif"));
    QVERIFY(item3.mimeType() == QLatin1String("image/gif"));
}

QTEST_MAIN(TestHtml)

#include "tst_html.moc"

