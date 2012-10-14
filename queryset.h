#ifndef QUERYSET_H
#define QUERYSET_H

#include <QString>


class Queryset
{
public:
    bool operator==(Queryset* p){return query==p->query;}
    Queryset();

private:
    QString query;

};

#endif // QUERYSET_H
