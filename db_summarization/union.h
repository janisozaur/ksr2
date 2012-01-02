#ifndef UNION_H
#define UNION_H

#include "fuzzyset.h"
#include <QVariant>

class Union : public FuzzySet
{
private:
	const FuzzySet *fuzzySet1;
	const FuzzySet *fuzzySet2;
public:
    Union();
	double membership(const QVariant &element) const;
    double membership(const QVector<QVariant> &elements) const;

	FuzzySet const *getFuzzySet1() const;
	void setFuzzySet1(const FuzzySet *fuzzySet);

	FuzzySet const *getFuzzySet2() const;
	void setFuzzySet2(const FuzzySet *fuzzySet);
};

#endif // UNION_H
