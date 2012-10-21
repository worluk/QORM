#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMetaClassInfo>
#include <stdarg.h>
#include <collection.h>

#define build(...) doBuild(count_arguments(#__VA_ARGS__), __VA_ARGS__)
#define generate(...) doCreate (count_arguments(#__VA_ARGS__), __VA_ARGS__)

int count_arguments(QString s);


class Table : public QObject
{
    Q_OBJECT
public:

    Table();
    Table(QString q){query = q;}
    bool create();

    bool operator==(Table* p){return query==p->getQuery();}

    QString getQuery(){return query;}

    static Table* setup(QString name, QStringList fields, QStringList values);
    static Table* insert(QString name, QStringList fields, QStringList values);
    void save();


    void debugQuery(){ qDebug() << query; }

    Table* exec();

    bool reload();

protected:
    int m_id;
    QString query;

    bool bRecordNew;
    bool bRecordChanged;


};

#endif // TABLE_H
