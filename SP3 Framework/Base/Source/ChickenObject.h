#ifndef CHICKEN_OBJECT_H
#define CHICKEN_OBJECT_H

#include "Vector2.h"
#include "Vector3.h"
#include "GameObject.h"
#include "TileIndex.h"
#include "TileMap.h"
#include "Player.h"

class ChickenObject : public GameObject
{
public:
	enum CHICKEN_STATES
	{
		IDLE,
		WALKING,
		RUNNING,
		TOTAL_STATES,
	};

	enum DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};


	ChickenObject();
	~ChickenObject();

	//Getters and Setters
	void setPlayer(Player& player);
	void setTileMap(TileMap& tilemap);
	void setCurrentState(CHICKEN_STATES changeState);
	void setDirection(DIRECTION newDirection);
	void setPosition(Vector3 position);
	void setScale(Vector3 scale);
	void setVelocity(Vector3 velocity);
	void setTime(float newTime);
	void setActive(bool newActive);
	void setInvert(bool isInverted);

	CHICKEN_STATES getCurrentState();
	DIRECTION getDirection();
	Vector3 getPosition();
	Vector3 getScale();
	Vector3 getVelocity();
	float getTime();
	bool getActive();
	bool getInvert();

	bool CheckUp();
	bool CheckDown();
	bool CheckRight();
	bool CheckLeft();
	void movementUpdate(const double& deltaTime);

private:

	TileMap* tileMap;
	Player* player;

	CHICKEN_STATES currentState;
	DIRECTION direction;
	Vector3 pos;
	Vector3 scale;
	Vector3 vel;
	float time;
	bool active;
	float hotspotOffset;


};

#endif