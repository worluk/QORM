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
    qorm.cpp

HEADERS  += mainwindow.h \
    qorm.h \
    table.h \
    collection.h

FORMS    += mainwindow.ui

TABLES += doctor.h \
    patient.h




