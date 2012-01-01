#include "basicfuzzyset.h"
#include "membershipfuncineterface.h"

BasicFuzzySet::BasicFuzzySet()
{
}

double BasicFuzzySet::membership(QVariant element) const{
    return membershipFunction->value(element);
}

double BasicFuzzySet::membership(QVector<QVariant> dbRow) const{
    return membershipFunction->value(dbRow.at(colNum));
}

MembershipFuncInterface *BasicFuzzySet::getMembershipFunction() const{
    return membershipFunction;
}
void BasicFuzzySet::setMembershipFunction(MembershipFuncInterface *membershipFunction){
    this->membershipFunction = membershipFunction;
}

double BasicFuzzySet::getColNum() const{
    return colNum;
}
void BasicFuzzySet::setColNum(const int colNum){
    this->colNum = colNum;
}
