#include <qorm.h>


//QMap<QString, Table> tables = QMap<QString, Table>();

Qorm::Qorm(QString driver)
{
    db = QSqlDatabase::addDatabase(driver);
}

bool Qorm::setDatabaseName(QString name)
{
    if(!db.isOpen())
    {
        db.setDatabaseName(name);
        return true;
    }
    else
    {
        return false;
    }

}

bool Qorm::open()
{
    QBool b = QBool(db.open());
    if(b)
    {
        QSqlQuery q("SELECT * from QORM_MASTER;");
        if(!q.exec())
        {
            qDebug() << "Master table not found!";
            //create master table
            if(q.exec("CREATE TABLE QORM_MASTER(name varchar(255), created_at varchar(25), updated_at varchar(25), version integer);"))
            {
                qDebug() << "Created";
                return true;
            }
            else
            {
                qDebug() << "Could not create master table. " << q.lastQuery();
                return false;
            }
        }
        else
        {
            qDebug() << "Master table found!";
            return true;
        }


    }
    else
        return false;
}
