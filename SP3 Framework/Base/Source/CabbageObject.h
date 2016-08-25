#ifndef CABBAGE_OBJECT_H
#define CABBAGE_OBJECT_H

#include "Vector3.h"

struct CabbageObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;

	CabbageObject();
	~CabbageObject();
};

#endif