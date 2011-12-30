#ifndef BASICFUZZYSET_H
#define BASICFUZZYSET_H

#include "membershipfuncineterface.h"
#include "fuzzyset.h"
#include<QVariant>
#include<QList>

class BasicFuzzySet : public FuzzySet
{
private:
    MembershipFuncInterface *membershipFunction;
public:
    BasicFuzzySet();
    double membership(QVariant);
    MembershipFuncInterface *getMembershipFunction() const;
    void setMembershipFunction(MembershipFuncInterface *membershipFunction);
};

#endif // BASICFUZZYSET_H
