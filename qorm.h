#ifndef GORM_H
#define GORM_H

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <table.h>

class Qorm : public QObject
{
    Q_OBJECT


public:
    Qorm(QString driver);
    template<class T> static void registerTable();
    bool setDatabaseName(QString name);
    bool open();

protected:
    QSqlDatabase db;

};

template<class T> void Qorm::registerTable()
{
    //create the new table
    T* model = new T;

    //get the class name
    const QString name = model->metaObject()->className();

    QSqlQuery q;
    //check if the table is existing
    q.exec(QString("SELECT * from QORM_MASTER where name = '")+ name + QString("'"));
    q.first();
    if(q.isValid())
        qDebug() << "Table" << name << " found.";
    else
    {

        qDebug() << "Table" << name << "not found.";

        if(!model->create())
            qDebug() << "Error when creating table " << name;
    }

    delete model;
}


#endif // GORM_H
