#ifndef COLLECTION_H
#define COLLECTION_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVector>

enum QORM_DIRECTION
{
    Q_ASC,
    Q_DESC
};

template<class T>
class Collection
{
public:

    T* operator[](int index){return data[index];}
    T* at(int index){return data[index];}
    Collection<T> operator=(Collection<T>*);
    Collection(){query = "";}
    Collection(QString s){query = s;}

    Collection<T>* find(QString);
    Collection<T>* find(QString, int);                           //collection
    Collection<T>* find(QString, QString);                       //collection
    Collection<T>* limit(int);                                   //collection
    Collection<T>* limit(int, int);                              //collection
    Collection<T>* order(QString s, QORM_DIRECTION d = Q_ASC);   //collection


    T* first();
    T* last();
    T* find(int);

    int length(){return data.size();}

    void debugQuery(){ qDebug() << query; }

protected:
    QVector<T*> data;
    QString query;
    bool exec();

};

template<class T>
bool Collection<T>::exec()
{
    T* item;
    data.clear();
    QSqlQuery q(query);
    QSqlRecord rec;
    QString data_query;
    while (q.next())
    {
        data_query = QString("SELECT * FROM ") + T::staticMetaObject.className() + QString(" WHERE id='") + q.record().value("id").toString() + QString("'");
        item = new T(data_query);

        rec = q.record();

        for(int i = 0;i < T::staticMetaObject.classInfoCount(); i++ )
            item->setProperty(rec.fieldName(i).toStdString().c_str(), rec.value(i).toString());
        data.append(item);

    }
    return true;
}

template<class T>
Collection<T> Collection<T>::operator=(Collection<T>* n)
{
    n->exec();
    this->data = n->data;
    this->query = n->query;
    return *n;
}

template<class T>
Collection<T>* Collection<T>::find(QString w)
{
    query += QString(" WHERE ") + w;
    return this;
}

template<class T>
Collection<T>* Collection<T>::find(QString f, int i)
{
    query += QString(" WHERE ") + f + QString("='") + QString::number(i) + QString("'");
    return this;
}

template<class T>
Collection<T>* Collection<T>::find(QString field, QString value)
{
    query += QString(" WHERE ") + field + QString("='") + value + QString("'");
    return this;
}

template<class T>
Collection<T>* Collection<T>::limit(int length)
{
    return limit(0, length);
}

template<class T>
Collection<T>* Collection<T>::limit(int from, int length)
{
    query += QString(" LIMIT ") + QString::number(from) + QString(",") + QString::number(length);
    return this;
}

template<class T>
Collection<T>* Collection<T>::order(QString field, QORM_DIRECTION direction)
{
    QString dir;
    if(direction == Q_ASC)
        dir = "ASC";
    else
        dir = "DESC";

    query += QString(" ORDER BY ") + field + QString(" ") + dir;
    return this;
}

/* Functions returning an object pointer, not a collection */
template<class T>
T* Collection<T>::find(int i)
{
    T* item;
    query += QString(" WHERE id='") + QString::number(i) + QString("'");
    item = new T(query);

    return item->exec();
}

template<class T>
T* Collection<T>::first()
{
    query += QString(" LIMIT 1") ;
    return (new T(query))->exec();
}

template<class T>
T* Collection<T>::last()
{
    query += QString(" LIMIT 1 DESC") ;
    return (new T(query))->exec();
}


#endif // COLLECTION_H
