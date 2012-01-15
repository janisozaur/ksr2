#include <QtCore/QCoreApplication>
#include <QFileInfoList>
#include <QStringList>
#include <QDebug>
#include <QList>
#include <QBitArray>
#include <QPair>
#include <QElapsedTimer>
#include "trapezoidfunction.h"
#include "quantifier.h"
#include "qualitymeasures.h"
#include "linguisticvalue.h"
#include "fileparser.h"
#include "summarization.h"
#include "summarizationgenerator.h"

#include "FuzzySetType2.h"
#include "FuzzySetEngineHelper.h"
#include "intersection.h"

#include <QScriptValue>
#include <QScriptEngine>

#ifdef Q_CREATOR_RUN
    #ifndef _OPENMP
        #define _OPENMP
    #endif
#endif

#ifdef _OPENMP
    #include <omp.h>
#endif

int testType2FuzzySet(QCoreApplication &a)
{
    if (a.arguments().size() < 1) {
        qCritical() << "too few arguments";
        return -1;
    }
    const QString filename = a.arguments().at(1);
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly)) {
        qCritical() << "failed to open file" << filename;
        return -2;
    }
    const QString source = f.readAll().trimmed();
    f.close();

    int threadCount = 1;
#ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp single
        {
            threadCount = omp_get_num_threads();
        }
    }
#endif

    FuzzySetEngineHelper::init(threadCount, source);
    QScriptValue v = FuzzySetEngineHelper::getEngine(0)->newArray(4);
    v.setProperty(0, 0);
    v.setProperty(1, 1);
    v.setProperty(2, 2);
    v.setProperty(3, 3);
    QScriptValueList params;
    params << "trapezoid" << v;
    FuzzySetType2 fst2(params);
    QVariantMap membershipParams;
    membershipParams["x"] = 2.75;
    membershipParams["y"] = 0.75;
    qDebug() << "fst2 membership for values" << membershipParams << ":"
             << fst2.membership(membershipParams);

    v.setProperty(1, 2);
    membershipParams["x"] = 1;
    membershipParams["y"] = -1;
    params.clear();
    params << "trapezoid" << v;
    FuzzySetType2 fst2_2(params);
    qDebug() << "fst2 membership for values" << membershipParams << ":"
             << fst2.membership(membershipParams);
    qDebug() << "fst2_2 membership for values" << membershipParams << ":"
             << fst2_2.membership(membershipParams);
    Intersection i;
    i.setFuzzySet1(&fst2);
    i.setFuzzySet2(&fst2_2);
    qDebug() << "intersection membership for values" << membershipParams << ":"
             << i.membership(membershipParams);
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString dataFilePath = "database10000.dat";
    QString dataDescFilePath = "data_description.txt";


    FileParser parser = FileParser();

    QList<QVector<QVariant> > dbRows = parser.parseDataBase(dataFilePath, dataDescFilePath);

    QList<Quantifier> quantifierList =  parser.parseQuantifiers("fuzzy_sets_quantifiers.txt");
    qDebug()<<"Liczba kwantyfikatorow: "<< quantifierList.size();

    QMap<int, QList<const LinguisticValue *> >linguisticValMap = parser.parseLinguisticValues("fuzzy_sets_lingValues.txt");
    QList<QList<const LinguisticValue *> > mapValues = linguisticValMap.values();
    int valuesCount = 0;
    for(int i=0; i<mapValues.size(); i++){
        valuesCount+=mapValues.at(i).size();
    }

    qDebug()<<"Liczba zmiennych lingwistycznych: "<< linguisticValMap.size();
    qDebug()<<"Liczba wartosci lingwistycznych: "<< valuesCount;

    QMap<QString, double> weightsMap = QMap<QString, double>();
    weightsMap.insert("T1", 1);
    weightsMap.insert("T2", 1);
    weightsMap.insert("T3", 1);
    weightsMap.insert("T4", 1);
    weightsMap.insert("T5", 1);
    weightsMap.insert("T6", 1);
    weightsMap.insert("T7", 1);
    weightsMap.insert("T8", 1);
    weightsMap.insert("T9", 1);
    weightsMap.insert("T10", 1);
    weightsMap.insert("T11", 1);

//    QMap<QString, double> weightsMap = QMap<QString, double>();
//    weightsMap.insert("T1", 1);
//    weightsMap.insert("T2", 1);
//    weightsMap.insert("T3", 1);
//    weightsMap.insert("T4", 1);
//    weightsMap.insert("T5", 1);
//    weightsMap.insert("T6", 0);
//    weightsMap.insert("T7", 0);
//    weightsMap.insert("T8", 0);
//    weightsMap.insert("T9", 0);
//    weightsMap.insert("T10", 0);
//    weightsMap.insert("T11", 0);


    int res = 0;
        //res = testType2FuzzySet(a);
    if (res < 0) {
        return res;
    }

    QElapsedTimer timer;
    timer.start();

    SummarizationGenerator generator = SummarizationGenerator();
    QList<Summarization> summarizationList = generator.generateAll(quantifierList, linguisticValMap);
    qDebug()<<"Liczba podsumowan: "<<summarizationList.size();
    QList<QPair<double, Summarization> > summarizationMeasureList= QualityMeasures::computeTotalQuality(weightsMap,summarizationList, dbRows);
    qDebug()<<"Czas obliczen: "<<timer.elapsed()<<"ms";

    generator.saveSummarizations(summarizationMeasureList, "summarizations.txt");

    return 0;
}
