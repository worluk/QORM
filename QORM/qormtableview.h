#ifndef QORMTABLEVIEW_H
#define QORMTABLEVIEW_H

#include <QTableView>
#include <table.h>
#include <QHeaderView>

class QOrmTableView : public QTableView
{
    Q_OBJECT
public:
    explicit QOrmTableView(QWidget *parent = 0);
    void setModel ( BaseCollection* model );
    bool addSearchField(QLineEdit* widget, QString field);
    BaseCollection* model() const{return m_model;}
    void reload();
signals:
    
public slots:
    void updateTable();

protected:
    QMap<QLineEdit*, QString> searchFields;
    BaseCollection* m_model;
    
};


#endif // QORMTABLEVIEW_H
