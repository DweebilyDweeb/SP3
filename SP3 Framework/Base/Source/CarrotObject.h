#ifndef CARROT_OBJECT_H
#define CARROT_OBJECT_H

#include "Vector3.h"
#include "Time.h"

struct CarrotObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;
	bool fullyGrown;
	Time growing;
	Time timeToFullyGrow;

	CarrotObject();
	~CarrotObject();
};

#endif