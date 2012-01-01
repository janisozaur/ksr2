#include "complement.h"

Complement::Complement()
{
}

double Complement::membership(QVariant element) const{
    return 1 - fuzzySet->membership(element);
}

double Complement::membership(QVector<QVariant> dbRow) const{
    return 1 - fuzzySet->membership(dbRow);
}

FuzzySet *Complement::getFuzzySet() const{
    return fuzzySet;
}
void Complement::setFuzzySet(FuzzySet *fuzzySet){
    this->fuzzySet = fuzzySet;
}
