#ifndef BUCKET_OBJECT_H_
#define BUCKET_OBJECT_H_

#include "Vector3.h"

struct BucketObject
{
    enum BUCKET_TYPE
    {
        BT_WATER,
        BT_TOTAL
    };

    BUCKET_TYPE type;
    Vector3 pos;
    Vector3 vel;
    Vector3 scale;
    Vector3 dir;
    bool active;
    float mass;

    BucketObject(BUCKET_TYPE typeValue = BT_WATER);
    ~BucketObject();

};

#endif