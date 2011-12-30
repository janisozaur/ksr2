#ifndef DISCRETEFUNCTION_H
#define DISCRETEFUNCTION_H

#include "membershipfuncineterface.h"
#include <QVariant>

class DiscreteFunction : public MembershipFuncInterface
{
private:
    QMap<QString, double> argumentToValueMap;

public:
    DiscreteFunction();
    double value(const QVariant) const;

    QMap<QString, double> getArgumentToValueMap() const;
    void setArgumentToValueMap(QMap<QString, double> const);
};

#endif // DISCRETEFUNCTION_H
