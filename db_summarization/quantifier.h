#ifndef QUANTIFIER_H
#define QUANTIFIER_H

#include "basicfuzzyset.h"

class Quantifier : public BasicFuzzySet
{
private:
    bool relative;
public:
    Quantifier();
    bool isRealtive() const;
    void setRelative(const bool relative);
};

#endif // QUANTIFIER_H
