#ifndef PATIENT_H
#define PATIENT_H

#include "../macros.h"
//#include "tables/tbl_doctor.h"
#define PatientAccessor patient

QOrmModel(Patient)
{
    QOrmOrganizer(Patient)
    QOrmModelField(name, "varchar(255)")
   // QOrmModelBelongsTo(Doctor)


};

#endif

