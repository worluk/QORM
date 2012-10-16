#-------------------------------------------------
#
# Project created by QtCreator 2012-10-12T18:05:15
#
#-------------------------------------------------

#http://stackoverflow.com/questions/12845513/getting-qmake-to-properly-run-my-code-generator

include(QORM/qorm.pri)

QT       += core gui sql

TARGET = Database
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    dataset.cpp \
    table.cpp \
    qorm.cpp \
    queryset.cpp \
    collection.cpp

HEADERS  += mainwindow.h \
    dataset.h \
    qorm.h \
    table.h \
    queryset.h \
    collection.h

FORMS    += mainwindow.ui

TABLES += doctor.h \
    patient.h




