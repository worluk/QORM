QORMModelReferences(Doctor)

QOrmModel(Patient)
{
    QOrmOrganizer(Patient)
    QOrmModelField(name, QString, )
	QOrmModelField(vorname, QString, )
    QOrmModelBelongsTo(Doctor, doctor)
};

