#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMetaClassInfo>
#include <collection.h>
#include <queryset.h>
#include <stdarg.h>

class Table : public Queryset
{
public:
    Table() : Queryset(){}
    Table(QString s) : Queryset(s){}
    bool create();


protected:
    Collection* collection;


};

#endif // TABLE_H
