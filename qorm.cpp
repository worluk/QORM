#include <qorm.h>


//QMap<QString, Table*> tables = QMap<QString, Table*>();

Qorm::Qorm(QString driver)
{
    db = QSqlDatabase::addDatabase(driver);
}

bool Qorm::setDatabaseName(QString name)
{
    if(db.isOpen())
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
    return db.open();
}
