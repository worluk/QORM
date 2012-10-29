#include <QHeaderView>
#include <QLineEdit>
#include <QStandardItem>
#include "qormtableview.h"


QOrmTableView::QOrmTableView(QWidget *parent) :
    QTableView(parent)
{
   setSelectionMode(QAbstractItemView::SingleSelection);
   setSelectionBehavior(QAbstractItemView::SelectRows);
   setShowGrid(false);
  // verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
   //horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

void QOrmTableView::setModel( BaseCollection* model )
{
    model->exec();
    m_model = model;
    QTableView::setModel(model);
    horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}


bool QOrmTableView::addSearchField(QLineEdit* widget, QString field)
{
    if(searchFields.contains(widget))
        return false;

    searchFields.insert(widget, field);
    return true;
}

void QOrmTableView::updateTable()
{
    BaseCollection* c = (BaseCollection*)model();
    QMap<QLineEdit*, QString>::iterator i;
    QStringList conditions;

    for(i=searchFields.begin(); i!=searchFields.end(); ++i)
    {
        if(i.key()->text() != "")
        conditions << i.value() + QString(" like '%") + i.key()->text() + QString("%'");
    }

    QString w;
    if(conditions.size())
        w = QString(" WHERE ")+ conditions.join(" and ");
    else
        w = conditions.join(" and ");

    c->update(w);


}

void QOrmTableView::reload()
{
    model()->reload();
}


