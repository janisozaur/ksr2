#ifndef SUMMARIZATIONGENERATOR_H
#define SUMMARIZATIONGENERATOR_H

#include "summarization.h"
#include <QPair>
#include <QList>
#include <QMap>

class SummarizationGenerator
{
public:
    SummarizationGenerator();

    QList<Summarization> generateAll(QList<Quantifier> &quantifierList, QMap<int, QList<const LinguisticValue *> > &linguisticValMap);
    void saveSummarizations(QList<QPair<double, Summarization> > summarizationMeasureList, QString filePath);
};

#endif // SUMMARIZATIONGENERATOR_H
