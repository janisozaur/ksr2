#ifndef QUALITYMEASURES_H
#define QUALITYMEASURES_H

#include "basicfuzzyset.h"
#include "quantifier.h"
#include <QList>
#include <QMap>
#include <QVector>
#include <QVariant>

class QualityMeasures
{
public:
	static double computeT1(const Quantifier &quantifier, const QList<const BasicFuzzySet *> &qualifiers, const QList<const BasicFuzzySet *> &summarizers, const QList<QVector<QVariant> > &dbRows);
    static double computeT2T9(QList<const BasicFuzzySet *> fuzzySets, QList<QVector<QVariant> > dbRows);
    static double computeT3(QList<const BasicFuzzySet *> qualifiers, QList<const BasicFuzzySet *> summarizers, QList<QVector<QVariant> > dbRows);
    static double computeT4(QList<const BasicFuzzySet *> qualifiers, QList<const BasicFuzzySet *> summarizers, QList<QVector<QVariant> > dbRows);
    static double computeT5T11(int summarizersNum);
    static double computeT6(Quantifier quantifier, int dbRowsSize);
    static double computeT7(Quantifier quantifier, int dbRowsSize);
    static double computeT8T10(QList<const BasicFuzzySet *> fuzzySets, QList<QVector<QVariant> > dbRows);
    static double computeTotalQuality(const QMap<QString, double> &weightsMap, const Quantifier &quantifier, const QList<const BasicFuzzySet *> &qualifiers, const QList<const BasicFuzzySet *> &summarizers, const QList<QVector<QVariant> > &dbRows);
};

#endif // QUALITYMEASURES_H
