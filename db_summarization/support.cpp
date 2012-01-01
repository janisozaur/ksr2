#include "support.h"

Support::Support()
{
}

double Support::membership(QVariant element) const{
    if(fuzzySet->membership(element) >0){
            return 1;
    }
    return 0;
}

double Support::membership(QVector<QVariant> dbRow) const{
    if(fuzzySet->membership(dbRow) >0){
            return 1;
    }
    return 0;
}

FuzzySet *Support::getFuzzySet() const{
    return fuzzySet;
}
void Support::setFuzzySet(FuzzySet *fuzzySet){
    this->fuzzySet = fuzzySet;
}
