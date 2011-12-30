#include "basicfuzzyset.h"
#include "membershipfuncineterface.h"

BasicFuzzySet::BasicFuzzySet()
{
}

double BasicFuzzySet::membership(QVariant element){
    return membershipFunction->value(element);
}

MembershipFuncInterface *BasicFuzzySet::getMembershipFunction() const{
    return membershipFunction;
}
void BasicFuzzySet::setMembershipFunction(MembershipFuncInterface *membershipFunction){
    this->membershipFunction = membershipFunction;
}
