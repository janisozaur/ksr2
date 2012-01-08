#include "fileparser.h"
#include "quantifier.h"
#include "MembershipFunctionFactory.h"

#include <QStringList>
#include <QVariantMap>
#include <QVariantList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

FileParser::FileParser()
{
}

QList<Quantifier> FileParser::parseQuantifiers(QString filePath){
    QList<Quantifier> list = QList<Quantifier>();
    MembershipFuncFactory factory = MembershipFuncFactory();

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(!line.startsWith("#")){
            QStringList stringList = line.split(":");

            Quantifier quantifier = Quantifier();
            quantifier.setLabel(stringList.at(0));
            if(stringList.at(1).compare("RELATIVE", Qt::CaseInsensitive) == 0){
                quantifier.setRelative(true);
            } else{
                quantifier.setRelative(false);
            }

            QVariantMap variantMap = QVariantMap();
            variantMap.insert("type", stringList.at(2));
            QVariantList variantList = QVariantList();
            for(int i =3; i< stringList.size(); i++){
                variantList.append(stringList.at(i));
            }
            variantMap.insert("params", variantList);

            quantifier.setMembershipFunction(factory.getFunction(variantMap));
            list.append(quantifier);
        }
    }

    return list;
}

// zwraca mape numerow kolumn i listy przypisanych do nich wartosci lingwistycznych
QMap<int, QList<const LinguisticValue *> > FileParser::parseLinguisticValues(QString filePath){
    QMap<int, QList<const LinguisticValue *> >map = QMap<int, QList<const LinguisticValue *> >();
    MembershipFuncFactory factory = MembershipFuncFactory();

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(!line.startsWith("#")){
            QStringList stringList = line.split(":");

            LinguisticValue *linguisticValue = new LinguisticValue();
            linguisticValue->setLabel(stringList.at(0));
            linguisticValue->setColNum(stringList.at(1).toInt());
            QVariantMap variantMap = QVariantMap();
            variantMap.insert("type", stringList.at(2));
            QVariantList variantList = QVariantList();
            for(int i =3; i< stringList.size(); i++){
                variantList.append(stringList.at(i));
            }
            variantMap.insert("params", variantList);

            linguisticValue->setMembershipFunction(factory.getFunction(variantMap));
            map[stringList.at(1).toInt()].append(linguisticValue);
        }
    }

    return map;
}


QList<QVector<QVariant> > FileParser::parseDataBase(QString dataFilePath, QString dataDescFilePath){
    QVector<QStringList> data;
    {
        QFile databaseFile(dataFilePath);
        if (!databaseFile.open(QIODevice::ReadOnly)) {
            qCritical() << "failed to open database file" << dataFilePath;
            return QList<QVector<QVariant> >();
        }
        while (!databaseFile.atEnd() && data.size()<10000) {
            data << QString(databaseFile.readLine()).trimmed().split(QRegExp("\\s"), QString::SkipEmptyParts);
            if(data.at(data.size()-1).size()<30){
                qDebug()<<"fail "<<data.size();
            }
        }
        databaseFile.close();
    }

    QVector<QString> dataDesc;
    {
        QFile dataDescFile(dataDescFilePath);
        if (!dataDescFile.open(QIODevice::ReadOnly)) {
            qCritical() << "failed to open data description file" << dataDescFilePath;
            return QList<QVector<QVariant> >();
        }
        QStringList splittedLine;
        QTextStream in(&dataDescFile);
        while (!in.atEnd()) {
            splittedLine = in.readLine().split(QString(":"));
            dataDesc << splittedLine.at(0);
        }
    }


    QList<QVector<QVariant> > dbRows;
    for (int i=0; i<data.size(); i++) {
        const int size = data.at(0).size();
        if (data.at(i).size() == size) {
            QVector<QVariant> dbRow;
            dbRow.reserve(size);
            for (int j = 0; j < size; j++) {
                QVariant v;
                if (dataDesc.at(j) == "N") {
                    v = QVariant(data.at(i).at(j).toDouble());
                }else{
                    v = QVariant(data.at(i).at(j));
                }
                dbRow.append(v);
            }
            dbRows.append(dbRow);
        }
    }

    return dbRows;
}
