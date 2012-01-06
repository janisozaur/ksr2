#include <QtCore/QCoreApplication>
#include <QFileInfoList>
#include <QStringList>
#include <QDebug>
#include <QList>
#include "trapezoidfunction.h"
#include "quantifier.h"
#include "qualitymeasures.h"
#include "linguisticvalue.h"
#include "fileparser.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString dataFilePath = "database.dat";
    QString dataDescFilePath = "data_description.txt";

    ////////////////////  TEST   /////////////////////////
    FileParser parser = FileParser();

    QList<QVector<QVariant> > dbRows = parser.parseDataBase(dataFilePath, dataDescFilePath);

    QList<Quantifier> quantifierList =  parser.parseQuantifiers("fuzzy_sets_quantifiers.txt");
    qDebug()<<"Liczba kwantyfikatorow: "<< quantifierList.size();

    QList<const LinguisticValue *> summarizers =  parser.parseLinguisticValues("fuzzy_sets_lingValues.txt");
    qDebug()<<"Liczba wartosci lingwistycznych: "<< summarizers.size();

//    TrapezoidFunction moreMembership = TrapezoidFunction();
//    moreMembership.setA(0.5);
//    moreMembership.setB(0.7);
//	moreMembership.setB(1);
//	moreMembership.setB(1);
//    Quantifier moreQuantifier = Quantifier();
//    moreQuantifier.setMembershipFunction(&moreMembership);
//    moreQuantifier.setLabel("wiekszosc");
//    moreQuantifier.setRelative(true);

//    TrapezoidFunction lowRainFunction = TrapezoidFunction();
//    lowRainFunction.setA(0);
//    lowRainFunction.setB(0);
//    lowRainFunction.setC(20);
//    lowRainFunction.setD(50);
//    LinguisticValue lowRainSet = LinguisticValue();
//    lowRainSet.setColNum(19);
//    lowRainSet.setLabel("niskie opady");
//    lowRainSet.setMembershipFunction(&lowRainFunction);

//    QList<const LinguisticValue *> summarizers;
//	summarizers.append(&lowRainSet);

    QList<const LinguisticValue *> qualifiers = QList< const LinguisticValue*>();

    qDebug()<<"T1: "<<QualityMeasures::computeT1(quantifierList.at(0), qualifiers, summarizers, dbRows);
    qDebug()<<"T2: "<<QualityMeasures::computeT2T9(summarizers, dbRows);
    qDebug()<<"T3: "<<QualityMeasures::computeT3(qualifiers, summarizers, dbRows);
    qDebug()<<"T4: "<<QualityMeasures::computeT4(qualifiers, summarizers, dbRows);
    qDebug()<<"T5: "<<QualityMeasures::computeT5T11(summarizers.size());
    qDebug()<<"T6: "<<QualityMeasures::computeT6(quantifierList.at(0), dbRows.size());
    qDebug()<<"T7: "<<QualityMeasures::computeT7(quantifierList.at(0), dbRows.size());
    qDebug()<<"T8: "<<QualityMeasures::computeT8T10(summarizers, dbRows);
    qDebug()<<"T9: "<<QualityMeasures::computeT2T9(qualifiers, dbRows);
    qDebug()<<"T10: "<<QualityMeasures::computeT8T10(qualifiers, dbRows);
    qDebug()<<"T11: "<<QualityMeasures::computeT5T11(qualifiers.size());

    QList<QualityMeasures::Measures> measures;
    measures << QualityMeasures::T1	<< QualityMeasures::T2 << QualityMeasures::T3
             << QualityMeasures::T4 << QualityMeasures::T5 << QualityMeasures::T6
             << QualityMeasures::T7 << QualityMeasures::T8 << QualityMeasures::T9
             << QualityMeasures::T10 << QualityMeasures::T11;
    QList<double> ts = QualityMeasures::computeT(measures, quantifierList.at(0),
                                                 qualifiers, summarizers, dbRows);
    for (int i = 0; i < measures.size(); i++) {
        const QString tIdStr = QString::number(int(measures.at(i)));
        const QString tValStr = QString::number(ts.at(i));
        qDebug() << QString("T%1: %2").arg(tIdStr, tValStr);
    }

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

    qDebug()<<"Total: "<<QualityMeasures::computeTotalQuality(weightsMap, quantifierList.at(0), qualifiers, summarizers, dbRows);
    return 0;
}
