#include "support.h"

Support::Support()
{
}

double Support::membership(const QVariant &element) const {
    if(fuzzySet->membership(element) >0){
            return 1;
    }
    return 0;
}

double Support::membership(const QVector<QVariant> &elements) const {
	if(fuzzySet->membership(elements) >0){
            return 1;
    }
    return 0;
}

const FuzzySet *Support::getFuzzySet() const{
    return fuzzySet;
}

void Support::setFuzzySet(const FuzzySet *fuzzySet){
    this->fuzzySet = fuzzySet;
}
