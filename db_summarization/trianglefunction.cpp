#include "trianglefunction.h"

#include <QDebug>

TriangleFunction::TriangleFunction()
{
}

bool TriangleFunction::init(const QVariant &params)
{
	const QList<QVariant> paramList = params.toList();
	if (paramList.size() != 3) {
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
	return true;
}

double TriangleFunction::value(const QVariant &arg) const{
    double x = arg.toDouble();

    if (x == b) {
        return 1;
    } else if (x > a && x < b) {
        return 1.0 / (b - a) * x + 1.0 - (1.0 / (b - a)) * b;
    } else if (x > b && x < c) {
        return 1.0 / (b - c) * x + 1.0 - (1.0 / (b - c)) * b;
    } else{
        return 0;
    }
}

double TriangleFunction::getA() const{
    return a;
}

double TriangleFunction::getB() const{
    return b;
}
double TriangleFunction::getC() const{
    return c;
}

void TriangleFunction::setA(const double a){
    this->a = a;
}
void TriangleFunction::setB(const double b){
    this->b = b;
}
void TriangleFunction::setC(const double c){
    this->c = c;
}
