#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QList>
#include "linguisticvalue.h"
#include "quantifier.h"

class FileParser
{
public:
    FileParser();

    QList<Quantifier> parseQuantifiers(QString filePath);
    QList<const LinguisticValue *> parseLinguisticValues(QString filePath);
    QList<QVector<QVariant> > parseDataBase(QString dataFilePath, QString dataDescFilePath);
};

#endif // FILEPARSER_H
