#include "linguisticvalue.h"

LinguisticValue::LinguisticValue()
{
}

const QString LinguisticValue::getLabel() const{
    return label;
}
void LinguisticValue::setLabel(const QString label){
    this->label = label;
}

const int LinguisticValue::getColNum() const{
    return colNum;
}
void LinguisticValue::setColNum(const int label){
    this->colNum = colNum;
}
