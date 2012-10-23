#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qorm.h>
#include "tbl_patient.h"
#include "tbl_doctor.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Qorm* db = new Qorm("QSQLITE");

    db->setDatabaseName("test.db");

    db->open();

    db->registerTable<Patient>();
    db->registerTable<Doctor>();

   /* Patient* n = Patient::build("Engel","Tobias");
    n->save();

    n->destroy();

    Patient* g = Patient::build("Testor", "Elmo");
    g->setname("Blub");
    g->save();

    Patient* s = Patient::all()->find(25);
    qDebug() << s->name() << s->vorname();

    g->setname("Elmo");
    g->save();

    qDebug() << "updated_at" << g->updated_at();
    qDebug() << g->name();

*/
    Collection<Patient> patients;//=Patient::all();
    patients=Patient::all();

    for(int i=0; i<patients.length();i++)
        qDebug() << patients[i]->name() << patients[i]->vorname();
  /*  Patient* p = Patient::all()->find(0);

    Patient::all()->find(QString("name like 'blub'"));

    Patient::all()->find(0)->debugQuery();
    Patient::all()->first()->debugQuery();
    Patient::all()->last()->debugQuery();
    Patient::all()->find(QString("name like 'blub'"))->debugQuery();
    Patient::all()->find(QString("age"), 12)->debugQuery();
    Patient::all()->find(QString("street"), QString("Elmstreet"))->debugQuery();
    Patient::all()->limit(2, 3)->debugQuery();
    Patient::all()->limit(4)->debugQuery();
    Patient::all()->order(QString("name"))->debugQuery();
    Patient::all()->order(QString("vorname"), Q_DESC)->debugQuery();
    Patient::all()->find(QString("name"), "Test")->limit(3)->order(QString("vorname"))->debugQuery();
   // Patient::all()  //collection
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

