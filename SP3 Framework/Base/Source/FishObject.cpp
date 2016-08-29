#include "FishObject.h"

FishObject::FishObject(FISH_TYPE typeValue)
: type(typeValue),
pos(0, 0, 1),
dir(0, 0, 1),
scale(1, 1, 1),
normal(1,0,0),
normal2(1,0,0),
active(false),
invert(false),
mass(1.f),
rotation(0.f),
timeAlive(0.f)
{
}

FishObject::~FishObject()
{
}