#include "ChickenObject.h"
#include "Vector2.h"
#include "PlayerSS.h"

ChickenObject::ChickenObject() :
CS(IDLE),
pos(0, 0, 1),
scale(1, 1, 1),
vel(0, 0, 0),
changeState(0),
active(false),
isInvert(false)
{
	collidable.push_back(TILE_FENCE);
}

ChickenObject::~ChickenObject()
{
	
}

void ChickenObject::movementUpdate(const double& deltaTime, Vector3 playerpos, TileMap tileMap)
{
	switch (CS)
	{
	case IDLE:
	{
				 vel.SetZero();
				 break;
	}
	case WALKING:
	{
	  /*  vel.Set(Math::RandFloatMinMax(-4.f, 4.f) * (float)deltaTime, Math::RandFloatMinMax(-4.f, 4.f) * (float)deltaTime, 0);
	    pos += vel;*/
	    break;
	}
    case RUNNING:
    {
        break;
        //	Vector2 collisionOffset;
        //	collisionOffset.x = (tileMap.GetTileSize() - scale.x) * 0.5f;
        //	collisionOffset.y = (tileMap.GetTileSize() - scale.y) * 0.5f;

        //	int tileX = tileMap.GetTileX(pos.x);
        //	int tileY = tileMap.GetTileY(pos.y);

        //	Vector3 maxSpeed(75, 75, 0);
        //	Vector3 maxSpeedN(-75, -75, 0);
        //	Vector3 minSpeed(0, 0, 0);
        //	
        //	Vector3 temp;

        //	Vector3 direction = playerpos - pos;
        //	direction.z = 0;
        //	
        //	if (direction.LengthSquared() > 10.f)
        //	{
        //		CS = IDLE;
        //		break;
        //	}

        //	/*if (direction.x > 0)
        //	{
        //		temp.x = maxSpeed.x - direction.x;
        //		if (direction.y > 0)
        //			temp.y = maxSpeed.y - direction.y;
        //		else
        //			temp.y = maxSpeedN.y + direction.y;
        //	}
        //	else
        //	{
        //		temp.x = maxSpeedN.x + direction.x;
        //		if (direction.y > 0)
        //			temp.y = maxSpeed.y - direction.y;
        //		else
        //			temp.y = maxSpeedN.y + direction.y;
        //	}*/

        //	/*if (direction.x > 0)
        //		direction.x = Math::Wrap(direction.x, -10.f, -1.f);
        //	else
        //		direction.x = Math::Wrap(direction.x, 1.f, 10.f);

        //	if (direction.y > 0)
        //		direction.y = Math::Wrap(direction.y, -10.f, -1.f);
        //	else
        //		direction.y = Math::Wrap(direction.y, 1.f, 10.f);*/

        //	vel.y = temp.y * (float)deltaTime;

        //	if (vel.y > 0) {
        //		if (CheckUp(tileMap)) {
        //			pos.y = (tileY * tileMap.GetTileSize() + collisionOffset.y) * (float)deltaTime;
        //			vel.y = 0;
        //		}
        //	}
        //	else {
        //		if (CheckDown(tileMap)) {
        //			pos.y = (tileY * tileMap.GetTileSize() - collisionOffset.y) * (float)deltaTime;
        //			vel.y = 0;
        //		}
        //	}

        //	vel.x = temp.x* (float)deltaTime;
        //	if (vel.x > 0) {
        //		if (CheckRight(tileMap)) {
        //			pos.x = (tileX * tileMap.GetTileSize() + collisionOffset.x) * (float)deltaTime;
        //			vel.x = 0;
        //		}
        //	}
        //	else {
        //		if (CheckLeft(tileMap)) {
        //			pos.x = (tileX * tileMap.GetTileSize() - collisionOffset.x) * (float)deltaTime;
        //			vel.x = 0;
        //		}
        //	}
        //	if (vel.x < 0)
        //		isInvert = true;
        //	else
        //		isInvert = false;
        //	pos += vel * (float)deltaTime;
        //	break;
        //}
        //default:
        //	break;
        //}
    }
	default:
		break;
	}
}

bool ChickenObject::CheckUp(TileMap tileMap)
{
	Vector3 pointA(pos.x - (scale.x * OffSet), pos.y + (scale.y * 0.5f), 0);
	int tileX = tileMap.GetTileX(pointA.x);
	int tileY = tileMap.GetTileY(pointA.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}

	Vector3 pointB(pos.x + (scale.x * OffSet), pos.y + (scale.y * 0.5f), 0);
	tileX = tileMap.GetTileX(pointB.x);
	tileY = tileMap.GetTileY(pointB.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}
}
bool ChickenObject::CheckDown(TileMap tileMap)
{
	Vector3 pointA(pos.x - (scale.x * OffSet), pos.y - (scale.y * 0.5f), 0);
	int tileX = tileMap.GetTileX(pointA.x);
	int tileY = tileMap.GetTileY(pointA.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}
	Vector3 pointB(pos.x + (scale.x * OffSet), pos.y - (scale.y * 0.5f), 0);
	tileX = tileMap.GetTileX(pointB.x);
	tileY = tileMap.GetTileY(pointB.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}

}
bool ChickenObject::CheckLeft(TileMap tileMap)
{

	Vector3 pointA(pos.x - (scale.x * OffSet), pos.y + (scale.y * 0.5f), 0);
	int tileX = tileMap.GetTileX(pointA.x);
	int tileY = tileMap.GetTileY(pointA.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}

	Vector3 pointB(pos.x - scale.x * 0.5f, pos.y - (scale.y * OffSet), 0);
	//The reason we +0.5f is because we need to round off the number.
	tileX = tileMap.GetTileX(pointB.x);
	tileY = tileMap.GetTileY(pointB.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}

}
bool ChickenObject::CheckRight(TileMap tileMap)
{
	Vector3 pointA(pos.x + (scale.x * 0.5f), pos.y + (scale.y * OffSet), 0);
	int tileX = tileMap.GetTileX(pointA.x);
	int tileY = tileMap.GetTileY(pointA.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}

	Vector3 pointB(pos.x + (scale.x * 0.5f), pos.y - (scale.y * OffSet), 0);
	tileX = tileMap.GetTileX(pointB.x);
	tileY = tileMap.GetTileY(pointB.y);

	for (size_t i = 0; i < collidable.size(); ++i) {
		if (collidable[i] == tileMap.map[tileY][tileX]) {
			return true;
		}
	}
}