#ifndef LIVRE_H
#define LIVRE_H

#include <QString>
#include <QStringList>
#include "persistentobject.h"

class Livre : public PersistentObject
{
private:
    void addPersistence();
public:
    Livre(QStringList auteurs, QString titre, QString ISBN, int annee): PersistentObject(QString("livre")) {
        this->auteurs= auteurs;
        this->titre=titre;
        this->ISBN=ISBN;
        this->annee=annee;
        this->addPersistence();
    }
    int save();
    QStringList auteurs;
    QString titre;
    QString ISBN;
    int annee;};

#endif // LIVRE_H
