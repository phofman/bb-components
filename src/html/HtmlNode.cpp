#include "HtmlNode.h"
#include "HtmlAttribute.h"

#include "gumbo.h"

#include <stdexcept>

#include <QDebug>

typedef struct InternalClassTag
{
    QString className;
    int tag;
} ClassTag;

HtmlNode::HtmlNode(GumboNode *node)
    : node_(node)
{
}

int HtmlNode::tag() const
{
    if (isElement())
        return node_->v.element.tag;

    return GUMBO_TAG_UNKNOWN;
}

QString HtmlNode::tagName() const
{
    GumboTag tag = node_->v.element.tag;
    return QString::fromUtf8(gumbo_normalized_tagname(tag));
}

bool HtmlNode::isElement() const
{
    return node_->type == GUMBO_NODE_ELEMENT;
}

QString HtmlNode::innerText() const
{
    QString result;

    GumboVector& vec = node_->v.element.children;
    for (uint i = 0, e = vec.length; i < e; ++i)
    {
        GumboNode *n = static_cast<GumboNode*>(vec.data[i]);
        if (n->type == GUMBO_NODE_TEXT || n->type == GUMBO_NODE_WHITESPACE)
        {
            result += QString::fromUtf8(n->v.text.text);
        }
    }
    return result;
}

HtmlNodesCollection HtmlNode::childNodes() const
{
    HtmlNodesCollection result;

    GumboVector& vec = node_->v.element.children;
    for (uint i = 0, e = vec.length; i < e; ++i)
    {
        GumboNode *n = static_cast<GumboNode*>(vec.data[i]);
        if (n->type == GUMBO_NODE_ELEMENT)
        {
            result.push_back(n);
        }
    }

    return result;
}

int HtmlNode::childCount() const
{
    if (!isElement())
        return 0;

    int count = 0;
    GumboVector& vec = node_->v.element.children;
    for (uint i = 0, e = vec.length; i < e; ++i)
    {
        GumboNode *n = static_cast<GumboNode*>(vec.data[i]);
        if (n->type == GUMBO_NODE_ELEMENT)
        {
            count++;
        }
    }
    return count;
}

QString HtmlNode::attribute(const QString &name) const
{
    if (name.isEmpty())
    {
        throw std::invalid_argument("Invalid attribute name");
    }

    GumboAttribute *attr = gumbo_get_attribute(&node_->v.element.attributes, name.toUtf8().constData());
    return attr != NULL ? QString::fromUtf8(attr->value) : QString();
}

HtmlAttributesCollection HtmlNode::attributes() const
{
    HtmlAttributesCollection result;

    for (uint i = 0, len = node_->v.element.attributes.length; i < len; ++i)
    {
        GumboAttribute *attr = static_cast<GumboAttribute*>(node_->v.element.attributes.data[i]);
        result.push_back(HtmlAttribute(QString::fromUtf8(attr->name), QString::fromUtf8(attr->value)));
    }

    return result;
}

QString HtmlNode::id() const
{
    GumboAttribute *attr = gumbo_get_attribute(&node_->v.element.attributes, "id");
    return attr != NULL ? QString::fromUtf8(attr->value) : QString();
}

QString HtmlNode::classValue() const
{
    GumboAttribute *attr = gumbo_get_attribute(&node_->v.element.attributes, "class");
    return attr != NULL ? QString::fromUtf8(attr->value) : QString();
}

QStringList HtmlNode::classes() const
{
    GumboAttribute *attr = gumbo_get_attribute(&node_->v.element.attributes, "class");
    if (attr != NULL)
    {
        QString value = QString::fromUtf8(attr->value);
        return value.split(' ', QString::SkipEmptyParts, Qt::CaseInsensitive);
    }
    return QStringList();
}

static bool forEachTree(HtmlNodesCollection &result, GumboNode *n, FuncNodePredicate iterator, void *data)
{
    if (n != NULL && n->type == GUMBO_NODE_ELEMENT)
    {
        HtmlNode node(n);
        if (iterator(node, data))
        {
            result.push_back(node);
            return true;
        }

        for (uint i = 0; i < n->v.element.children.length; ++i)
        {
            GumboNode *child = static_cast<GumboNode*>(n->v.element.children.data[i]);

            if (child != NULL && child->type == GUMBO_NODE_ELEMENT)
            {
                forEachTree(result, child, iterator, data);
            }
        }
    }

    return false;
}

static GumboNode *forEachSingle(GumboNode *n, FuncNodePredicate predicate, void *data)
{
    if (n == NULL || n->type != GUMBO_NODE_ELEMENT)
    {
        return NULL;
    }

    HtmlNode node(n);
    if (predicate(node, data))
    {
        return n;
    }

    GumboVector* children = &n->v.element.children;
    for (uint i = 0; i < children->length; ++i)
    {
        GumboNode *child = static_cast<GumboNode *>(children->data[i]);
        GumboNode *result = forEachSingle(child, predicate, data);
        if (result != NULL)
        {
            return result;
        }
    }

    return NULL;
}

HtmlNodesCollection HtmlNode::forEach(FuncNodePredicate iterator, void *data) const
{
    if (iterator == NULL)
    {
        throw std::invalid_argument("Invalid iterator");
    }

    HtmlNodesCollection result;

    forEachTree(result, node_, iterator, data);
    return result;
}

static bool FindItemByClass(const HtmlNode &node, void *data)
{
    return node.classes().contains(*(const QString *)data);
}

static bool FindItemByTag(const HtmlNode &node, void *data)
{
    return node.tag() == (int)data;
}

static bool FindItemByTagClass(const HtmlNode &node, void *data)
{
    ClassTag *param = (ClassTag *)data;

    //qDebug() << node.tagName() << ", id: " << node.id() << ", class: " << node.classValue();

    return node.classes().contains(param->className) && node.tag() == param->tag;
}

HtmlNodesCollection HtmlNode::forEachByClass(const QString &name) const
{
    return forEach(FindItemByClass, (void *)&name);
}

HtmlNodesCollection HtmlNode::forEachByTag(int tag) const
{
    return forEach(FindItemByTag, (void *)tag);
}

HtmlNode *HtmlNode::find(FuncNodePredicate predicate, void *data) const
{
    if (predicate == NULL)
    {
        throw std::invalid_argument("Invalid predicate");
    }

    GumboNode *result = forEachSingle(node_, predicate, data);
    return result != NULL ? new HtmlNode(result) : NULL;
}

HtmlNode *HtmlNode::findByClass(const QString &name) const
{
    return find(FindItemByClass, (void *)&name);
}

HtmlNode *HtmlNode::findByTag(int tag) const
{
    return find(FindItemByTag, (void *)tag);
}

HtmlNode *HtmlNode::findByTagClass(int tag, const QString &name) const
{
    ClassTag param;
    param.className = name;
    param.tag = tag;

    return find(FindItemByTagClass, (void *)&param);
}
