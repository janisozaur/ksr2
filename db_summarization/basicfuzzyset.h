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
    int colNum;
public:
    BasicFuzzySet();
    double membership(QVariant) const;
    double membership(QVector<QVariant>) const;
    MembershipFuncInterface *getMembershipFunction() const;
    void setMembershipFunction(MembershipFuncInterface *membershipFunction);

    double getColNum() const;
    void setColNum(const int colNum);
};

#endif // BASICFUZZYSET_H
