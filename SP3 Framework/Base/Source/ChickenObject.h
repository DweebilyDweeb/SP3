#ifndef CHICKEN_OBJECT_H
#define CHICKEN_OBJECT_H

#include "Vector3.h"
#include "GameObject.h"
#include "TileIndex.h"
#include "TileMap.h"
#include <vector>

struct ChickenObject
{
	enum CHICKEN_STATES
	{
		IDLE,
		WALKING,
		RUNNING,
		TOTAL_STATES,
	};

	std::vector<TILE_TYPE> collidable;

	CHICKEN_STATES CS;
	Vector3 pos;
	Vector3 scale;
	Vector3 vel;
	float changeState;
	bool moving;
	bool active;
	bool isInvert;
	float OffSet = 0.495f;

	ChickenObject();
	~ChickenObject();

	bool CheckUp(TileMap);
	bool CheckDown(TileMap);
	bool CheckRight(TileMap);
	bool CheckLeft(TileMap);
	void movementUpdate(const double& deltaTime, Vector3 playerpos, TileMap);
};

#endif