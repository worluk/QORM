#include <qorm.h>

QMap<QString, QString> keywords;


Qorm::Qorm(QString driver)
{
    db = QSqlDatabase::addDatabase(driver);
    if(driver == "QSQLITE")
    {
        keywords["QORM_PK"] = "PRIMARY KEY";
        keywords["QORM_AI"] = "AUTOINCREMENT";
        keywords["QORM_NOTNULL"] = "NOT NULL";
        keywords["int"] = "INTEGER";
        keywords["QString"] = "VARCHAR(255)";
        keywords["QDateTime"] = "VARCHAR(25)";
    }
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

int count_arguments(QString s)
{
    QStringList l = s.split(",");
    return l.count();
}
