#include "trapezoidfunction.h"

#include <QDebug>

TrapezoidFunction::TrapezoidFunction()
{
}

bool TrapezoidFunction::init(const QVariant &params)
{
	const QList<QVariant> paramList = params.toList();
	if (paramList.size() != 4) {
		return false;
	}
	bool ok;
	int i = 0;
	a = paramList.at(i).toDouble(&ok);
	if (!ok) {
		qCritical() << "failed to parse" << i << ":"
					<< paramList.at(i).toString() << "as double";
		return false;
	}
	i = 1;
	b = paramList.at(i).toDouble(&ok);
	if (!ok) {
		qCritical() << "failed to parse" << i << ":"
					<< paramList.at(i).toString() << "as double";
		return false;
	}
	i = 2;
	c = paramList.at(i).toDouble(&ok);
	if (!ok) {
		qCritical() << "failed to parse" << i << ":"
					<< paramList.at(i).toString() << "as double";
		return false;
	}
	i = 3;
	d = paramList.at(i).toDouble(&ok);
	if (!ok) {
		qCritical() << "failed to parse" << i << ":"
					<< paramList.at(i).toString() << "as double";
		return false;
	}
	return true;
}

double TrapezoidFunction::value(const QVariant arg) const{
    double x = arg.toDouble();

    if (x >= b && x <= c) {
        return 1;
    } else if (x > a && x < b) {
        return 1.0 / (b - a) * x + 1.0 - (1.0 / (b - a)) * b;
    } else if (x > c && x < d) {
        return 1.0 / (c - d) * x + 1.0 - (1.0 / (c - d)) * c;
    } else{
        return 0;
    }
}

double TrapezoidFunction::getA() const{
    return a;
}
double TrapezoidFunction::getB() const{
    return b;
}
double TrapezoidFunction::getC() const{
    return c;
}
double TrapezoidFunction::getD() const{
    return d;
}

void TrapezoidFunction::setA(const double a){
    this->a = a;
}
void TrapezoidFunction::setB(const double b){
    this->b = b;
}
void TrapezoidFunction::setC(const double c){
    this->c = c;
}
void TrapezoidFunction::setD(const double d){
    this->d = d;
}
