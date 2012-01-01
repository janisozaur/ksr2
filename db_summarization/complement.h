#ifndef COMPLEMENT_H
#define COMPLEMENT_H

#include "fuzzyset.h"
#include <QVariant>

class Complement : public FuzzySet
{
private:
    FuzzySet *fuzzySet;
public:
    Complement();
    double membership(QVariant) const;
    double membership(QVector<QVariant>) const;
    FuzzySet *getFuzzySet() const;
    void setFuzzySet(FuzzySet *fuzzySet);
};

#endif // COMPLEMENT_H
