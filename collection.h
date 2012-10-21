#ifndef COLLECTION_H
#define COLLECTION_H



enum QORM_DIRECTION
{
    Q_ASC,
    Q_DESC
};

template<class T>
class Collection
{
public:

    T operator[](int index){return data[index];}
    Collection<T> operator=(Collection<T>*){return *this;}
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

    void debugQuery(){ qDebug() << query; }

protected:
    QVector<T*> data;
    QString query;

};


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
    query += QString(" WHERE id='") + QString::number(i) + QString("'");
    return new T(query);
}

template<class T>
T* Collection<T>::first()
{
    query += QString(" LIMIT 1") ;
    return new T(query);
}

template<class T>
T* Collection<T>::last()
{
    query += QString(" LIMIT 1 DESC") ;
    return new T(query);
}


#endif // COLLECTION_H
