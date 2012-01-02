#include <QtCore/QCoreApplication>
#include <QFileInfoList>
#include <QStringList>
#include <QDebug>
#include "trapezoidfunction.h"
#include "quantifier.h"
#include "qualitymeasures.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString dataFileName = "database.dat";
    QString dataDescFileName = "data_description.txt";

    QVector<QStringList> data;
    {
        QFile databaseFile(dataFileName);
        if (!databaseFile.open(QIODevice::ReadOnly)) {
            qCritical() << "failed to open database file" << dataFileName;
            return -2;
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
        QFile dataDescFile(dataDescFileName);
        if (!dataDescFile.open(QIODevice::ReadOnly)) {
            qCritical() << "failed to open data description file" << dataDescFileName;
            return -2;
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


    /////////////////////////////////////////////
    TrapezoidFunction moreMembership = TrapezoidFunction();
    moreMembership.setA(0.5);
    moreMembership.setB(0.7);
	moreMembership.setB(1);
	moreMembership.setB(1);
    Quantifier moreQuantifier = Quantifier();
    moreQuantifier.setMembershipFunction(&moreMembership);
    moreQuantifier.setRelative(true);

    TrapezoidFunction lowRainFunction = TrapezoidFunction();
    lowRainFunction.setA(0);
    lowRainFunction.setB(0);
    lowRainFunction.setC(20);
    lowRainFunction.setD(50);
    BasicFuzzySet lowRainSet = BasicFuzzySet();
    lowRainSet.setColNum(19);
    lowRainSet.setMembershipFunction(&lowRainFunction);

	QList<const BasicFuzzySet *> summarizers;
	summarizers.append(&lowRainSet);

	qDebug()<<"T1: "<<QualityMeasures::computeT1(moreQuantifier, QList<const BasicFuzzySet *>(), summarizers, dbRows);
    return 0;
}
