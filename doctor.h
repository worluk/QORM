QORMModelReferences(Patient)

QOrmModel(Doctor)
{
    QOrmOrganizer(Doctor)
    QOrmModelField(name, QString,)
	QOrmModelHasMany(Patient, patients)

};

