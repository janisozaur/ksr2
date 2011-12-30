#include "intersection.h"

Intersection::Intersection()
{
}

double Intersection::membership(QVariant element) const{
    return qMin(fuzzySet1->membership(element), fuzzySet2->membership(element));
}

FuzzySet *Intersection::getFuzzySet1() const{
    return fuzzySet1;
}
void Intersection::setFuzzySet1(FuzzySet *fuzzySet){
    this->fuzzySet1 = fuzzySet;
}


FuzzySet *Intersection::getFuzzySet2() const{
    return fuzzySet2;
}
void Intersection::setFuzzySet2(FuzzySet *fuzzySet){
    this->fuzzySet2 = fuzzySet;
}
