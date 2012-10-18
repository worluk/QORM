#include "queryset.h"
#include <QStringList>
#include <QMetaClassInfo>
#include <stdarg.h>

Queryset::Queryset()
{
    bRecordNew = true; bRecordChanged = false;
}



Queryset* Queryset::first()
{
    query += QString(" LIMIT 1") ;
    return this;
}

Queryset* Queryset::last()
{
    query += QString(" DESC LIMIT 1") ;
    return this;
}

Queryset* Queryset::find(int i)
{
    query += QString(" WHERE id='") + QString::number(i) + QString("'");
    return this;
}

Queryset* Queryset::find(QString w)
{
    query += QString(" WHERE ") + w;
    return this;
}

Queryset* Queryset::find(QString f, int i)
{
    query += QString(" WHERE ") + f + QString("='") + QString::number(i) + QString("'");
    return this;
}

Queryset* Queryset::find(QString field, QString value)
{
    query += QString(" WHERE ") + field + QString("='") + value + QString("'");
    return this;
}

Queryset* Queryset::limit(int length)
{
    return limit(0, length);
}

Queryset* Queryset::limit(int from, int length)
{
    query += QString(" LIMIT ") + QString::number(from) + QString(",") + QString::number(length);
    return this;
}

Queryset* Queryset::order(QString field, QORM_DIRECTION direction)
{
    QString dir;
    if(direction == Q_ASC)
        dir = "ASC";
    else
        dir = "DESC";

    query += QString(" ORDER BY ") + field + QString(" ") + dir;
    return this;
}

void Queryset::save()
{
    if(bRecordNew)
    {

    }
}


Queryset* Queryset::insert(QString name, QStringList fields, QStringList values)
{
    QString insertQuery;

    insertQuery = QString("INSERT INTO ") + name + QString("(");
    insertQuery += fields.join(",");
    insertQuery += ") values (";
    insertQuery += values.join(",");
    insertQuery += ")";
    qDebug() << insertQuery;

    return new Queryset(insertQuery);
}


void Queryset::exec()
{
   /* if(query == q)
        return;
    else
    {

    }*/

}


int count_arguments(QString s)
{
    QStringList l = s.split(",");
    return l.count();
}
