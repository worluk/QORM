TableMocHeader.output  = ./QORM/moc_${QMAKE_FILE_BASE}.cpp
TableMocHeader.commands = moc ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
TableMocHeader.depend_command = $$QMAKE_CXX -E -M $(CXXFLAGS) $(INCPATH) $$QMAKE_INCDIR ${QMAKE_FILE_NAME} | sed \"s/^.*: //\"
TableMocHeader.input = NEW_HEADERS
TableMocHeader.variable_out = SOURCES

TableBuild.output = ./tbl_${QMAKE_FILE_BASE}.h
TableBuild.commands = cat QORM/header.tmpl ${QMAKE_FILE_NAME} QORM/footer.tmpl  |sed \"s/__QORMFILE__/QORM${QMAKE_FILE_BASE}/\"  > ${QMAKE_FILE_OUT}
TableBuild.input = PRE_HEADERS
TableBuild.CONFIG = no_link
TableBuild.variable_out = NEW_HEADERS

TablePrepare.output = ./QORM/${QMAKE_FILE_BASE}.pretbl
TablePrepare.commands =  $$QMAKE_CXX -P -E ${QMAKE_FILE_NAME} -include ./QORM/macros.h | sed \'s/QORMDependsOn(\\(.*\\))/$${LITERAL_HASH}include \"tbl_\\1.h\"/g\' | sed \"s/<crlf>/°/g\" | tr \"°\" \"\\012\" > ${QMAKE_FILE_OUT}
TablePrepare.input = TABLES
TablePrepare.CONFIG = no_link
TablePrepare.variable_out = PRE_HEADERS

QMAKE_EXTRA_COMPILERS += TablePrepare TableBuild TableMocHeader 

SOURCES += QORM/qorm.cpp \
    QORM/qormtableview.cpp

HEADERS  += QORM/qorm.h \
    QORM/table.h \
    QORM/collection.h \
    QORM/qormtableview.h \
    QORM/qormfield.h

INCLUDEPATH += QORM
