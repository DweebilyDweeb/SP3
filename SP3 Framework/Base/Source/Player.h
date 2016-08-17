#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "TileMap.h"
#include "TileIndex.h"
#include "Vector3.h"

class Player : public GameObject {

protected:
	Vector3 velocity;
	vector<TILE_TYPE> collidables;
	vector<TILE_TYPE> collectibles;
    vector<TILE_TYPE> spikes;
    vector<TILE_TYPE> bounce;
    vector<TILE_TYPE> portal;
    vector<TILE_TYPE> flag;
    vector<TILE_TYPE> pole;

	bool CheckIfInsideTileMap();
	bool CheckCollisionLeft();
	bool CheckCollisionRight();
	bool CheckCollisionUp();
	bool CheckCollisionDown();
	
	TileMap* tileMap;

	float hotspotOffset;

	

public:
	Player();
	virtual ~Player();

	virtual void Update(const double& deltaTime);
	void SetTileMap(TileMap& tileMap);
	void RemoveTileMap();

	void SetHotspotOffset(float hotspotOffset = 1.0f);
	float GetHotspotCentre();
    int score;
    int Level;

	enum PLAYER_STATE
	{
		WALKING,
		IDLE,
		JUMPING,
		TOTAL
	};

	PLAYER_STATE playerState = IDLE;
};

#endif