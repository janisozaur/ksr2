#include "alphacut.h"
#include <QVariant>

AlphaCut::AlphaCut()
{
    alpha = 0;
}

double AlphaCut::membership(const QVariant &element) const {
    return fuzzySet->membership(element) > alpha ? 1 : 0;
}

double AlphaCut::membership(const QVector<QVariant> &elements) const {
        return fuzzySet->membership(elements) > alpha ? 1 : 0;
}

FuzzySet const *AlphaCut::getFuzzySet() const {
    return fuzzySet;
}
void AlphaCut::setFuzzySet(const FuzzySet *fuzzySet){
    this->fuzzySet = fuzzySet;
}

const double AlphaCut::getAlpha() const{
    return alpha;
}
void AlphaCut::setAlpha(const double alpha){
    this->alpha = alpha;
}
