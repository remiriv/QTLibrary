#include "persistentattribute.h"
#include <QVariant>


PersistentAttribute::PersistentAttribute(QString name, QVariant::Type type, void *data)
{
    this->name=name;
    this->type=type;
    this->data=data;
}
