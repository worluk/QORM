#ifndef DOCTOR_H
#define DOCTOR_H

#include "../macros.h"

#define DoctorAccessor doctor

QOrmModel(Doctor)
{
    QOrmOrganizer(Doctor)
    QOrmModelField(name, "varchar(255)")

};

#endif // DOCTOR_H
