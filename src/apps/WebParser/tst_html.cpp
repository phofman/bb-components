#include <QtTest>
#include <QCoreApplication>
#include <QtNetwork/QNetworkReply>

#include "HtmlDocument.h"
#include "HtmlNode.h"

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

QTEST_MAIN(TestHtml)

#include "tst_html.moc"

