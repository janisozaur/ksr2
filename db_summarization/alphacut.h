#ifndef ALPHACUT_H
#define ALPHACUT_H

#include "fuzzyset.h"
#include <QVariant>

class AlphaCut : FuzzySet
{
private:
    FuzzySet *fuzzySet;
public:
    AlphaCut();
    double membership(QVariant) const;
    FuzzySet *getFuzzySet() const;
    void setFuzzySet(FuzzySet *fuzzySet);
};

#endif // ALPHACUT_H
