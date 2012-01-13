#include "FuzzySetType2.h"
#include "FuzzySetEngineHelper.h"

#include <QScriptEngine>

//#include <QDebug>

#ifdef Q_CREATOR_RUN
    #ifndef _OPENMP
        #define _OPENMP
    #endif
#endif

#ifdef _OPENMP
    #include <omp.h>
#endif

FuzzySetType2::FuzzySetType2(const QScriptValueList &params)
{
    int idx = 0;
#ifdef _OPENMP
    idx = omp_get_thread_num();
#endif
    mId = FuzzySetEngineHelper::getIdForThread(idx);
    FuzzySetEngineHelper::createFunctionForThreadId(idx, mId, params);
}

double FuzzySetType2::membership(const QVariant &element) const
{
    int idx = 0;
#ifdef _OPENMP
    idx = omp_get_thread_num();
#endif
    QScriptValue func = FuzzySetEngineHelper::getFuncForThreadId(idx, mId);
    QScriptValueList params;
    if (element.type() == QVariant::Map) {
        const QVariantMap &m = element.toMap();
        params << m.value("x").toDouble() << m.value("y").toDouble();
    } else {
        params << element.toDouble();
    }
    QScriptValue result = func.call(QScriptValue(), params);
    //qDebug() << func.isFunction() << func.toString();
    return result.toNumber();
}

double FuzzySetType2::membership(const QVector<QVariant> &elements) const
{
    return 0;
}
