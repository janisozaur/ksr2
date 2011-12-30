#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "fuzzyset.h"
#include <QVariant>

class Intersection : FuzzySet
{
private:
    FuzzySet *fuzzySet1;
    FuzzySet *fuzzySet2;
public:
    Intersection();
    double membership(QVariant) const;

    FuzzySet *getFuzzySet1() const;
    void setFuzzySet1(FuzzySet *fuzzySet);

    FuzzySet *getFuzzySet2() const;
    void setFuzzySet2(FuzzySet *fuzzySet);
};

#endif // INTERSECTION_H
