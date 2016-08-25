#ifndef CORN_OBJECT_H
#define CORN_OBJECT_H

#include "Vector3.h"

struct CornObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;

	CornObject();
	~CornObject();
};

#endif