#include "fuzzyset.h"
#include <QVariant>

double FuzzySet::cardinality(const QList<QVariant> &element) const {
	double sum = 0;
	for (int i = 0; i < element.size(); i++) {
		sum += membership(element.at(i));
    }
    return sum;
}

double FuzzySet::cardinality(const QList<QVector<QVariant> > &elements) const {
	double sum = 0;
	for (int i = 0; i < elements.size(); i++) {
		sum += membership(elements.at(i));
    }
    return sum;
}

