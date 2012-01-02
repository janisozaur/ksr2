#include "alphacut.h"
#include <QVariant>

AlphaCut::AlphaCut()
{
}

double AlphaCut::membership(const QVariant &element) const {
    return fuzzySet->membership(element) > 0 ? 1 : 0;
}

double AlphaCut::membership(const QVector<QVariant> &elements) const {
	return fuzzySet->membership(elements) > 0 ? 1 : 0;
}

FuzzySet const *AlphaCut::getFuzzySet() const {
    return fuzzySet;
}
void AlphaCut::setFuzzySet(const FuzzySet *fuzzySet){
    this->fuzzySet = fuzzySet;
}
