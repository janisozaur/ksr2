#include "discretefunction.h"

DiscreteFunction::DiscreteFunction()
{
}

double DiscreteFunction::value(const QVariant arg) const{
    return argumentToValueMap.value(arg.toString());
}

QMap<QString, double> DiscreteFunction::getArgumentToValueMap() const{
    return argumentToValueMap;
}

void DiscreteFunction::setArgumentToValueMap(QMap<QString, double> const){
    this->argumentToValueMap = argumentToValueMap;
}
