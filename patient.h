#ifndef PATIENT_H
#define PATIENT_H
#include <QObject>
#include <table.h>
#include <doctor.h>
/*
#define PatientAccessor patient

QOrmModel(Patient)
{

    QOrmOrganizer()
    QOrmModelField(name, "varchar(255)")
    QOrmModelBelongsTo(Doctor)
};
*/

class Patient : public QObject, public Table<Patient>
{

};
#endif // PATIENT_H
