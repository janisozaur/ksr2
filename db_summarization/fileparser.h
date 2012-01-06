#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QList>
#include <QMap>
#include "linguisticvalue.h"
#include "quantifier.h"

class FileParser
{
public:
    FileParser();

    QList<Quantifier> parseQuantifiers(QString filePath);
    QMap<int, QList<const LinguisticValue *> > parseLinguisticValues(QString filePath);
    QList<QVector<QVariant> > parseDataBase(QString dataFilePath, QString dataDescFilePath);
};

#endif // FILEPARSER_H
