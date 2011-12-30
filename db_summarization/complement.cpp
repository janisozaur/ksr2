#include "complement.h"

Complement::Complement()
{
}

double Complement::membership(QVariant element) const{
    return 1 - fuzzySet->membership(element);
}

FuzzySet *Complement::getFuzzySet() const{
    return fuzzySet;
}
void Complement::setFuzzySet(FuzzySet *fuzzySet){
    this->fuzzySet = fuzzySet;
}
