#include "bibliotheque.h"

Bibliotheque::Bibliotheque(QString nom)
{
    this->nom=nom;

}

void Bibliotheque::delLivre(int pos){
    livres.removeAt(pos);
}

void Bibliotheque::addLivre(Livre livre){
    livres.append(livre);
}

QList<Livre> Bibliotheque::getLivres(){
    return this->livres;
}
