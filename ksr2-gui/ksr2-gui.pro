#-------------------------------------------------
#
# Project created by QtCreator 2012-01-07T17:47:12
#
#-------------------------------------------------

QT       += core gui

TARGET = ksr2-gui
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        MainWindow.cpp \
    Quantifier.cpp

HEADERS  += MainWindow.h \
    Quantifier.h \
    Common.h

FORMS    += MainWindow.ui
