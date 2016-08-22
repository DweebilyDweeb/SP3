#include "BucketObject.h"

BucketObject::BucketObject(BUCKET_TYPE typeValue)
    : type(typeValue),
    pos(10, 10, 3),
    dir(0, 0, 1),
    scale(1, 1, 1),
    active(false),
    mass(1.f)
{
}

BucketObject::~BucketObject()
{
}