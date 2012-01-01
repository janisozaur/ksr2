#ifndef ALPHACUT_H
#define ALPHACUT_H

#include "fuzzyset.h"
#include <QVariant>

class AlphaCut : public FuzzySet
{
private:
    FuzzySet *fuzzySet;
public:
    AlphaCut();
    double membership(QVariant) const;
    double membership(QVector<QVariant>) const;
    FuzzySet *getFuzzySet() const;
    void setFuzzySet(FuzzySet *fuzzySet);
};

#endif // ALPHACUT_H
