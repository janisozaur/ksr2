#ifndef FUZZYSETTYPE2_H
#define FUZZYSETTYPE2_H

#include "fuzzyset.h"

#include <QScriptValue>
#include <QScriptProgram>

class FuzzySetType2 : public FuzzySet
{
public:
    FuzzySetType2(const QScriptValueList &params);
    double membership(const QVariant &element) const;
    double membership(const QVector<QVariant> &elements) const;

private:
    int mId;
};

#endif // FUZZYSETTYPE2_H
