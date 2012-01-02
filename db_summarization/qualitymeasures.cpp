#include "qualitymeasures.h"
#include "intersection.h"
#include "support.h"
#include <QList>
#include <QVector>
#include <QVariant>
#include <cmath>


double  QualityMeasures::computeT1(Quantifier quantifier, QList<BasicFuzzySet> qualifiers, QList<BasicFuzzySet> summarizers, QList<QVector<QVariant> > dbRows){
    //int dbSize = summarizers.at(0).getElements().size();
    BasicFuzzySet basicFuzzySet = summarizers.value(0);
    FuzzySet *summarizerIntersection = &basicFuzzySet;
    FuzzySet *qualifierIntersection;
    Intersection *temp;
    for(int i = 1; i<summarizers.size(); i++){
        temp = new Intersection();
        temp->setFuzzySet1(summarizerIntersection);
        basicFuzzySet = summarizers.value(i);
        temp->setFuzzySet2(&basicFuzzySet);
        summarizerIntersection = temp;
    }
    if(!qualifiers.empty()){
        basicFuzzySet = qualifiers.value(0);
        qualifierIntersection = &basicFuzzySet;
        for(int i = 1; i<qualifiers.size(); i++){
            temp = new Intersection();
            temp->setFuzzySet1(qualifierIntersection);
            basicFuzzySet = qualifiers.value(i);
            temp->setFuzzySet2(&basicFuzzySet);
            summarizerIntersection = temp;
        }
    }
    int m=1;
    if (quantifier.isRealtive()){
        m=dbRows.size();
    }

    if(qualifiers.empty()){
        double sum = 0;
        for(int i=0; i<dbRows.size(); i++){
            sum += summarizerIntersection->membership(dbRows.at(i));
        }
        return quantifier.membership(sum/m);
    }else{
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
    }
}

double  QualityMeasures::computeT2T9(QList<BasicFuzzySet> fuzzySets, QList<QVector<QVariant> > dbRows){
    if(fuzzySets.empty()){
        return 1;
    }

    BasicFuzzySet basicFuzzySet;
    double result = 1;
    for(int i =0; i<fuzzySets.size(); i++){
        Support support = Support();
        basicFuzzySet = fuzzySets.value(i);
        support.setFuzzySet(&basicFuzzySet);
        result*=support.cardinality(dbRows)/dbRows.size();
    }
    result = pow(result, 1.0/fuzzySets.size());
    return 1.0 - result;
}

double  QualityMeasures::computeT3(QList<BasicFuzzySet> qualifiers, QList<BasicFuzzySet> summarizers, QList<QVector<QVariant> > dbRows){

    BasicFuzzySet basicFuzzySet = summarizers.value(0);
    FuzzySet *summarizerIntersection = &basicFuzzySet;
    FuzzySet *qualifierIntersection;
    Intersection *temp;
    for(int i = 1; i<summarizers.size(); i++){
        temp = new Intersection();
        temp->setFuzzySet1(summarizerIntersection);
        basicFuzzySet = summarizers.value(i);
        temp->setFuzzySet2(&basicFuzzySet);
        summarizerIntersection = temp;
    }
    if(!qualifiers.empty()){
        basicFuzzySet = qualifiers.value(0);
        qualifierIntersection = &basicFuzzySet;
        for(int i = 1; i<qualifiers.size(); i++){
            temp = new Intersection();
            temp->setFuzzySet1(qualifierIntersection);
            basicFuzzySet = qualifiers.value(i);
            temp->setFuzzySet2(&basicFuzzySet);
            summarizerIntersection = temp;
        }
    }

    if(qualifiers.empty()){
        Support support = Support();
        support.setFuzzySet(summarizerIntersection);
        return support.cardinality(dbRows)/dbRows.size();
    } else{
        Intersection intersection = Intersection();
        intersection.setFuzzySet1(summarizerIntersection);
        intersection.setFuzzySet2(qualifierIntersection);

        Support support1 = Support();
        Support support2 = Support();
        support1.setFuzzySet(summarizerIntersection);
        support2.setFuzzySet(qualifierIntersection);

        return support1.cardinality(dbRows)/support2.cardinality(dbRows);
    }
}


double  QualityMeasures::computeT4(QList<BasicFuzzySet> qualifiers, QList<BasicFuzzySet> summarizers, QList<QVector<QVariant> > dbRows){
    if(summarizers.empty()){
        return 1;
    }

    BasicFuzzySet basicFuzzySet;
    double result = 1;
    for(int i =0; i<summarizers.size(); i++){
        Support support = Support();
        basicFuzzySet = summarizers.value(i);
        support.setFuzzySet(&basicFuzzySet);
        result*=support.cardinality(dbRows)/dbRows.size();
    }
    result = result/summarizers.size();
    return result - QualityMeasures::computeT3(qualifiers, summarizers, dbRows);
}

double  QualityMeasures::computeT5T11(int summarizersNum){
    if(summarizersNum==0){
        return 1;
    }
    return 2.0*pow(0.5, summarizersNum);
}

double  QualityMeasures::computeT6(Quantifier quantifier, int dbRowsSize){
    QList<QVariant> quantityList = QList<QVariant>();
    if(quantifier.isRealtive()){
        for(int i =0; i<dbRowsSize; i++){
            QVariant qVariant = QVariant((double)i * 1.0 /dbRowsSize);
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


double  QualityMeasures::computeT7(Quantifier quantifier, int dbRowsSize){
    QList<QVariant> quantityList = QList<QVariant>();
    if(quantifier.isRealtive()){
        for(int i =0; i<dbRowsSize; i++){
            QVariant qVariant = QVariant((double)i * 1.0 /dbRowsSize);
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

double  QualityMeasures::computeT8T10(QList<BasicFuzzySet> fuzzySets, QList<QVector<QVariant> > dbRows){
    if(fuzzySets.empty()){
        return 1;
    }

    BasicFuzzySet basicFuzzySet;
    double result = 1;
    for(int i =0; i<fuzzySets.size(); i++){
        Support support = Support();
        basicFuzzySet = fuzzySets.value(i);
        support.setFuzzySet(&basicFuzzySet);
        result*=support.cardinality(dbRows)/dbRows.size();
    }
    result = pow(result, 1.0/fuzzySets.size());
    return 1.0 - result;
}
