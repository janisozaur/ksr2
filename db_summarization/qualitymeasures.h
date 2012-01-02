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
	static double computeT2T9(const QList<const BasicFuzzySet *> &fuzzySets, const QList<QVector<QVariant> > &dbRows);
	static double computeT3(const QList<const BasicFuzzySet *> &quantifiers, const QList<const BasicFuzzySet *> &summarizers, const QList<QVector<QVariant> > &dbRows);
	static double computeT4(const QList<const BasicFuzzySet *> &quantifiers, const QList<const BasicFuzzySet *> &summarizers, const QList<QVector<QVariant> > &dbRows);
	static double computeT5T11(const int &summarizersNum);
	static double computeT6(const Quantifier &quantifier, const QList<QVector<QVariant> > &dbRows);
	static double computeT7(const Quantifier &quantifier, const int &dbRowsSize);
};

#endif // QUALITYMEASURES_H
