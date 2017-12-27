#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "commondefine.h"

#include <QMatrix4x4>

class BaseObject
{
public:
    enum  ObjectType{
        Chunk,
        ObjectTypeCount
    };

public:
    BaseObject(ObjectType type);
    virtual ~BaseObject();

    virtual QMatrix4x4 GetModelMatrix() const = 0;

    ObjectType GetType() const { return type_; }

private:
    ObjectType type_;
};

#endif // BASEOBJECT_H
