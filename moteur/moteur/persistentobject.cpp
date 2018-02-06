#include "persistentobject.h"
#include <QtSql>
#include "livre.h"
#include <iostream>
//using namespace std;

PersistentObject::PersistentObject(QString className)
{
    this->table=new QString(className);
    this->id=0;
}

bool PersistentObject::createConnection(){
    db = QSqlDatabase::database(this->dbName);
    if(this->dbName == NULL){
        return false;
    }
    if(!db.open()){
        std::cout<< "Unable to open the database" << std::endl;
        return false;
    }
    QSqlQuery query(db);
    QString sqlStatement = "CREATE TABLE IF NOT EXISTS ";
    sqlStatement += *table+" (key INTEGER PRIMARY KEY";
    for(PersistentAttribute *p:attributes){
        sqlStatement += ","+ p->name+" "+this->getSQLType(p->type);
    }
    sqlStatement += ");";
    query.prepare(sqlStatement);
    if(!query.exec()){
        std::cout << "Error updating element" <<std::endl;
        qDebug()<< query.lastError();
        return false;
    }
    return true;
}

void PersistentObject::addAttribute(PersistentAttribute *attribute) {
    attributes.append(attribute);
}

/* QVariant::type - Value - SQL type
 * Int - 2 - INT
 * QString - 10 - TEXT
 * Float - 38 -
 * QStringList - 11 -
 * */
QString PersistentObject::getSQLType(QVariant::Type t){
    switch(t){
    case QVariant::Int:
        return QString("INTEGER");
    case QVariant::String:
        return QString("TEXT");
    case QVariant::Double:
        return QString("REAL");
    case QVariant::StringList:
        return QString("TEXT");
    default:
        return QString("BLOB");
    }
    return NULL;
}

QString PersistentObject::getDataToString(PersistentAttribute *p){
    switch(p->type){
    case QVariant::Int:
        return QString::number(*(int*)(p->data));
    case QVariant::String:
        return QString(*(QString*)(p->data));
//    case QVariant::Double:
//        return QString(*(double*)(p->data))
    case QVariant::StringList:
        return QString((*(QStringList*)(p->data)).join("/"));
    default:
        return QString("BLOB");
    }
}

int PersistentObject::save() {
    int result = 0;
    if(this->createConnection()){
        if(this->id==0){
            result=this->insert();
        } else{
            this->update();
            result=this->id;
        }
    }
//    if(db.isOpen()){
//        db.close();
//    }
    return result;
}

bool PersistentObject::update(){
    QSqlQuery query(db);
    QString sqlStatement = "UPDATE ";
    sqlStatement += *table;
    sqlStatement += " SET ";
    bool first = true;
    for(PersistentAttribute *p:attributes){
        if(first){
            sqlStatement+=p->name+"=:"+p->name;
            first=false;
        } else {
            sqlStatement += ","+ p->name +"=:"+p->name;
        }
    }
    sqlStatement += " WHERE key="+QString::number(this->id)+";";
    query.prepare(sqlStatement);
    for (PersistentAttribute *p : attributes){
        query.bindValue(":"+p->name,this->getDataToString(p));
    }
    if(!query.exec()){
        std::cout << "Error updating element" <<std::endl;
        qDebug()<< query.lastError();
        return false;
    }

    return true;
}

int PersistentObject::insert(){
    QSqlQuery query(db);
    QString sqlStatement = "INSERT INTO ";
    sqlStatement += *table +" (";
    bool first = true;
    for(PersistentAttribute *p:attributes){
        if(first){
            sqlStatement += p->name;
            first=false;
        } else {
            sqlStatement += ","+p->name;
        }
    }
    sqlStatement += ") VALUES (";
    first = true;
    for(PersistentAttribute *p:attributes){
        if(first){
            sqlStatement += ":"+p->name;
            first=false;
        } else {
            sqlStatement += ",:"+p->name;
        }
    }
    sqlStatement += ");";
    query.prepare(sqlStatement);
    for (PersistentAttribute *p : attributes){
        query.bindValue(":"+p->name,this->getDataToString(p));
    }
    if(!query.exec()){
        std::cout << "Error inserting element" <<std::endl;
        qDebug()<< query.lastError();
        return -1;
    }
    int i = query.lastInsertId().toInt();
    return i;
}


bool PersistentObject::delet(){
    if(this->createConnection()){

        QSqlQuery query(db);
        QString sqlStatement = "DELETE FROM ";
        sqlStatement += *table +" WHERE key=:key;";
        query.prepare(sqlStatement);
        query.bindValue(":key",this->getID());
        if(!query.exec()){
            std::cout << "Error deleting element" <<std::endl;
            qDebug()<< query.lastError();
            return false;
        }
        return true;
    }
    return true;
}

int PersistentObject::getID(){
    return this->id;
}

void PersistentObject::setID(int i){
    this->id=i;
}

void PersistentObject::setDBName(QString na){
    this->dbName=na;
}
