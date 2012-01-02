#ifndef TRAPEZOIDFUNCTION_H
#define TRAPEZOIDFUNCTION_H

#include "membershipfuncineterface.h"
#include <QVariant>

class TrapezoidFunction : public MembershipFuncInterface
{
private:
    double a;
    double b;
    double c;
    double d;

public:
    TrapezoidFunction();
    double value(const QVariant) const;
	bool init(const QVariant &params);

    double getA() const;
    double getB() const;
    double getC() const;
    double getD() const;

    void setA(const double a);
    void setB(const double b);
    void setC(const double c);
    void setD(const double d);
};

#endif // TRAPEZOIDFUNCTION_H
