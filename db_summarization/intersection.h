#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "fuzzyset.h"
#include <QVariant>

class Intersection : public FuzzySet
{
private:
	const FuzzySet *fuzzySet1;
	const FuzzySet *fuzzySet2;
public:
    Intersection();
	double membership(const QVariant &element) const;
	double membership(const QVector<QVariant> &elements) const;

	const FuzzySet *getFuzzySet1() const;
	void setFuzzySet1(const FuzzySet *const fuzzySet);

	const FuzzySet *getFuzzySet2() const;
	void setFuzzySet2(const FuzzySet *fuzzySet);
};

#endif // INTERSECTION_H
