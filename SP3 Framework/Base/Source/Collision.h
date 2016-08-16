#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"

bool LineSphereCollide(Vector3 lineSource, Vector3 lineDirection, float lineLength, Vector3 spherePosition, float sphereRadius);

#endif