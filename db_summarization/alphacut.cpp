#include "alphacut.h"
#include <QVariant>

AlphaCut::AlphaCut()
{
}

double AlphaCut::membership(QVariant element) const{
    return fuzzySet->membership(element) > 0 ? 1 : 0;
}

FuzzySet *AlphaCut::getFuzzySet() const{
    return fuzzySet;
}
void AlphaCut::setFuzzySet(FuzzySet *fuzzySet){
    this->fuzzySet = fuzzySet;
}
