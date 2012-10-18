#ifndef QUERYSET_H
#define QUERYSET_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QDebug>
#include <stdarg.h>

#define build(...) doBuild(count_arguments(#__VA_ARGS__), __VA_ARGS__)

int count_arguments(QString s);

enum QORM_DIRECTION
{
    Q_ASC,
    Q_DESC
};

class Queryset : public QObject
{
    Q_OBJECT

public:
    bool operator==(Queryset* p){return query==p->getQuery();}
    Queryset();
    Queryset(QString q){query = q;}
    QString getQuery(){return query;}
    static Queryset* doBuild(int, ... );

    Queryset* first();
    Queryset* last();
    Queryset* find(int);
    Queryset* find(QString);
    Queryset* find(QString, int);
    Queryset* find(QString, QString);
    Queryset* limit(int);
    Queryset* limit(int, int);
    Queryset* order(QString s, QORM_DIRECTION d = Q_ASC);
    static Queryset* insert(QString name, QStringList fields, QStringList values);
    void save();


    void debugQuery(){ qDebug() << query; }


protected:
    QString query;
    virtual void exec();
    QVector<Queryset> collection;
    bool bRecordNew;
    bool bRecordChanged;

};

#endif // QUERYSET_H
