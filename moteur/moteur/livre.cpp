#include "livre.h"

int Livre::save() {
    return this->PersistentObject::save();
}

void Livre::addPersistence(){
    this->addAttribute(new PersistentAttribute(QString("auteurs"), (new QVariant(Livre::auteurs))->type(), &auteurs));
    this->addAttribute(new PersistentAttribute(QString("titre"), (new QVariant(Livre::titre))->type(), &titre));
    this->addAttribute(new PersistentAttribute(QString("ISBN"), (new QVariant(Livre::ISBN))->type(), &ISBN));
    this->addAttribute(new PersistentAttribute(QString("annee"), (new QVariant(Livre::annee))->type(), &annee));
}


