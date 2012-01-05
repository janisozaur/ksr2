#ifndef LINGUISTICVALUE_H
#define LINGUISTICVALUE_H

#include "basicfuzzyset.h"

class LinguisticValue : public BasicFuzzySet
{
private:
    QString label; // etykieta zmiennej lingwistycznej
    int colNum; //numer kolumny w bazie danych

public:
    LinguisticValue();
    const QString getLabel() const;
    void setLabel(const QString label);
    const int getColNum() const;
    void setColNum(const int label);
};

#endif // LINGUISTICVALUE_H
