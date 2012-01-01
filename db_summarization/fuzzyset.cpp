#include "fuzzyset.h"
#include <QVariant>

double FuzzySet::cardinality(QList<QVariant> elements){
    double sum = 0;
    QVariant element;
    foreach(element, elements){
        sum += membership(element);
    }
    return sum;
}

double FuzzySet::cardinality(QList<QVector<QVariant> > dbRows){
    double sum = 0;
    QVector<QVariant> dbRow;
    foreach(dbRow, dbRows){
        sum += membership(dbRow);
    }
    return sum;
}

