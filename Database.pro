#-------------------------------------------------
#
# Project created by QtCreator 2012-10-12T18:05:15
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Database
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataset.cpp \
    table.cpp \
    patient.cpp \
    qorm.cpp \
    queryset.cpp

HEADERS  += mainwindow.h \
    dataset.h \
    patient.h \
    qorm.h \
    doctor.h \
    table.h \
    queryset.h

FORMS    += mainwindow.ui
