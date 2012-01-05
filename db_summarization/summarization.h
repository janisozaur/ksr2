#ifndef SUMMARIZATION_H
#define SUMMARIZATION_H

#include "quantifier.h"
#include "linguisticvalue.h"

class Summarization
{

private:
    Quantifier quantifiier;
    QList<const LinguisticValue *> qualifiers;
    QList<const LinguisticValue *> summarizers;

public:
    Summarization();

    const Quantifier getQuantifier() const;
    void setQuantifier(const Quantifier quantifier);

    const QList<const LinguisticValue *> getQualifiers() const;
    void setQualifiers(const QList<const LinguisticValue *> qualifiers);

    const QList<const LinguisticValue *> getSummarizers() const;
    void setSummarizers(const QList<const LinguisticValue *> summarizers);
};

#endif // SUMMARIZATION_H
