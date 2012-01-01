#include "union.h"

Union::Union()
{
}

double Union::membership(QVariant element) const{
    return qMax(fuzzySet1->membership(element), fuzzySet2->membership(element));
}

double Union::membership(QVector<QVariant> dbRow) const{
    return qMax(fuzzySet1->membership(dbRow), fuzzySet2->membership(dbRow));
}

FuzzySet *Union::getFuzzySet1() const{
    return fuzzySet1;
}
void Union::setFuzzySet1(FuzzySet *fuzzySet){
    this->fuzzySet1 = fuzzySet;
}


FuzzySet *Union::getFuzzySet2() const{
    return fuzzySet2;
}
void Union::setFuzzySet2(FuzzySet *fuzzySet){
    this->fuzzySet2 = fuzzySet;
}
