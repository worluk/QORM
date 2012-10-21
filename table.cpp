#include <QStringList>
#include <QMetaClassInfo>
#include <QSqlQuery>
#include "table.h"


bool Table::create()
{
    QString name = this->metaObject()->className();
    qDebug() << "Create" << this->metaObject()->className() << "table";

    QString createQuery = QString("CREATE TABLE ") + name + QString("(");
    QStringList fields;

    //TODO: handle conversion between different sql engines for datatypes

    for(int i = 0;i < this->metaObject()->classInfoCount(); i++ )
    {
        fields << QString(metaObject()->classInfo(i).name()) + " " + QString(metaObject()->classInfo(i).value());
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

Table::Table()
{
    bRecordNew = true;
    bRecordChanged = false;
}


void Table::save()
{
    if(bRecordNew)
    {

    }
}

Table* Table::setup(QString name, QStringList fields, QStringList values)
{
    QString insertQuery;

    insertQuery = QString("INSERT INTO ") + name + QString("(");
    insertQuery += fields.join(",");
    insertQuery += ") values (";
    insertQuery += values.join(",");
    insertQuery += ")";

    Table* t = (new Table(insertQuery))->exec();
    m_id = getLastID();
    t->reload();
    return t;
}


Table* Table::insert(QString name, QStringList fields, QStringList values)
{
    QString insertQuery;

    insertQuery = QString("INSERT INTO ") + name + QString("(");
    insertQuery += fields.join(",");
    insertQuery += ") values (";
    insertQuery += values.join(",");
    insertQuery += ")";
    Table* t = (new Table(insertQuery))->exec();
    m_id = getLastID();
    t->reload();
    return t;
}




Table*  Table::exec()
{
   QSqlQuery q;
   qDebug() << query;
   qDebug() << "Succeeded:" << q.exec(query);


   return this;
}


bool Table::reload()
{
    QSqlQuery q;
    q.exec("SELECT ")
}

int count_arguments(QString s)
{
    QStringList l = s.split(",");
    return l.count();
}

