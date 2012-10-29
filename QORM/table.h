#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QMetaClassInfo>
#include <stdarg.h>
#include <collection.h>


extern QMap<QString, QString> keywords;

#define build(...) doBuild(count_arguments(#__VA_ARGS__), __VA_ARGS__)
#define generate(...) doCreate (count_arguments(#__VA_ARGS__), __VA_ARGS__)

int count_arguments(QString s);

template<class T>
class Table
{

public:

    Table();
    Table(QString q);
    void initProperties();

    bool operator==(Table* p){return query==p->getQuery();}
    T* operator=(T* q);

    bool save();
    void destroy();

    static Collection<T>* all(){return (new Collection<T>(QString("SELECT * FROM ") + QString(T::staticMetaObject.className())));}
    static Collection<T>* all(QList<QORMField> f){return (new Collection<T>(QString("SELECT * FROM ") + QString(T::staticMetaObject.className()), f));}
    static T* doBuild(int count, ... );
    static T* doCreate(int count, ... );
    static bool create();

    template<class U> U* getForeignObject();
    template<class U> void setForeignObject(U* object);
    template<class U> Collection<U>* getForeignCollection();

    void debugQuery(){ qDebug() << query; }

    bool reload();





    int dataid;
    int m_id;
    T* exec();
protected:

    QString query;


    bool bRecordChanged;


};


template<class T>
template<class U>
void Table<T>::setForeignObject(U* object)
{
    if(object->id() == 0)
        object->save();

    QString foreignTable = U::staticMetaObject.className();
    QString fieldname = foreignTable + QString("_id");

    T* item = (T*)this;
    item->setProperty(fieldname.toStdString().c_str(), object->id());
    bRecordChanged =true;

}
template<class T>
template<class U>
U* Table<T>::getForeignObject()
{
    //SELECT t1.* FROM Doctor t1 JOIN Patient t2 ON t2.Doctor_id = t1.id where t2.id=1
    QString foreignTable = U::staticMetaObject.className();
    QString ownTable = T::staticMetaObject.className();
    QString fieldname = foreignTable + QString("_id");
    T* self = (T*)this;

    QString objectQuery = QString("SELECT t1.* FROM ") + foreignTable + QString(" t1 JOIN ") + ownTable + QString(" t2 ON t2.") + fieldname + QString("=t1.id where t2.id=") + QString::number(self->id());
    U* item = new U(objectQuery);

    return item->exec();
}

template<class T>
template<class U>
Collection<U>* Table<T>::getForeignCollection()
{
    //SELECT t1.* FROM PATIENT t1 JOIN Doctor t2 ON t1.Doctor_id = t2.id
    QString foreignTable = U::staticMetaObject.className();
    QString ownTable = T::staticMetaObject.className();
    QString fieldname = ownTable + QString("_id");

    QString objectQuery = QString("SELECT t1.* FROM ") + foreignTable + QString(" t1 JOIN ") + ownTable + QString(" t2 ON t1.") + fieldname + QString("=t2.id");
    Collection<U>* item = new Collection<U>(objectQuery);

    item->exec();
    return item;
}

template<class T>
bool Table<T>::create()
{
    QString name = T::staticMetaObject.className();
    qDebug() << "Create" << T::staticMetaObject.className() << "table";

    QString createQuery = QString("CREATE TABLE ") + name + QString("(");
    QStringList fields;

    for(int i = 0;i < T::staticMetaObject.classInfoCount(); i++ )
    {
        //handling types and keywords
        QStringList infoValues = QString(T::staticMetaObject.classInfo(i).value()).split(" ");
        QStringList infoValuesResult;
        for(int n=0;n<infoValues.count();n++)
           infoValuesResult << keywords[infoValues[n]];


        //build the SQL
        fields << QString(T::staticMetaObject.classInfo(i).name()) + " " + infoValuesResult.join(" ");
    }

    createQuery += fields.join(",");

    createQuery += ");";


    QSqlQuery q;
    if(!q.exec(createQuery))
    {
        qDebug() << "Creating table " << name << "failed";
        qDebug() << q.lastQuery();
        return false;
    }
    return q.exec(QString("INSERT INTO QORM_MASTER values('") + name + QString("',datetime(),datetime(), 1)"));


}

template<class T>
T* Table<T>::operator=(T* q)
{
    q->exec();
    return this;
}


template<class T>
Table<T>::Table()
{
    bRecordChanged = true;
    m_id = 0;
    dataid = 0;
}

template<class T>
Table<T>::Table(QString q)
{
    bRecordChanged = true;
    m_id = 0;
    dataid = 0;
    query = q;
}

template<class T>
void Table<T>::destroy()
{

    QString whereString = query.mid(query.indexOf("WHERE"));
    QString s = QString("DELETE FROM ") + T::staticMetaObject.className() + QString(" ") + whereString;
    qDebug() << s;

    QSqlQuery q;
    q.exec(s);
    delete static_cast<T*>(this);

}

