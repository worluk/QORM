#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qorm.h>
#include "tbl_patient.h"
#include "tbl_doctor.h"



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

//    Patient* t = new Patient;
//    t->setid(QString("3"));
//    qDebug() << t->setProperty("id","4");
//    //qDebug() << t->id();

    Patient* n = Patient::generate("Engel","Tobias");

    qDebug() << n->vorname() << n->name();

    //returns a collection<Patient>
   // Collection<Patient> p = Patient::all()->find(QString("name like 'blub'"));
   // Collection <Patient>* p = Patient::all();

    Collection<Patient>* patients = Patient::all();
    Patient* p = Patient::all()->find(0);

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

