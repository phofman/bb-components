#ifndef HTMLDOCUMENT_H
#define HTMLDOCUMENT_H

#include <QByteArray>

extern "C" {
    struct GumboInternalOptions;
    struct GumboInternalOutput;

    typedef struct GumboInternalOptions GumboOptions;
    typedef struct GumboInternalOutput GumboOutput;
}

class HtmlNode;

class HtmlDocument
{
public:
    HtmlDocument(const QByteArray &content, const GumboOptions *options = NULL);
    virtual ~HtmlDocument();

public:
    HtmlNode rootNode() const;

private:
    const GumboOptions *options_;
    GumboOutput *output_;
};

#endif // HTMLDOCUMENT_H
