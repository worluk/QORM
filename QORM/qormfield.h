#ifndef QORMFIELD_H
#define QORMFIELD_H

class QORMField
{
public:
    QORMField(QString n, QString d) {name=n; displayName=d;}
    QString key() const{return name;}
    QString value() const{return displayName;}
private:
    QString name;
    QString displayName;
};

#endif // QORMFIELD_H
