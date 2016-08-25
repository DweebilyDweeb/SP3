#ifndef CARROT_OBJECT_H
#define CARROT_OBJECT_H

#include "Vector3.h"

struct CarrotObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;

	CarrotObject();
	~CarrotObject();
};

#endif