#ifndef MACROS_H
#define MACROS_H

#define QOrmModel(table)  \
    class table : public Table

#define QOrmOrganizer(table)                                                                 						\
    Q_OBJECT                                                                                 						\
    public:                                                                                  						\
	table() : Table(){}																								\
	table(QString s) : Table(s){}																					\
	table* operator=(Table* q){q->exec(); return this;} \
	static Collection<table>* all(){return new Collection<table>(QString("SELECT * FROM ") + QString(staticMetaObject.className()));} 		\
    int getLastID(){QSqlQuery q; q.exec("SELECT seq FROM sqlite_sequence where name ='table'"); q.first();return q.value(0).toInt();}	\
	QOrmModelField(id, "integer PRIMARY KEY AUTOINCREMENT")                                  						\
    QOrmModelField(updated_at, "varchar(25) NOT NULL")                                         						\
    QOrmModelField(created_at, "varchar(25) NOT NULL")																\
	public: 																										\
		static table* doBuild(int count, ... ){ va_list parameters; va_start(parameters, count); QStringList fields, values;		\
		fields << staticMetaObject.classInfo(1).name();																	\
		values << QString("datetime()");																				\
		fields << staticMetaObject.classInfo(2).name();																	\
		values << QString("datetime()");																				\
		for(int i = 0;i < count; i++ ){																					\
			fields << staticMetaObject.classInfo(i+3).name();															\
			values << QString("'") + QString(va_arg(parameters, char*)) + QString("'");									\
		}																												\
		va_end(parameters);																								\
		return (table*)(setup(staticMetaObject.className(), fields, values));											\
		}																												\
		static table* doCreate(int count, ... ){ va_list parameters; va_start(parameters, count); QStringList fields, values;		\
		fields << staticMetaObject.classInfo(1).name();																	\
		values << QString("datetime()");																				\
		fields << staticMetaObject.classInfo(2).name();																	\
		values << QString("datetime()");																				\
		for(int i = 0;i < count; i++ ){																					\
			fields << staticMetaObject.classInfo(i+3).name();															\
			values << QString("'") + QString(va_arg(parameters, char*)) + QString("'");									\
		}																												\
		va_end(parameters);																								\
		return (table*)(insert(staticMetaObject.className(), fields, values));							\
		}



#define QOrmModelField(fieldname, type)                                                     \
    public:                                                                                 \
        Q_PROPERTY(QString fieldname READ fieldname WRITE set##fieldname)                   \
        Q_CLASSINFO(#fieldname, type)                                                        \
        QString fieldname() const{ return m_##fieldname;}                                   \
        void set##fieldname(const QString &fieldname){ m_##fieldname = fieldname;}          \
    private:                                                                                \
        QString m_##fieldname;

#define QOrmModelBelongsTo(target)                                                          \
        QOrmModelField(target##_id, "integer")                                              \
    public:                                                                                 \
        Q_PROPERTY(Table* target READ target WRITE set##target)                             \
                                                                                            \
        target* target##Accessor() const{ return m_##target;}                               \
        void set##target(target* fieldname){ m_##target = fieldname;}                       \
    private:                                                                                \
        target* m_##target;

#define QOrmModelHasMany(target)                                                            \
    Q_PROPERTY(Table* target READ target WRITE set##target)                                 \
                                                                                            \
    public:                                                                                 \
        target* target##Accessor##s() const{ return (target*)m_##target->foreignKeyFor(this);}        \
        void set##target(target* target){ m_##target = target;}                             \
    private:                                                                                \
        target* m_##target;


#endif // MACROS_H
