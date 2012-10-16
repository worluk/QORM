#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <collection.h>
#include <queryset.h>


class Table : public QObject
{
public:

    Table(){}
    static Queryset* all();
    bool create();


protected:
    void exec(Queryset*);
    Collection* collection;


};

#endif // TABLE_H
