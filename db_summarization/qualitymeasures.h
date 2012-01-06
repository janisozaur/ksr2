#ifndef QUALITYMEASURES_H
#define QUALITYMEASURES_H

#include "linguisticvalue.h"
#include "quantifier.h"
#include "summarization.h"

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
                                  const QList<const LinguisticValue *> &qualifiers,
                                  const QList<const LinguisticValue *> &summarizers,
								  const QList<QVector<QVariant> > &dbRows);
	static double computeT1(const Quantifier &quantifier,
                            const QList<const LinguisticValue *> &qualifiers,
                            const QList<const LinguisticValue *> &summarizers,
							const QList<QVector<QVariant> > &dbRows);
    static double computeT2T9(const QList<const LinguisticValue *> &fuzzySets,
							  const QList<QVector<QVariant> > &dbRows);
    static double computeT3(const QList<const LinguisticValue *> &qualifiers,
                            const QList<const LinguisticValue *> &summarizers,
							const QList<QVector<QVariant> > &dbRows);
    static double computeT4(const QList<const LinguisticValue *> &qualifiers,
                            const QList<const LinguisticValue *> &summarizers,
							const QList<QVector<QVariant> > &dbRows);
	static double computeT5T11(const int &summarizersNum);
	static double computeT6(const Quantifier &quantifier,
							const int &dbRowsSize);
	static double computeT7(const Quantifier &quantifier,
							const int &dbRowsSize);
    static double computeT8T10(QList<const LinguisticValue *> fuzzySets,
							   const QList<QVector<QVariant> > &dbRows);
    static double computeTotalQuality(const QMap<QString, double> &weightsMap, const Quantifier &quantifier, const QList<const LinguisticValue *> &qualifiers, const QList<const LinguisticValue *> &summarizers, const QList<QVector<QVariant> > &dbRows);


    static double computeT1(const Summarization &summarization,const QList<QVector<QVariant> > &dbRows);
    static double computeT2(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT3(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT4(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT5(const Summarization &summarization);
    static double computeT6(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT7(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT8(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT9(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT10(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);
    static double computeT11(const Summarization &summarization);
    static double computeTotalQuality(const QMap<QString, double> &weightsMap, const Summarization &summarization, const QList<QVector<QVariant> > &dbRows);

    static QList<QPair<double, Summarization> > computeTotalQuality(const QMap<QString, double> &weightsMap, const QList<Summarization> &summarizationList, const QList<QVector<QVariant> > &dbRows);

};

#endif // QUALITYMEASURES_H
