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
	enum Measures {
		T1 = 1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
	};

	static QList<double> computeT(const QList<Measures> &measures,
								  const Quantifier &quantifier,
								  const QList<const BasicFuzzySet *> &qualifiers,
								  const QList<const BasicFuzzySet *> &summarizers,
								  const QList<QVector<QVariant> > &dbRows);
	static double computeT1(const Quantifier &quantifier,
							const QList<const BasicFuzzySet *> &qualifiers,
							const QList<const BasicFuzzySet *> &summarizers,
							const QList<QVector<QVariant> > &dbRows);
	static double computeT2T9(const QList<const BasicFuzzySet *> &fuzzySets,
							  const QList<QVector<QVariant> > &dbRows);
	static double computeT3(const QList<const BasicFuzzySet *> &qualifiers,
							const QList<const BasicFuzzySet *> &summarizers,
							const QList<QVector<QVariant> > &dbRows);
	static double computeT4(const QList<const BasicFuzzySet *> &qualifiers,
							const QList<const BasicFuzzySet *> &summarizers,
							const QList<QVector<QVariant> > &dbRows);
	static double computeT5T11(const int &summarizersNum);
	static double computeT6(const Quantifier &quantifier,
							const int &dbRowsSize);
	static double computeT7(const Quantifier &quantifier,
							const int &dbRowsSize);
	static double computeT8T10(QList<const BasicFuzzySet *> fuzzySets,
							   const QList<QVector<QVariant> > &dbRows);
    static double computeTotalQuality(const QMap<QString, double> &weightsMap, const Quantifier &quantifier, const QList<const BasicFuzzySet *> &qualifiers, const QList<const BasicFuzzySet *> &summarizers, const QList<QVector<QVariant> > &dbRows);
};

#endif // QUALITYMEASURES_H