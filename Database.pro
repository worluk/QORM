#-------------------------------------------------
#
# Project created by QtCreator 2012-10-12T18:05:15
#
#-------------------------------------------------

include(QORM/qorm.pri)

QT       += core gui sql

TARGET = Database
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

TABLES += doctor.h \
    patient.h




