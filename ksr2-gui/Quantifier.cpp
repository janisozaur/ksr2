#include "Quantifier.h"

#include <QStringList>

Quantifier::Quantifier(QObject *parent) :
    QObject(parent)
{
}

Quantifier::Quantifier(const QString &name, const QList<double> &values, const Range &_range, const QString &type, QObject *parent) :
    QObject(parent),
    mName(name),
    mValues(values),
    mRange(_range),
    mTypeName(type)
{
}

Quantifier::Quantifier(const Quantifier &q) :
    QObject(q.parent()),
    mName(q.quantName()),
    mValues(q.values()),
    mRange(q.range()),
    mTypeName(q.typeName())
{
}

QString Quantifier::quantName() const
{
    return mName;
}

void Quantifier::setQuantName(const QString &name)
{
    mName = name;
}

QList<double> Quantifier::values() const
{
    return mValues;
}

void Quantifier::setValues(const QList<double> &val)
{
    mValues = val;
}

Range Quantifier::range() const
{
    return mRange;
}

void Quantifier::setRange(const Range &range)
{
    mRange = range;
}

QString Quantifier::typeName() const
{
    return mTypeName;
}

void Quantifier::setTypeName(const QString &name)
{
    mTypeName = name;
}

QTextStream& operator<<(QTextStream &qs, const Quantifier &obj)
{
    QStringList ql;
    for (int i = 0; i < obj.mValues.size(); i++) {
        ql << QString::number(obj.mValues.at(i));
    }
    qs << obj.quantName() << ":"
       << (obj.range() == Absolute ? "ABSOLUTE" : "RELATIVE") << ":"
       << obj.mTypeName << ":" << ql.join(":");
    return qs;
}
