#ifndef PERSISTENTMODEL_H
#define PERSISTENTMODEL_H

#include <QtSql>
#include "persistentobject.h"

class PersistentModel
{
private:
    bool createConnection(QString,QString);
public:
    PersistentModel();
    QSqlDatabase db;
    int save();
    QList<PersistentObject*> load(QString,QString,QString);
    bool createDatabase(QString,QString);
};

#endif // PERSISTENTMODEL_H
