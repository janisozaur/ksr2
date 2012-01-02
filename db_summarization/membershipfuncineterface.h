#ifndef MEMBERSHIPFUNCINTERFACE_H
#define MEMBERSHIPFUNCINTERFACE_H

#include <QVariant>

class MembershipFuncInterface
{
public:
    virtual double value(const QVariant) const =0;
	virtual bool init(const QVariant &params) = 0;
};

#endif // MEMBERSHIPFUNCINTERFACE_H
