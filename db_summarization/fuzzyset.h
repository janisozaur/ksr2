#ifndef FUZZYSET_H
#define FUZZYSET_H

#include<QVariant>
#include<QVector>
#include<QList>

class FuzzySet
{
public:
	virtual double membership(const QVariant &element) const = 0;
	virtual double membership(const QVector<QVariant> &elements) const = 0;

	double cardinality(const QList<QVariant> &element) const;
	double cardinality(const QList<QVector<QVariant> > &elements) const;
};
#endif // FUZZYSET_H
