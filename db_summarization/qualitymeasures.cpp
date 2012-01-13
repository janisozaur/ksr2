#include "qualitymeasures.h"
#include "intersection.h"
#include "support.h"
#include "linguisticvalue.h"

#include <QList>
#include <QMap>
#include <QVector>
#include <QVariant>
#include <cmath>
#include <QDebug>

// stopien prawdziwosci
double QualityMeasures::computeT1(const Quantifier &quantifier, const QList<const LinguisticValue *> &qualifiers, const QList<const LinguisticValue *> &summarizers, const QList<QVector<QVariant> > &dbRows) {
    //int dbSize = summarizers.at(0).getElements().size();
    const FuzzySet *summarizerIntersection = summarizers.at(0);
    const FuzzySet *qualifierIntersection;
    Intersection *temp;
    for(int i = 1; i<summarizers.size(); i++){

        temp = new Intersection();
        temp->setFuzzySet1(summarizerIntersection);
        temp->setFuzzySet2(summarizers.at(i));
        summarizerIntersection = temp;
    }
    int m=1;
    if (quantifier.isRealtive()){
        m=dbRows.size();
    }
    if(!qualifiers.empty()){
        qualifierIntersection = qualifiers.at(0);
        for(int i = 1; i<qualifiers.size(); i++){
            temp = new Intersection();
            temp->setFuzzySet1(qualifierIntersection);
            temp->setFuzzySet2(qualifiers.at(i));
            qualifierIntersection = temp;
        }
        Intersection *intersection = new Intersection();
        intersection->setFuzzySet1(summarizerIntersection);
        intersection->setFuzzySet2(qualifierIntersection);

        double sum1=0;
        double sum2=0;

        for(int i=0; i<dbRows.size(); i++){
            sum1 += intersection->membership(dbRows.at(i));
            sum2 += qualifierIntersection->membership(dbRows.at(i));
        }
        if(sum2 == 0){
            return quantifier.membership(0);
        } else{
            return quantifier.membership((sum1/sum2)/m);
        }
    } else {
        double sum = 0;
        for(int i=0; i<dbRows.size(); i++){
            //qDebug()<<i;
            sum += summarizerIntersection->membership(dbRows.at(i));
        }
        return quantifier.membership(sum/m);
    }
}

// stopien nieprecyzyjnosci (sumaryzatora lub kwalifikatora)
double QualityMeasures::computeT2T9(const QList<const LinguisticValue *> &fuzzySets, const QList<QVector<QVariant> > &dbRows){
    if(fuzzySets.empty()){
        return 1;
    }

    double result = 1;
    Support support;
    for(int i =0; i<fuzzySets.size(); i++){
        support.setFuzzySet(fuzzySets[i]);
        result*=support.cardinality(dbRows)/dbRows.size();
    }
    result = pow(result, 1.0/fuzzySets.size());
    return 1.0 - result;
}

// stopien pokrycia
double QualityMeasures::computeT3(const QList<const LinguisticValue *> &qualifiers, const QList<const LinguisticValue *> &summarizers, const QList<QVector<QVariant> > &dbRows)
{
    const FuzzySet *summarizerIntersection = summarizers.at(0);
    const FuzzySet *qualifierIntersection = nullptr;
    Intersection *temp;
    for(int i = 1; i<summarizers.size(); i++){
        temp = new Intersection();
        temp->setFuzzySet1(summarizerIntersection);
        temp->setFuzzySet2(summarizers.at(i));
        summarizerIntersection = temp;
    }
    double result;
    if(!qualifiers.empty()) {
        qualifierIntersection = qualifiers.at(0);
        for(int i = 1; i<qualifiers.size(); i++){
            temp = new Intersection();
            temp->setFuzzySet1(qualifierIntersection);
            temp->setFuzzySet2(qualifiers.at(i));
            qualifierIntersection = temp;
        }
        Intersection intersection;
        intersection.setFuzzySet1(summarizerIntersection);
        intersection.setFuzzySet2(qualifierIntersection);

        Support support1;
        Support support2;
        support1.setFuzzySet(&intersection);
        support2.setFuzzySet(qualifierIntersection);
        double support2Cardinality = support2.cardinality(dbRows);
        if(support2Cardinality == 0){
            result = 0;
        } else {
            result =  support1.cardinality(dbRows)/support2Cardinality;
        }
    } else {
        Support support;
        support.setFuzzySet(summarizerIntersection);
        result = support.cardinality(dbRows)/dbRows.size();
    }
    const Intersection *i;
    while ((i = dynamic_cast<const Intersection *>(summarizerIntersection)) != nullptr) {
        summarizerIntersection = i->getFuzzySet1();
        delete i;
    }
    while ((i = dynamic_cast<const Intersection *>(qualifierIntersection)) != nullptr) {
        qualifierIntersection = i->getFuzzySet1();
        delete i;
    }
    return result;
}

