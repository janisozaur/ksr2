#include "fuzzyset.h"
#include <QVariant>

double FuzzySet::cardinality(){
    double sum = 0;
    QVariant element;
    foreach(element, elements){
        sum += membership(element);
    }
    return sum;
}

QList<QVariant> FuzzySet::getElements() const{
    return elements;
}
void FuzzySet::setElements(const QList<QVariant> &elements){
    this->elements = elements;
}

