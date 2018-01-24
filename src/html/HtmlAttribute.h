#ifndef HTMLATTRIBUTE_H
#define HTMLATTRIBUTE_H

#include <QString>

class HtmlAttribute
{
public:
    HtmlAttribute(const QString name, const QString value);

public:
    const QString &name() const {return name_;}
    const QString &value() const {return value_;}

private:
    QString name_;
    QString value_;
};

#endif // HTMLATTRIBUTE_H
