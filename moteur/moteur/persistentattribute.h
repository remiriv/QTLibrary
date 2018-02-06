#ifndef PERSISTANTATTRIBUTE_H
#define PERSISTANTATTRIBUTE_H

#include <QVariant>

class PersistentAttribute {
public:
    QString name;
    QVariant::Type type;
    void *data;

    PersistentAttribute(QString, QVariant::Type, void*);
};

#endif // PERSISTANTATTRIBUTE_H
