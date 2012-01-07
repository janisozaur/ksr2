#include "Quantifier.h"

#include <QMetaType>

Q_DECLARE_METATYPE(Quantifier *)

Quantifier::Quantifier(QObject *parent) :
    QObject(parent)
{
}

Quantifier::Quantifier(const QString &name, const QList<double> &values, const Range &_range, QObject *parent) :
    QObject(parent),
    mName(name),
    mValues(values),
    mRange(_range)
{
}

Quantifier::Quantifier(const Quantifier &q) :
    QObject(q.parent()),
    mName(q.quantName()),
    mValues(q.values()),
    mRange(q.range())
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
