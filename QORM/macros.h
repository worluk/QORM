#ifndef MACROS_H
#define MACROS_H

#define QOrmModel(table)  \
    class table : public Table

#define QOrmOrganizer(table)                                                                 						\
    Q_OBJECT                                                                                 						\
    public:                                                                                  						\
	table() : Table(){}																										\
	table(QString s) : Table(s){}																					\
	table& operator=(Queryset* q){exec(); return *this;}                            										\
	static table* all(){return new table(QString("SELECT * FROM ") + QString(staticMetaObject.className()));} 		\
	table* find(int i){return (table*)Table::find(i);}																\
	table* find(QString s){return (table*)Table::find(s);}															\
	table* find(QString s, int i){return (table*)Table::find(s, i);}												\
	table* find(QString s, QString v){return (table*)Table::find(s, v);}											\
	table* first() {return (table*)Table::first();}																	\
	table* last() {return (table*)Table::last();}																	\
	table* limit(int i) {return (table*)Table::limit(i);}															\
	table* limit(int i, int l) {return (table*)Table::limit(i,l);}													\
	table* order(QString s, QORM_DIRECTION d = Q_ASC) {return (table*)Table::order(s,d);}							\
    QOrmModelField(id, "integer PRIMARYKEY AUTO_INCREMENT")                                  						\
    QOrmModelField(updated_at, "varchar(25) NOT NULL")                                         						\
    QOrmModelField(created_at, "varchar(25) NOT NULL")																\
	public: \
	static table* doBuild(int count, ... ){ va_list parameters; va_start(parameters, count); QStringList fields, values;		\
    for(int i = 0;i < count; i++ ){																					\
        fields << staticMetaObject.classInfo(i+3).name();																\
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
