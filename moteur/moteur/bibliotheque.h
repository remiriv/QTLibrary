#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <QString>
#include <QList>
#include "livre.h"

class Bibliotheque
{
private:
    QString nom;
    QList<Livre> livres;

public:
    Bibliotheque(QString);
    void addLivre(Livre);
    void delLivre(int);
    QList<Livre> getLivres();
};

#endif // BIBLIOTHEQUE_H