template<class T>
bool Table<T>::save()
{
    QStringList fields, values;
    QSqlQuery q;
    QString s = QString("SELECT * FROM ") + T::staticMetaObject.className() + QString(" WHERE id='") +  QString::number(((T*)this)->id()) + QString("'");
    qDebug() << s;
    bool ret = q.exec(s);
    bool exists = q.next();


    if(ret && exists)
    {
        QString name;
        //UPDATE
        s = QString("UPDATE ") + T::staticMetaObject.className() + QString(" SET ");

        fields << "updated_at=datetime()";
        for(int i = 3;i < T::staticMetaObject.classInfoCount(); i++ )
        {
            name = T::staticMetaObject.classInfo(i).name();
            fields << name + QString(" ='") + ((T*)this)->property(name.toStdString().c_str()).toString()  + QString("'");
        }
         s += fields.join(",");
        s+= QString(" WHERE id = '") + QString::number(((T*)this)->id()) + QString("'");
        qDebug() << s;
        q.exec(s);
    }
    else
    {
        QString name;
        //INSERT
        s = QString("INSERT INTO ") + T::staticMetaObject.className() + QString("(");

        fields << T::staticMetaObject.classInfo(1).name();
        values << QString("datetime()");
        fields << T::staticMetaObject.classInfo(2).name();
        values << QString("datetime()");
        for(int i = 3;i < T::staticMetaObject.classInfoCount(); i++ )
        {
            name = T::staticMetaObject.classInfo(i).name();
            fields << name;
            values << QString("'")+((T*)this)->property(name.toStdString().c_str()).toString()+QString("'");
        }

        s += fields.join(",");
        s += ") values (";
        s += values.join(",");
        s += ")";
        qDebug() << s;
        q.exec(s);
        QString idquery = QString("SELECT * FROM ") + T::staticMetaObject.className() + QString(" ORDER BY id DESC LIMIT 1");
        QSqlQuery idq(idquery);

        idq.first();
        dataid = idq.value(0).toInt();
        ((T*)this)->setid(dataid);
        ((T*)this)->setupdated_at( idq.value(2).toDateTime());
        ((T*)this)->setcreated_at(idq.value(1).toDateTime());
        //reload();
    }
    query = QString("SELECT * FROM ") + T::staticMetaObject.className() + QString(" WHERE id='") + QString::number(dataid) + QString("'");
    qDebug() << "query:" << query;
    return true;
}

template<class T>
T* Table<T>::exec()
{
    if(!bRecordChanged)
        return (T*)this;
    QSqlRecord rec;
    T* item = (T*)this;
   QSqlQuery q;
  // qDebug() << query;
    q.exec(query);

   q.first();
   rec = q.record();

   for(int i = 0;i < T::staticMetaObject.classInfoCount(); i++ )
       item->setProperty(rec.fieldName(i).toStdString().c_str(), rec.value(i).toString());


   return item;
}

template<class T>
bool Table<T>::reload()
{
    bool r = true;
    T* o = (T*)this;
    QSqlQuery q;
    QSqlRecord rec;
    QString reloadQuery = QString("SELECT * FROM ") + T::staticMetaObject.className() + QString(" WHERE id='") + QString::number(dataid) + QString("'") ;

    r |= q.exec(reloadQuery);
    r |= q.first();
    rec = q.record();

    for(int i = 0;i < T::staticMetaObject.classInfoCount(); i++ )
        r |= o->setProperty(rec.fieldName(i).toStdString().c_str(), rec.value(i).toString());


    return r;
}

template<class T>
T* Table<T>::doBuild(int count, ... )
{
    va_list parameters;
    va_start(parameters, count);
    QStringList fields, values;
    fields << T::staticMetaObject.classInfo(1).name();
    values << QString("datetime()");
    fields << T::staticMetaObject.classInfo(2).name();
    values << QString("datetime()");
    for(int i = 3;i < count+3; i++ ){
        fields << T::staticMetaObject.classInfo(i).name();
        values << QString(va_arg(parameters, char*));
    }
    va_end(parameters);


    bool r = true;
    T* t = new T();
    //id eines ungespeicherten objektes ist 0
    t->setProperty("id", 0);

    //setzte die angegebenen werte
    for(int i = 0;i < count+2; i++ )
        r |= t->setProperty(fields[i].toStdString().c_str(), values[i]);

    //Alle anderen Werte auf 0 setzen.
    for(int i= count+3;i < T::staticMetaObject.classInfoCount(); i++)
        r |= t->setProperty(T::staticMetaObject.classInfo(i).name(), 0);

    if(!r)
        qDebug() << "error";

   return t;
}

template<class T>
T* Table<T>::doCreate(int count, ... )
{

}








#endif // TABLE_H
