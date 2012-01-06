#ifndef BASICFUZZYSET_H
#define BASICFUZZYSET_H

#include "membershipfuncineterface.h"
#include "fuzzyset.h"
#include<QVariant>
#include<QList>

class BasicFuzzySet : public FuzzySet
{
private:
	const MembershipFuncInterface *membershipFunction;
protected:
    int colNum;
public:
    BasicFuzzySet();
	double membership(const QVariant &element) const;
	double membership(const QVector<QVariant> &elements) const;
	const MembershipFuncInterface *getMembershipFunction() const;
	void setMembershipFunction(const MembershipFuncInterface *membershipFunction);

    const int getColNum() const;
    void setColNum(const int colNum);
};

#endif // BASICFUZZYSET_H
