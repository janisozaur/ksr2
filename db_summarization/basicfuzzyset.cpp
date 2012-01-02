#include "basicfuzzyset.h"
#include "membershipfuncineterface.h"

BasicFuzzySet::BasicFuzzySet()
{
}

double BasicFuzzySet::membership(const QVariant &element) const {
    return membershipFunction->value(element);
}

double BasicFuzzySet::membership(const QVector<QVariant> &elements) const {
	return membershipFunction->value(elements.at(colNum));
}

const MembershipFuncInterface *BasicFuzzySet::getMembershipFunction() const {
    return membershipFunction;
}
void BasicFuzzySet::setMembershipFunction(const MembershipFuncInterface *membershipFunction) {
    this->membershipFunction = membershipFunction;
}

double BasicFuzzySet::getColNum() const {
    return colNum;
}
void BasicFuzzySet::setColNum(const int colNum) {
    this->colNum = colNum;
}
