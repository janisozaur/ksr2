#include "FuzzySetEngineHelper.h"

#include <QScriptEngine>
#include <QCoreApplication>

//#include <QDebug>

QVector<QScriptEngine *> FuzzySetEngineHelper::mEngines;
QVector<QScriptValue> FuzzySetEngineHelper::mConstructors;
QVector<QScriptProgram> FuzzySetEngineHelper::mPrograms;
QVector<QHash<int, QScriptValue> > FuzzySetEngineHelper::mFunctions;
QMutex FuzzySetEngineHelper::mCreatorMutex;
QHash<int, QScriptValue> *FuzzySetEngineHelper::mPFunctions;

QScriptEngine *FuzzySetEngineHelper::getEngine(const int &idx)
{
    return mEngines.at(idx);
}

QScriptValue FuzzySetEngineHelper::getConstructor(const int &idx)
{
    return mConstructors.at(idx);
}

int FuzzySetEngineHelper::getIdForThread(const int &idx)
{
    return mFunctions.at(idx).size();
}

void FuzzySetEngineHelper::createFunctionForThreadId(const int &tIdx,
                                                     const int &fId,
                                                     const QScriptValueList &values)
{
    // QVector::operator[] is not thread-safe!
    mCreatorMutex.lock();
    //qDebug() << "ctor:" << mConstructors.at(tIdx).isFunction() << mConstructors.at(tIdx).toString();
    mFunctions[tIdx][fId] = mConstructors[tIdx].call(QScriptValue(), values);
    mCreatorMutex.unlock();
}

QScriptValue FuzzySetEngineHelper::getFuncForThreadId(const int &tIdx, const int &fId)
{
    return mPFunctions[tIdx].value(fId);
}

void FuzzySetEngineHelper::init(const int &count, const QString &source)
{
    clear();
    mEngines.reserve(count);
    mConstructors.reserve(count);
    mPrograms.reserve(count);
    mFunctions.resize(count);
    mPFunctions = mFunctions.data();
    for (int i = 0; i < count; i++) {
        QScriptEngine *e = new QScriptEngine(QCoreApplication::instance());
        mEngines.append(e);
        QScriptProgram p(source);
        mPrograms.append(p);
        mConstructors.append(e->evaluate(p));
    }
}

void FuzzySetEngineHelper::clear()
{
    mConstructors.resize(0);
    mPrograms.resize(0);
    mFunctions.resize(0);
    for (int i = 0; i < mEngines.size(); i++) {
        delete mEngines.at(i);
    }
}
