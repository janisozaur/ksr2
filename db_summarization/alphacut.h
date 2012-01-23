#ifndef ALPHACUT_H
#define ALPHACUT_H

#include "fuzzyset.h"
#include <QVariant>

class AlphaCut : public FuzzySet
{
private:
	const FuzzySet * fuzzySet;
        double alpha;
public:
    AlphaCut();
	double membership(const QVariant &element) const;
	double membership(const QVector<QVariant> &elements) const;
	const FuzzySet *getFuzzySet() const;
	void setFuzzySet(const FuzzySet *fuzzySet);
        const double getAlpha() const;
        void setAlpha(const double alpha);
};

#endif // ALPHACUT_H
