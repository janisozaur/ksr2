#include "MembershipFunctionFactory.h"
#include "trapezoidfunction.h"
#include "trianglefunction.h"
#include "discretefunction.h"

#include <QDebug>

const MembershipFuncInterface *MembershipFuncFactory::getFunction(const QVariantMap &map)
{
	MembershipFuncInterface *result = nullptr;
	const QString type = map["type"].toString().toLower();
	if (type == "trapezoid") {
		result = new TrapezoidFunction();
	} else if (type == "triangle") {
		result = new TriangleFunction();
	} else if (type == "discrete") {
		result = new DiscreteFunction();
	} else {
		qCritical() << "failed to create function" << type;
	}
	if (result != nullptr) {
		const QVariant params = map["params"];
		const bool initOk = result->init(params);
		if (!initOk) {
			delete result;
			result = nullptr;
			qCritical() << "failed to properly init function" << type
						<< "with params" << params.toString();
		}
	}
	return result;
}
