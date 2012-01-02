#ifndef MEMBERSHIPFUNCTIONFACTORY_H
#define MEMBERSHIPFUNCTIONFACTORY_H

#include <QVariantMap>

#include "membershipfuncineterface.h"

class MembershipFuncFactory
{
public:
	static MembershipFuncInterface const *getFunction(const QVariantMap &map);
};

#endif // MEMBERSHIPFUNCTIONFACTORY_H