// miara trafnosci
double QualityMeasures::computeT4(const QList<const LinguisticValue *> &qualifiers, const QList<const LinguisticValue *> &summarizers, const QList<QVector<QVariant> > &dbRows){
    if(summarizers.empty()){
        return 1;
    }

    double result = 1;
    for(int i =0; i<summarizers.size(); i++){
        Support support = Support();
        support.setFuzzySet(summarizers[i]);
        result*=support.cardinality(dbRows)/dbRows.size();
    }
    result = result/summarizers.size();
    return fabs(result - QualityMeasures::computeT3(qualifiers, summarizers, dbRows));
}

// dlugosc podsumowania (sumaryzatora lub kwalifikatora)
double QualityMeasures::computeT5T11(const int &summarizersNum){
    if(summarizersNum==0){
        return 1;
    }
    return 2.0*pow(0.5, summarizersNum);
}

// stopien nieprecyzyjnosci kwantyfikatora
double QualityMeasures::computeT6(const Quantifier &quantifier, const int &dbRowsSize){
    QList<QVariant> quantityList;
    quantityList.reserve(dbRowsSize);
    if(quantifier.isRealtive()){
        for(int i =0; i<dbRowsSize; i++){
            QVariant qVariant = QVariant((double)i / qreal(dbRowsSize));
            quantityList.append(qVariant);
        }
    } else{
        for(int i =0; i<dbRowsSize; i++){
            QVariant qVariant = QVariant((double)i);
            quantityList.append(qVariant);
        }
    }

    Support support = Support();
    support.setFuzzySet(&quantifier);

    double result = support.cardinality(quantityList)/dbRowsSize;

    return 1 - result;
}


// stopien kardynalnosci kwantyfikatora
double QualityMeasures::computeT7(const Quantifier &quantifier, const int &dbRowsSize){
    QList<QVariant> quantityList;
    quantityList.reserve(dbRowsSize);
    if(quantifier.isRealtive()){
        for(int i =0; i<dbRowsSize; i++){
            QVariant qVariant = QVariant((double)i / qreal(dbRowsSize));
            quantityList.append(qVariant);
        }
    } else{
        for(int i =0; i<dbRowsSize; i++){
            QVariant qVariant = QVariant((double)i);
            quantityList.append(qVariant);
        }
    }

    return quantifier.cardinality(quantityList)/quantityList.size();
}

// stopien kardynalnosci sumaryzatora lub kwalifikatora
double  QualityMeasures::computeT8T10(QList<const LinguisticValue *> fuzzySets, const QList<QVector<QVariant> > &dbRows){
    if(fuzzySets.empty()){
        return 1;
    }

    double result = 1;
    for(int i =0; i<fuzzySets.size(); i++){
        result*=fuzzySets[i]->cardinality(dbRows)/dbRows.size();
    }
    result = pow(result, 1.0/fuzzySets.size());
    return 1.0 - result;
}

QList<double> QualityMeasures::computeT(const QList<Measures> &measures,
                                        const Quantifier &quantifier,
                                        const QList<const LinguisticValue *> &qualifiers,
                                        const QList<const LinguisticValue *> &summarizers,
                                        const QList<QVector<QVariant> > &dbRows)
{
    QList<double> result;
    result.reserve(measures.size());
    for (int i = 0; i < measures.size(); i++) {
        double t;
        switch (measures.at(i)) {
            case T1:
                t = computeT1(quantifier, qualifiers, summarizers, dbRows);
                break;
            case T2:
                t = computeT2T9(summarizers, dbRows);
                break;
            case T3:
                t = computeT3(qualifiers, summarizers, dbRows);
                break;
            case T4:
                t = computeT4(qualifiers, summarizers, dbRows);
                break;
            case T5:
                t = computeT5T11(summarizers.size());
                break;
            case T6:
                t = computeT6(quantifier, dbRows.size());
                break;
            case T7:
                t = computeT7(quantifier, dbRows.size());
                break;
            case T8:
                t = computeT8T10(summarizers, dbRows);
                break;
            case T9:
                t = computeT2T9(qualifiers, dbRows);
                break;
            case T10:
                t = computeT8T10(qualifiers, dbRows);
                break;
            case T11:
                t = computeT5T11(qualifiers.size());
                break;
        }
        result.append(t);
    }
    return result;
}

