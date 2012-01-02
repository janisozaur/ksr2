#include "discretefunction.h"

#include <QDebug>

DiscreteFunction::DiscreteFunction()
{
}

bool DiscreteFunction::init(const QVariant &params)
{
	const QList<QVariant> paramList = params.toList();
	if (paramList.size() % 2 == 1) {
		return false;
	}
	QMap<QString, double> values;
	bool ok;
	for (int i = 0; i < paramList.size(); i += 2) {
		const QString label = paramList.at(i).toString();
		if (values.contains(label)) {
			qCritical() << "duplicate label detected:" << label;
			return false;
		}
		const double value = paramList.at(i + 1).toDouble(&ok);
		if (!ok) {
			qCritical() << "failed to parse" << i + 1 << ":"
						<< paramList.at(i + 1).toString() << "as double";
			return false;
		}
		values[label] = value;
	}
	argumentToValueMap = values;
	return true;
}

double DiscreteFunction::value(const QVariant arg) const{
    return argumentToValueMap.value(arg.toString());
}

QMap<QString, double> DiscreteFunction::getArgumentToValueMap() const{
    return argumentToValueMap;
}

void DiscreteFunction::setArgumentToValueMap(const QMap<QString, double> valueMap){
	this->argumentToValueMap = valueMap;
}
