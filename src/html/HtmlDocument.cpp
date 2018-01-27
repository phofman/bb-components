#include "HtmlDocument.h"
#include "HtmlNode.h"

#include "gumbo.h"

#include <stdexcept>

HtmlDocument::HtmlDocument(const QByteArray &content, const GumboOptions *options)
    : options_(options)
{
    output_ = gumbo_parse_with_options(options == NULL ? &kGumboDefaultOptions : options, content.constData(), content.size());

    if (output_ == NULL)
    {
        throw std::runtime_error("Invalid data to parse");
    }
}

HtmlDocument::HtmlDocument(const QString &content, const GumboOptions *options)
    : options_(options)
{
    output_ = gumbo_parse_with_options(options == NULL ? &kGumboDefaultOptions : options, content.toUtf8().constData(), content.size());

    if (output_ == NULL)
    {
        throw std::runtime_error("Invalid data to parse");
    }
}

HtmlDocument::~HtmlDocument()
{
    if (output_ != NULL)
    {
        gumbo_destroy_output(options_ == NULL ? &kGumboDefaultOptions : options_, output_);
        output_ = NULL;
    }

    delete options_;
    options_ = NULL;
}

HtmlNode HtmlDocument::rootNode() const
{
    return HtmlNode(output_->root);
}
