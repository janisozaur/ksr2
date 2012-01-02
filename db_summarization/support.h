#ifndef SUPPORT_H
#define SUPPORT_H

#include "fuzzyset.h"
#include <QVariant>

class Support : public FuzzySet
{
private:
	const FuzzySet *fuzzySet;

public:
    Support();
	double membership(const QVariant &element) const;
	double membership(const QVector<QVariant> &elements) const;
	const FuzzySet *getFuzzySet() const;
	void setFuzzySet(const FuzzySet *fuzzySet);
};

#endif // SUPPORT_H
