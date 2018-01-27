#include <QtTest>
#include <QCoreApplication>

#include "HtmlDocument.h"
#include "HtmlNode.h"

#include "gumbo.h"



class TestHtml : public QObject
{
    Q_OBJECT

public:
    TestHtml();
    ~TestHtml();

private slots:
    void test_parseHtml();

};

TestHtml::TestHtml()
{

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

QTEST_MAIN(TestHtml)

#include "tst_html.moc"

