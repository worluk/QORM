#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QVector>
#include <queryset.h>


#define QOrmModel(table)  class table : public QObject, public Table<table>

#define QOrmOrganizer()                                                                     \
     QOrmModelField(id, "integer PRIMARYKEY AUTO_INCREMENT")                                 \
    QOrmModelField(updated_at, "timestamp NOT_NULL")                                         \
    QOrmModelField(created_at, "timestamp NOT NULL")



#define QOrmModelField(fieldname, type)                                                     \
    public:                                                                                 \
        Q_PROPERTY(QString fieldname READ fieldname WRITE set##fieldname)                   \
        Q_CLASSINFO(fieldname, type)                                                        \
        QString fieldname() const{ return m_##fieldname;}                                   \
        void set##fieldname(const QString &fieldname){ m_##fieldname = fieldname;}          \
    private:                                                                                \
        QString m_##fieldname;

#define QOrmModelBelongsTo(target)                                                          \
        QOrmModelField(target##_id, "integer")                                              \
    public:                                                                                 \
        Q_PROPERTY(Table* target READ target WRITE set##target)                             \
                                                                                            \
        target* target##Accessor() const{ return m_##target;}                                    \
        void set##target(target* fieldname){ m_##target = fieldname;}                  \
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


template<class T>
class Table
{

public:
    virtual T& operator=(Queryset* q) {return static_cast<T>(*this);}

    Table(){}
    Queryset* all();
    Queryset* first();




};

#endif // TABLE_H
