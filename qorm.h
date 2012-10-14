#ifndef GORM_H
#define GORM_H

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
#include <table.h>

//extern QMap<QString, Table*> tables;


class Qorm : public QObject
{
    Q_OBJECT


public:
    Qorm(QString driver);
   // template<class T> static void registerTable();
    bool setDatabaseName(QString name);
    bool open();

protected:
    QSqlDatabase db;

};
/*
template<class T> void Gorm::registerTable()
{
    //create the new table
    T* model = new T;

    //get the class name
    const QString name = model->metaObject()->className();

    //add the table to the tables map
    if (!tables.contains(name))
       tables.insert(name, (Table*)(model));

    //check if the table is existing

    //check if the table is up to date
}
*/

#endif // GORM_H
