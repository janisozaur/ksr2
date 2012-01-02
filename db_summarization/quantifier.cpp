#include "quantifier.h"

Quantifier::Quantifier()
{
}

bool Quantifier::isRealtive() const{
    return relative;
}

void Quantifier::setRelative(const bool relative){
    this->relative = relative;
}
