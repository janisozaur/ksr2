#include "intersection.h"

Intersection::Intersection()
{
}

double Intersection::membership(const QVariant &element) const {
    return qMin(fuzzySet1->membership(element), fuzzySet2->membership(element));
}

double Intersection::membership(const QVector<QVariant> &elements) const {
	return qMin(fuzzySet1->membership(elements), fuzzySet2->membership(elements));
}

FuzzySet const *Intersection::getFuzzySet1() const{
    return fuzzySet1;
}
void Intersection::setFuzzySet1(const FuzzySet *fuzzySet) {
    this->fuzzySet1 = fuzzySet;
}

FuzzySet const *Intersection::getFuzzySet2() const {
    return fuzzySet2;
}

void Intersection::setFuzzySet2(const FuzzySet *fuzzySet){
    this->fuzzySet2 = fuzzySet;
}
