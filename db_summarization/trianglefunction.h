#ifndef TRIANGLEFUNCTION_H
#define TRIANGLEFUNCTION_H

#include "membershipfuncineterface.h"
#include <QVariant>

class TriangleFunction : public MembershipFuncInterface
{
private:
    double a;
    double b;
    double c;

public:
    TriangleFunction();
	double value(const QVariant &arg) const;
	bool init(const QVariant &params);

    double getA() const;
    double getB() const;
    double getC() const;

    void setA(const double a);
    void setB(const double b);
    void setC(const double c);
};

#endif // TRIANGLEFUNCTION_H
