#include "trianglefunction.h"
#include <QVariant>

TriangleFunction::TriangleFunction()
{
}

double TriangleFunction::value(const QVariant arg) const{
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
