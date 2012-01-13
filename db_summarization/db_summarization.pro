#-------------------------------------------------
#
# Project created by QtCreator 2011-12-30T17:00:39
#
#-------------------------------------------------

QT       += core script

QT       -= gui

TARGET = db_summarization
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../qjson/include/

LIBS += -L../qjson/lib -lqjson -lgomp

QMAKE_CXXFLAGS += -std=c++0x -fopenmp -O3 -mtune=native -march=native

SOURCES += main.cpp \
    trianglefunction.cpp \
    trapezoidfunction.cpp \
    discretefunction.cpp \
    basicfuzzyset.cpp \
    alphacut.cpp \
    fuzzyset.cpp \
    union.cpp \
    intersection.cpp \
    complement.cpp \
    support.cpp \
    quantifier.cpp \
    qualitymeasures.cpp \
    MembershipFunctionFactory.cpp \
    summarization.cpp \
    linguisticvalue.cpp \
    fileparser.cpp \
    summarizationgenerator.cpp \
    FuzzySetType2.cpp \
    FuzzySetEngineHelper.cpp

HEADERS += \
    membershipfuncineterface.h \
    trianglefunction.h \
    trapezoidfunction.h \
    discretefunction.h \
    basicfuzzyset.h \
    fuzzyset.h \
    alphacut.h \
    union.h \
    intersection.h \
    complement.h \
    support.h \
    quantifier.h \
    qualitymeasures.h \
    MembershipFunctionFactory.h \
    linguisticvalue.h \
    summarization.h \
    fileparser.h \
    summarizationgenerator.h \
    FuzzySetType2.h \
    FuzzySetEngineHelper.h

OTHER_FILES += \
    qscripts/func.qs
