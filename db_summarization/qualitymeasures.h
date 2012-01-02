#ifndef QUALITYMEASURES_H
#define QUALITYMEASURES_H

#include "basicfuzzyset.h"
#include "quantifier.h"
#include <QList>
#include <QVector>
#include <QVariant>

class QualityMeasures
{
public:
	static double computeT1(const Quantifier &quantifier, const QList<const BasicFuzzySet *> &qualifiers, const QList<const BasicFuzzySet *> &summarizers, const QList<QVector<QVariant> > &dbRows);
    static double computeT2T9(QList<BasicFuzzySet> fuzzySets, QList<QVector<QVariant> > dbRows);
    static double computeT3(QList<BasicFuzzySet> quantifiers, QList<BasicFuzzySet> summarizers, QList<QVector<QVariant> > dbRows);
    static double computeT4(QList<BasicFuzzySet> quantifiers, QList<BasicFuzzySet> summarizers, QList<QVector<QVariant> > dbRows);
    static double computeT5T11(int summarizersNum);
    static double computeT6(Quantifier quantifier, QList<QVector<QVariant> > dbRows);
    static double computeT7(Quantifier quantifier, int dbRowsSize);
};

#endif // QUALITYMEASURES_H
