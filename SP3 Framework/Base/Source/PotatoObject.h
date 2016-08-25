#ifndef POTATO_OBJECT_H
#define POTATO_OBJECT_H

#include "Vector3.h"

struct PotatoObject
{
	Vector3 pos;
	Vector3 scale;

	bool active;

	PotatoObject();
	~PotatoObject();
};

#endif