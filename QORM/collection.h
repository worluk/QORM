#ifndef COLLECTION_H
#define COLLECTION_H


#include <QSqlQuery>
#include <QSqlRecord>
#include <QVector>
#include <QAbstractItemModel>
#include <QStandardItemModel>

#include <qormfield.h>

enum QORM_DIRECTION
{
    Q_ASC,
    Q_DESC
};

class BaseCollection : public QStandardItemModel
{
public:
    BaseCollection(QString q){query = q;}
    virtual BaseCollection* find(QString w){query += QString(" WHERE ") + w; return this;}
    void update(QString w){query = query.mid(0, query.indexOf(" WHERE"))+w; exec();}
    virtual bool exec() = 0;
    void debugQuery(){ qDebug() << query; }
    virtual QVariant data ( int i, int j  )const = 0;
    void reload(){exec();}
protected:
    QString query;
};

template<class T>
class Collection : public BaseCollection
{
public:

    T* operator[](int index){return model_data[index];}
    T* at(int index){return model_data[index];}
    Collection<T> operator=(Collection<T>*);
    Collection() : QStandardItemModel() {query = "";}
    Collection(QString s) : BaseCollection(s){}
    Collection(QString s, QList<QORMField> f) : BaseCollection(s){fieldMapping = f;}

    Collection<T>* find(QString);
    Collection<T>* find(QString, int);                           //collection
    Collection<T>* find(QString, QString);                       //collection
    Collection<T>* limit(int);                                   //collection
    Collection<T>* limit(int, int);                              //collection
    Collection<T>* order(QString s, QORM_DIRECTION d = Q_ASC);   //collection

    Collection<T>* withFields(QList<QORMField>);

    T* first();
    T* last();
    T* find(int);

    int length(){return model_data.size();}


    bool exec();



    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() )const;
    QModelIndex parent ( const QModelIndex & index )const;
    int rowCount ( const QModelIndex & parent = QModelIndex() )const;
    int columnCount ( const QModelIndex & parent = QModelIndex() )const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole )const;
    QVariant data ( int i, int j  )const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

protected:
    //QMap<QString, QString> fieldMapping;
    QVector<T*> model_data;

    QList<QORMField> fieldMapping;




};

template<class T>
bool Collection<T>::exec()
{
    T* item;

    for(int i=0;i<model_data.size();i++)
        delete model_data[i];
    model_data.clear();
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
        model_data.append(item);

    }
    emit dataChanged(createIndex(0,0),createIndex(rowCount()-1,columnCount()-1));
    return true;
}

template<class T>
Collection<T> Collection<T>::operator=(Collection<T>* n)
{
    n->exec();
    this->model_data = n->model_data;
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
    query += QString(" ORDER BY id DESC LIMIT 1 ") ;
    return (new T(query))->exec();
}


/* QAbstractItemModel Functions */
template<class T>
QModelIndex Collection<T>::index ( int row, int column, const QModelIndex & parent  )const
{
    return createIndex(row, column);
}

template<class T>
QModelIndex Collection<T>::parent ( const QModelIndex & index )const
{
    return QModelIndex();
}


template<class T>
int Collection<T>::rowCount ( const QModelIndex & parent  )const
{
    return model_data.size();
}


template<class T>
int Collection<T>::columnCount ( const QModelIndex & parent  )const
{

    return fieldMapping.size();
}


template<class T>
QVariant Collection<T>::data ( const QModelIndex & index, int role  )const
{
     QString name;
    switch(role)
    {
        case Qt::DisplayRole:
            Q_ASSERT(model_data.size()>index.row());
            Q_ASSERT(T::staticMetaObject.classInfoCount()>index.column());

            name = fieldMapping[index.column()].key();
            return model_data[index.row()]->property(name.toStdString().c_str());
            break;
        default:
            return QVariant();
            break;
    };
    return NULL;
}

template<class T>
QVariant Collection<T>::data ( int i, int j  )const
{
     QString name;

     Q_ASSERT(model_data.size()>i);
     Q_ASSERT(T::staticMetaObject.classInfoCount()>j);

     name = fieldMapping[j].key();
     return model_data[i]->property(name.toStdString().c_str());

}

template<class T>
QVariant Collection<T>::headerData ( int section, Qt::Orientation orientation, int role ) const
{

    switch(role)
    {
        case Qt::DisplayRole:
            return fieldMapping[section].value();
            break;
        default:
            return QVariant();
            break;
    };
    return NULL;
}

template<class T>
Collection<T>* Collection<T>::withFields(QList<QORMField> map)
{
    fieldMapping = map;
    return this;
}


#endif // COLLECTION_H
