#include "mainwindow.h"
#include <QApplication>
#include "livre.h"
#include "persistentmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0,"/home/vincent/git/moteur/");
    w.show();

//    QStringList auteurs;
//    auteurs << "John";
//    QString titre = "titreLivre";
//    QString ISBN = "124";
//    int annee = 121;
//    Livre livreTest(auteurs,titre,ISBN,annee);
//    livreTest.setDBName("moteur2");
//    int s = livreTest.save();
//    printf("Identifiant persistant du livreTest :%i", s);
//    printf("fin");

//    PersistentModel *m = new PersistentModel();
//    QList<PersistentObject*> obj = m->load("moteur2","livre");
//    for(PersistentObject *p:obj){
//        printf("ID du livre :%i \n",p->getID());
//    }
//    fflush(stdout);
    return a.exec();

}
