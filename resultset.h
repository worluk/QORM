#ifndef RESULTSET_H
#define RESULTSET_H

#include <QObject>
#include <QVector>
#include <table.h>
#include <dataset.h>

class ResultSet : public QObject
{
    Q_OBJECT
public:
    explicit ResultSet(QObject *parent = 0);
    Resultset find(uint index);
    Resultset all();
    Resultset first(){return find(0);}


private:


signals:
    
public slots:
    
};

#endif // RESULTSET_H
