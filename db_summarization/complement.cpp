#include "complement.h"

Complement::Complement()
{
}

double Complement::membership(const QVariant &element) const {
    return 1 - fuzzySet->membership(element);
}

double Complement::membership(const QVector<QVariant> &dbRow) const {
    return 1 - fuzzySet->membership(dbRow);
}

const FuzzySet *Complement::getFuzzySet() const {
    return fuzzySet;
}

void Complement::setFuzzySet(const FuzzySet *fuzzySet) {
    this->fuzzySet = fuzzySet;
}
