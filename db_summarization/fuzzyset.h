#ifndef FUZZYSET_H
#define FUZZYSET_H

#include<QVariant>
#include<QVector>
#include<QList>

class FuzzySet
{
public:
    virtual double membership(QVariant) const = 0;
    virtual double membership(QVector<QVariant>) const = 0;

    double cardinality(QList<QVariant>);
    double cardinality(QList<QVector<QVariant> >);
};
#endif // FUZZYSET_H
