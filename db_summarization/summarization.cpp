#include "summarization.h"

Summarization::Summarization()
{
}

const Quantifier Summarization::getQuantifier() const{
    return quantifiier;
}
void Summarization::setQuantifier(const Quantifier quantifier){
    this->quantifiier=quantifier;
}

const QList<const LinguisticValue *> Summarization::getQualifiers() const{
    return qualifiers;
}
void Summarization::setQualifiers(const QList<const LinguisticValue *> qualifiers){
    this->qualifiers=qualifiers;
}

const QList<const LinguisticValue *> Summarization::getSummarizers() const{
    return summarizers;
}

void Summarization::setSummarizers(const QList<const LinguisticValue *> summarizers){
    this->summarizers=summarizers;
}
