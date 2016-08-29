#ifndef COOP_OBJECT_H
#define COOP_OBJECT_H

#include "Vector3.h"

struct CoopObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;

	CoopObject();
	~CoopObject();
};

#endif