#ifndef CORN_OBJECT_H
#define CORN_OBJECT_H

#include "Vector3.h"
#include "Time.h"

struct CornObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;
	bool fullyGrown;
	Time growing;
	Time timeToFullyGrow;

	CornObject();
	~CornObject();
};

#endif