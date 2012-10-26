#ifndef MACROS_H
#define MACROS_H


#define QORMModelReferences(table) class table;	<crlf>\
		QORMDependsOn(table)

#define QOrmModel(table)  \
    class table : public QObject, public Table<table>

#define QOrmOrganizer(table)                                                                \
    Q_OBJECT                                                                                <crlf>\
    public:                                                                                 <crlf>\
	table() : Table<table>(){}																<crlf>\
	table(QString s) : Table<table>(s){}													<crlf>\
	QOrmModelField(id, int, QORM_PK QORM_AI)                            				<crlf>\
	QOrmModelField(created_at, QDateTime, QORM_NOTNULL)									<crlf>\
    QOrmModelField(updated_at, QDateTime, QORM_NOTNULL)                                	<crlf>



#define QOrmModelField(fieldname, type, options)                                                  \
    public:                                                                                 <crlf>\
        Q_PROPERTY(type fieldname READ fieldname WRITE set##fieldname)     				<crlf>\
        Q_CLASSINFO(#fieldname, #type" "#options)                                              <crlf>\
        type fieldname() const{ return m_##fieldname;}                                   <crlf>\
        void set##fieldname(const type &fieldname){bRecordChanged=true; m_##fieldname = fieldname;}          <crlf>\
    private:                                                                                <crlf>\
        type m_##fieldname;																<crlf>

#define QOrmModelBelongsTo(target, accessor)                                                          \
        QOrmModelField(target##_id, int,)	                                              <crlf>\
    public:                                                                                 <crlf>\
        target* accessor() { return getForeignObject<target>();}                               <crlf>\
        void set##target(target* object){setForeignObject<target>(object);}   

#define QOrmModelHasMany(target, accessors)                                                            \
    public:                                                                                 <crlf>\
        Collection<target>* accessors() { return getForeignCollection<target>();}        


#endif // MACROS_H
