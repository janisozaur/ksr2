#ifndef COMPLEMENT_H
#define COMPLEMENT_H

#include "fuzzyset.h"
#include <QVariant>

class Complement : public FuzzySet
{
private:
	const FuzzySet *fuzzySet;
public:
    Complement();
	double membership(const QVariant &) const;
	double membership(const QVector<QVariant> &) const;
	const FuzzySet *getFuzzySet() const;
	void setFuzzySet(const FuzzySet *fuzzySet);
};

#endif // COMPLEMENT_H
