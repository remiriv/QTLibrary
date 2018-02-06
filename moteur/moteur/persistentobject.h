#ifndef PERSISTANTOBJECT_H
#define PERSISTANTOBJECT_H

#include <QList>
#include <QtSql>
#include "persistentattribute.h"

class PersistentObject
{
private:
    QSqlDatabase db;
    QList<PersistentAttribute *> attributes;
    QString *table;
    int id;
//    void* getAttributeDataForName(QString);
    QString getSQLType(QVariant::Type);
    QString getDataToString(PersistentAttribute*);
//    QVariant getQtType(QString);
    bool createConnection();
    bool createTable();
    bool update();
    int insert();
    QString dbName;

public:
    PersistentObject(QString);
    void addAttribute(PersistentAttribute *);
    int save();
    bool delet();
    int getID();
    void setID(int);
    void setDBName(QString);
};

#endif // PERSISTANTOBJECT_H
