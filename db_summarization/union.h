#ifndef UNION_H
#define UNION_H

#include "fuzzyset.h"
#include <QVariant>

class Union : public FuzzySet
{
private:
    FuzzySet *fuzzySet1;
    FuzzySet *fuzzySet2;
public:
    Union();
    double membership(QVariant) const;
    double membership(QVector<QVariant>) const;

    FuzzySet *getFuzzySet1() const;
    void setFuzzySet1(FuzzySet *fuzzySet);

    FuzzySet *getFuzzySet2() const;
    void setFuzzySet2(FuzzySet *fuzzySet);
};

#endif // UNION_H
