#ifndef QUANTIFIER_H
#define QUANTIFIER_H

#include "basicfuzzyset.h"
#include "linguisticvalue.h"

class Quantifier : public LinguisticValue
{
private:
    bool relative;
public:
    Quantifier();
    bool isRealtive() const;
    void setRelative(const bool relative);
};

#endif // QUANTIFIER_H
