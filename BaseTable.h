#ifndef BASETABLE_H
#define BASETABLE_H

#include <QVector>
#include <dataset.h>


template<class T> class BaseTable
{

public:
    BaseTable(){}
    BaseTable* find(uint index);
    BaseTable* all();
   // T* first(){return find(0);}
    //virtual T* foreignKeyFor(const BaseTable*);

private:
    QVector<Dataset> data;
};

#endif // BASETABLE_H
