#ifndef POTATO_OBJECT_H
#define POTATO_OBJECT_H

#include "Vector3.h"
#include "Time.h"

struct PotatoObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;
	bool fullyGrown;
	Time growing;
	Time timeToFullyGrow;

	PotatoObject();
	~PotatoObject();
};

#endif