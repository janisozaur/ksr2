#include "linguisticvalue.h"

LinguisticValue::LinguisticValue()
{
}

double LinguisticValue::membership(const QVariant &element) const {
    return membershipFunction->value(element);
}

double LinguisticValue::membership(const QVector<QVariant> &elements) const {
    return membershipFunction->value(elements.at(colNum));
}

const MembershipFuncInterface *LinguisticValue::getMembershipFunction() const {
    return membershipFunction;
}
void LinguisticValue::setMembershipFunction(const MembershipFuncInterface *membershipFunction) {
    this->membershipFunction = membershipFunction;
}

QString LinguisticValue::getLabel() const{
    return label;
}
void LinguisticValue::setLabel(const QString label){
    this->label = label;
}

int LinguisticValue::getColNum() const{
    return colNum;
}
void LinguisticValue::setColNum(const int colNum){
    this->colNum = colNum;
}
