#ifndef MACROS_H
#define MACROS_H

#define QOrmModel(table)  \
    class table : public QObject, public Table<table>

#define QOrmOrganizer(table)                                                                \
    Q_OBJECT                                                                                <crlf>\
    public:                                                                                 <crlf>\
	table() : Table<table>(){}																<crlf>\
	table(QString s) : Table<table>(s){}													<crlf>\
	QOrmModelField(id, "integer PRIMARY KEY AUTOINCREMENT")                                 <crlf>\
	QOrmModelField(created_at, "varchar(25) NOT NULL")										<crlf>\
    QOrmModelField(updated_at, "varchar(25) NOT NULL")                                      <crlf>



#define QOrmModelField(fieldname, type)                                                     \
    public:                                                                                 <crlf>\
        Q_PROPERTY(QString fieldname READ fieldname WRITE set##fieldname)     				<crlf>\
        Q_CLASSINFO(#fieldname, type)                                                       <crlf>\
        QString fieldname() const{ return m_##fieldname;}                                   <crlf>\
        void set##fieldname(const QString &fieldname){ m_##fieldname = fieldname;}          <crlf>\
    private:                                                                                <crlf>\
        QString m_##fieldname;																<crlf>

#define QOrmModelBelongsTo(target)                                                          \
        QOrmModelField(target##_id, "integer")                                              <crlf>\
    public:                                                                                 <crlf>\
        Q_PROPERTY(Table* target READ target WRITE set##target)                             <crlf>\
                                                                                            <crlf>\
        target* target##Accessor() const{ return m_##target;}                               <crlf>\
        void set##target(target* fieldname){ m_##target = fieldname;}                       <crlf>\
    private:                                                                                <crlf>\
        target* m_##target;																	<crlf>

#define QOrmModelHasMany(target)                                                            \
    Q_PROPERTY(Table* target READ target WRITE set##target)                                 <crlf>\
                                                                                            <crlf>\
    public:                                                                                 <crlf>\
        target* target##Accessor##s() const{ return (target*)m_##target->foreignKeyFor(this);}        <crlf>\
        void set##target(target* target){ m_##target = target;}                             <crlf>\
    private:                                                                                <crlf>\
        target* m_##target;																	<crlf>


#endif // MACROS_H
