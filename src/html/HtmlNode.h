#ifndef HTMLNODE_H
#define HTMLNODE_H

#include <QString>
#include <QStringList>
#include <vector>

extern "C" {
    struct GumboInternalNode;

    typedef struct GumboInternalNode GumboNode;
}

class HtmlNode;
typedef std::vector<HtmlNode> HtmlNodesCollection;

class HtmlAttribute;
typedef std::vector<HtmlAttribute> HtmlAttributesCollection;

typedef bool (*FuncNodePredicate)(const HtmlNode &node, void *data);


class HtmlNode
{
public:
    HtmlNode(GumboNode *node);

public:
    int tag() const;
    QString tagName() const;
    inline QString nodeName() const {return tagName();}

    bool isElement() const;
    QString innerText() const;

    HtmlNodesCollection childNodes() const;
    int childCount() const;

    QString attribute(const QString &name) const;
    HtmlAttributesCollection attributes() const;

    QString id() const;
    QString classValue() const;
    QStringList classes() const;

    HtmlNodesCollection forEach(FuncNodePredicate iterator, void *data = NULL) const;
    HtmlNodesCollection forEachByClass(const QString &name) const;
    HtmlNodesCollection forEachByTag(int tag) const;
    HtmlNode *find(FuncNodePredicate predicate, void *data = NULL) const;
    HtmlNode *findByClass(const QString &name) const;
    HtmlNode *findByTag(int tag) const;
    HtmlNode *findByTagClass(int tag, const QString &name) const;

private:
    GumboNode *node_;
};

#endif // HTMLNODE_H
