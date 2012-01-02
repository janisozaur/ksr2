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
	bool init(const QVariant &params);

    QMap<QString, double> getArgumentToValueMap() const;
	void setArgumentToValueMap(QMap<QString, double> const valueMap);
};

#endif // DISCRETEFUNCTION_H
