#ifndef FUZZYSET_H
#define FUZZYSET_H

#include<QVariant>

class FuzzySet
{
private: QList<QVariant> elements;
public:
    virtual double membership(QVariant) const = 0;

    double cardinality();
    QList<QVariant> getElements() const;
    void setElements(const QList<QVariant>&);
};
#endif // FUZZYSET_H
