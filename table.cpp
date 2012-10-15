#include "table.h"



void Table::exec(Queryset* q)
{
    if(collection->qset == q)
        return;
    else
    {

    }

}

Queryset* Table:: all()
{
    return new Queryset(QString("SELECT * from ") + QString(staticMetaObject.className()) + QString(";"));
}


