#include "union.h"

Union::Union()
{
}

double Union::membership(const QVariant &element) const{
    return qMax(fuzzySet1->membership(element), fuzzySet2->membership(element));
}

double Union::membership(const QVector<QVariant> &elements) const {
	return qMax(fuzzySet1->membership(elements), fuzzySet2->membership(elements));
}

const FuzzySet *Union::getFuzzySet1() const{
    return fuzzySet1;
}
void Union::setFuzzySet1(const FuzzySet *fuzzySet){
    this->fuzzySet1 = fuzzySet;
}

const FuzzySet *Union::getFuzzySet2() const{
    return fuzzySet2;
}

void Union::setFuzzySet2(const FuzzySet *fuzzySet){
    this->fuzzySet2 = fuzzySet;
}
