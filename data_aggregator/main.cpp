#include <QtCore/QCoreApplication>
#include <QFileInfoList>
#include <QStringList>
#include <QDir>
#include <cmath>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const QStringList arguments = a.arguments();
    if (arguments.size() < 4) {
        qCritical() << "this program requires following attributes:"
                    << "[database file]"
                    << "[data definition file]"
                    << "[column 1]"
                    << "[column 2]";
        return -1;
    }

    QVector<QStringList> data;
    {
        const QString databaseFilename(arguments.at(1));
        QFile databaseFile(databaseFilename);
        if (!databaseFile.open(QIODevice::ReadOnly)) {
            qCritical() << "failed to open database file" << databaseFilename;
            return -2;
        }
        while (!databaseFile.atEnd()) {
            data << QString(databaseFile.readLine()).trimmed().split(QRegExp("\\s"), QString::SkipEmptyParts);
        }
        databaseFile.close();
    }

    QStringList dataDefinitions;
    {
        const QString dataDefinitionFilename(arguments.at(2));
        QFile dataDefinitionFile(dataDefinitionFilename);
        if (!dataDefinitionFile.open(QIODevice::ReadOnly)) {
            qCritical() << "failed to open data definition file" << dataDefinitionFilename;
            return -2;
        }
        while (!dataDefinitionFile.atEnd()) {
            dataDefinitions << QString(dataDefinitionFile.readLine()).trimmed();
        }
        dataDefinitionFile.close();
    }

    bool ok;
    const int keyCol = arguments.at(3).toInt(&ok);
    if (!ok) {
        qCritical() << "failed to parse" << arguments.at(2) << "as integer";
        return -3;
    }
    const int valCol = arguments.at(4).toInt(&ok);
    if (!ok) {
        qCritical() << "failed to parse" << arguments.at(3) << "as integer";
        return -3;
    }

    QMap<QString, QVector<double> > groupedData;
    for (int i = 0; i < data.size(); i++) {
        const QString &key = data.at(i).at(keyCol);
        groupedData[key].append(data.at(i).at(valCol).toDouble());
    }

    // value's first is average, second - std deviation
    QMap<QString, QPair<double, double> > displayData;
    for (int i = 0; i < groupedData.size(); i++) {
        double avg = 0;
        const QVector<double> values = groupedData.values().at(i);
        for (int j = 0; j < values.size(); j++) {
            avg += values.at(j);
        }
        avg /= values.size();
        double stddev = 0;
        for (int j = 0; j < values.size(); j++) {
            double temp = values.at(j) - avg;
            stddev += temp * temp;
        }
        stddev /= values.size();
        stddev = std::sqrt(stddev);
        displayData[groupedData.keys().at(i)] = qMakePair(avg, stddev);
    }

    QTextStream out(stdout);
    out << dataDefinitions.at(keyCol) << " : " << dataDefinitions.at(valCol) << endl;
    for (int i = 0; i < displayData.size(); i++) {
        out << displayData.keys().at(i) << " " << displayData.values().at(i).first << " " << displayData.values().at(i).second << endl;
    }
    
    return 0;
}
