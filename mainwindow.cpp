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

   /* Patient::find(0)->name();

    Patient n = Patient::first();*/
    Patient p;
    //qDebug() << p.find(0)->name();
    //qDebug() << p.find<Patient>(0)->vorname();

    //Patient p = Patient::all()->first();
    //Queryset* q = Patient::all();



    //qDebug() << q->getQuery();
    //qDebug() << p.metaObject()->className();

    //Patient p2=p1.all();

            // Patient* n = p.all()->all();


}

MainWindow::~MainWindow()
{
    delete ui;
}

