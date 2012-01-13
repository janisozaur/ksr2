#ifndef LINGUISTICVALUE_H
#define LINGUISTICVALUE_H

#include "fuzzyset.h"
#include "membershipfuncineterface.h"

class LinguisticValue : public FuzzySet
{
private:
    QString label; // etykieta zmiennej lingwistycznej
    int colNum; //numer kolumny w bazie danych
    const MembershipFuncInterface *membershipFunction;

public:
    LinguisticValue();

    double membership(const QVariant &element) const;
    double membership(const QVector<QVariant> &elements) const;
    const MembershipFuncInterface *getMembershipFunction() const;
    void setMembershipFunction(const MembershipFuncInterface *membershipFunction);

    QString getLabel() const;
    void setLabel(const QString label);
    int getColNum() const;
    void setColNum(const int colNum);
};

#endif // LINGUISTICVALUE_H
