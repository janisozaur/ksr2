#ifndef SUPPORT_H
#define SUPPORT_H

#include "fuzzyset.h"
#include <QVariant>

class Support : public FuzzySet
{
private:
    FuzzySet *fuzzySet;
public:
    Support();
    double membership(QVariant) const;
    double membership(QVector<QVariant>) const;
    FuzzySet *getFuzzySet() const;
    void setFuzzySet(FuzzySet *fuzzySet);
};

#endif // SUPPORT_H
