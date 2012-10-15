#ifndef QUERYSET_H
#define QUERYSET_H

#include <QString>


class Queryset
{
public:
    bool operator==(Queryset* p){return query==p->query;}
    Queryset();
    Queryset(QString q){query = q;}
    QString getQuery(){return query;}

private:
    QString query;

};

#endif // QUERYSET_H
