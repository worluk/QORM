#-------------------------------------------------
#
# Project created by QtCreator 2012-10-12T18:05:15
#
#-------------------------------------------------

#http://stackoverflow.com/questions/12845513/getting-qmake-to-properly-run-my-code-generator

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
    collection.h \
    macros.h

FORMS    += mainwindow.ui

TABLES += tables/doctor.h \
    tables/patient.h



TableBuild.output = ./tables/tbl_${QMAKE_FILE_BASE}.h
TableBuild.commands =  d:/QtSDK/mingw/bin/mingw32-gcc.exe -P -E  -I d:/QtSDK/Desktop/Qt/4.8.0/mingw/include ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}# -include QtCore/qobject.h
TableBuild.input = TABLES
TableBuild.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += TableBuild


##mytarget.commands = $QMAKE_CXX -E $$(TABLES) -o $$(TABLES).tbl
##QMAKE_EXTRA_TARGETS += mytarget
#PRE_TARGETDEPS += ${TABLES}
