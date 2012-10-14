#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qorm.h>
#include <patient.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

 /*   Gorm* db = new Gorm("QSQLITE");

    db->setDatabaseName("test.db");

    db->open();

    db->registerTable<Patient>();
    db->registerTable<Doctor>();

    //tables["Patient"]->all();
   /// tables["Doctor"]->all();

   // Patient* p = table("Patient")->first();
   // BaseTable<int> t;
*/
 /*   Patient p;
    Patient* n = p.all()->all();
    Doctor* d = n->first()->doctor();
    QString s = d->name();

*/

    Queryset* q = new Queryset;
    Patient p1=q;
    Patient p2=p1.all();

            // Patient* n = p.all()->all();


}

MainWindow::~MainWindow()
{
    delete ui;
}

