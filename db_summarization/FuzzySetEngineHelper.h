#ifndef FUZZYSETENGINEHELPER_H
#define FUZZYSETENGINEHELPER_H

#include <QVector>
#include <QScriptValue>
#include <QScriptProgram>
#include <QHash>
#include <QMutex>

class QScriptEngine;

class FuzzySetEngineHelper
{
public:
    static QScriptEngine *getEngine(const int &idx);
    static QScriptValue getConstructor(const int &idx);
    static int getIdForThread(const int &idx);
    static void createFunctionForThreadId(const int &tIdx, const int &fId, const QScriptValueList &values);
    static QScriptValue getFuncForThreadId(const int &tIdx, const int &fId);
    static void init(const int &count, const QString &source);
    static void clear();

private:
    FuzzySetEngineHelper() = default;
    static QVector<QScriptEngine *> mEngines;
    static QVector<QScriptValue> mConstructors;
    static QVector<QScriptProgram> mPrograms;
    static QVector<QHash<int, QScriptValue> > mFunctions;
    static QHash<int, QScriptValue> *mPFunctions;
    static QMutex mCreatorMutex;
};

#endif // FUZZYSETENGINEHELPER_H