// miara calkowita - srednia wazona miar
double  QualityMeasures::computeTotalQuality(const QMap<QString, double> &weightsMap, const Quantifier &quantifier, const QList<const LinguisticValue *> &qualifiers, const QList<const LinguisticValue *> &summarizers, const QList<QVector<QVariant> > &dbRows){
    double weightsSum = 0;
    double measuresSum = 0;
    double weight;
    double measure;

    weight = weightsMap.value("T1");
    if(weight > 0 ){
        measure = QualityMeasures::computeT1(quantifier, qualifiers, summarizers, dbRows);
        if (measure >1){
            qDebug()<<"T1 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T2");
    if(weight > 0 ){
        measure = QualityMeasures::computeT2T9(summarizers, dbRows);
        if (measure >1){
            qDebug()<<"T2 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T3");
    if(weight > 0 ){
        measure = QualityMeasures::computeT3(qualifiers, summarizers, dbRows);
        if (measure >1){
            qDebug()<<"T3 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T4");
    if(weight > 0 ){
        measure = QualityMeasures::computeT4(qualifiers, summarizers, dbRows);
        if (measure >1){
            qDebug()<<"T4 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T5");
    if(weight > 0 ){
        measure = QualityMeasures::computeT5T11(summarizers.size());
        if (measure >1){
            qDebug()<<"T5 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T6");
    if(weight > 0 ){
        measure = QualityMeasures::computeT6(quantifier, dbRows.size());
        if (measure >1){
            qDebug()<<"T6 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T7");
    if(weight > 0 ){
        measure = QualityMeasures::computeT7(quantifier, dbRows.size());
        if (measure >1){
            qDebug()<<"T7 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T8");
    if(weight > 0 ){
        measure = QualityMeasures::computeT8T10(summarizers, dbRows);
        if (measure >1){
            qDebug()<<"T8 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T9");
    if(weight > 0 ){
        measure = QualityMeasures::computeT2T9(qualifiers, dbRows);
        if (measure >1){
            qDebug()<<"T9 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T10");
    if(weight > 0 ){
        measure = QualityMeasures::computeT8T10(qualifiers, dbRows);
        if (measure >1){
            qDebug()<<"T10 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    weight = weightsMap.value("T11");
    if(weight > 0 ){
        measure = QualityMeasures::computeT5T11(qualifiers.size());
        if (measure >1){
            qDebug()<<"T11 "<<measure ;
        }
        measuresSum += measure;
        weightsSum += weight;
    }

    if(weightsSum == 0){
        return 0;
    } else{
        return measuresSum/weightsSum;
    }
}


double QualityMeasures::computeT1(const Summarization &summarization,const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT1(summarization.getQuantifier(), summarization.getQualifiers(), summarization.getSummarizers(), dbRows);
}

double QualityMeasures::computeT2(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT2T9(summarization.getSummarizers(), dbRows);
}

double QualityMeasures::computeT3(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT3(summarization.getQualifiers(), summarization.getSummarizers(), dbRows);
}

double QualityMeasures::computeT4(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT4(summarization.getQualifiers(), summarization.getSummarizers(), dbRows);
}

double QualityMeasures::computeT5(const Summarization &summarization){
    return QualityMeasures::computeT5T11(summarization.getSummarizers().size());
}

double QualityMeasures::computeT6(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT6(summarization.getQuantifier(), dbRows.size());
}

double QualityMeasures::computeT7(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT7(summarization.getQuantifier(), dbRows.size());
}

double QualityMeasures::computeT8(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT8T10(summarization.getSummarizers(), dbRows);
}

double QualityMeasures::computeT9(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT2T9(summarization.getQualifiers(), dbRows);
}

double QualityMeasures::computeT10(const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeT8T10(summarization.getSummarizers(), dbRows);
}

double QualityMeasures::computeT11(const Summarization &summarization){
    return QualityMeasures::computeT5T11(summarization.getQualifiers().size());
}

double QualityMeasures::computeTotalQuality(const QMap<QString, double> &weightsMap, const Summarization &summarization, const QList<QVector<QVariant> > &dbRows){
    return QualityMeasures::computeTotalQuality(weightsMap, summarization.getQuantifier(), summarization.getQualifiers(), summarization.getSummarizers(), dbRows);
}

bool QualityMeasures::pairGreaterThan(const QPair<double, Summarization> &p1, const QPair<double, Summarization> &p2)
 {
     return p1.first > p2.first;
 }

QList<QPair<double, Summarization> > QualityMeasures::computeTotalQuality(const QMap<QString, double> &weightsMap, const QList<Summarization> &summarizationList, const QList<QVector<QVariant> > &dbRows){
    QList<QPair<double, Summarization> > result = QList<QPair<double, Summarization> >();

    #pragma omp parallel for
    for(int i = 0; i<summarizationList.size(); i++){
        Summarization summarization = summarizationList.at(i);
        double quality = QualityMeasures::computeTotalQuality(weightsMap, summarization.getQuantifier(), summarization.getQualifiers(), summarization.getSummarizers(), dbRows);
        result.append(QPair<double, Summarization>(quality,summarization));
    }
    qSort(result.begin(), result.end(), pairGreaterThan); //sortowanie w kolejnosci malejacej
    return result;
}
