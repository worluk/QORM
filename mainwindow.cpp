#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qorm.h>
#include "tbl_Patient.h"
#include "tbl_Doctor.h"

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


    Patient* p = Patient::all()->first();
    Doctor* d = Doctor::all()->first();

    Collection<Patient> patients;
    patients=d->patients();

    for(int i=0; i<patients.length();i++)
        qDebug() << patients[i]->name() << patients[i]->vorname() << patients[i]->created_at();


}

MainWindow::~MainWindow()
{
    delete ui;
}

