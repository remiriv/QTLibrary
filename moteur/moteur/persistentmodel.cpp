#include "persistentmodel.h"
#include <QtSql>
#include <iostream>
#include "livre.h"

PersistentModel::PersistentModel() {}

bool PersistentModel::createConnection(QString dbName, QString path){
    db = QSqlDatabase::addDatabase("QSQLITE",dbName);
    db.setDatabaseName(path+dbName+".db");
    if(!db.open()){
        std::cout<< "Unable to open the database in model" << std::endl;
        return false;
    }
    return true;
}

QList<PersistentObject*> PersistentModel::load(QString dbName, QString className, QString path){
    QList<PersistentObject*> objets;
    if(this->createConnection(dbName,path)){
        QSqlQuery query(db);
        QString sqlStatement = "SELECT ";
        if(className=="livre"){
            sqlStatement += "key, auteurs, titre, ISBN, annee FROM livre;";
            query.prepare(sqlStatement);
            if(!query.exec()){
                std::cout << "Error selecting element" <<std::endl;
                qDebug()<< query.lastError();
            } else{
                while(query.next()){
                    Livre *l = new Livre(query.value("auteurs").toString().split("/"),query.value("titre").toString(),query.value("ISBN").toString(),query.value("annee").toInt());
                    l->setID(query.value("key").toInt());
                    l->setDBName(dbName);
                    objets.append(l);
                }
            }
         }
    }
//    if(db.isOpen()){
//        db.close();
//    }

    return objets;
}

bool PersistentModel::createDatabase(QString name,QString path){
    if(this->createConnection(name,path)){
//        if(db.isOpen()){
//            db.close();
//        }
        return false;
    }
    return true;
}
