#ifndef FISH_OBJECT_H_
#define FISH_OBJECT_H_

#include "Vector3.h"

struct FishObject
{
	enum FISH_TYPE
	{
		FT_TROUT,
		FT_TOTAL
	};

	FISH_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 dir;
	bool active;
	float rotation;
	float mass;
	float timeAlive;

	FishObject(FISH_TYPE typeValue = FT_TROUT);
	~FishObject();

};

#endif