#ifndef PATIENT_H
#define PATIENT_H

#include <table.h>
#include <doctor.h>

#define PatientAccessor patient

QOrmModel(Patient)
{
    QOrmOrganizer(Patient)
    QOrmModelField(name, "varchar(255)")
    QOrmModelBelongsTo(Doctor)


};


#endif // PATIENT_H
