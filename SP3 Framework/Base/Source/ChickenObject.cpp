#include "ChickenObject.h"

ChickenObject::ChickenObject() :
currentState(IDLE),
direction(LEFT),
pos(0, 0, -1),
scale(1, 1, 1),
vel(0, 0, 0),
time(0),
active(true),
hotspotOffset(0.495f)
{
	pos = Vector3(Math::RandIntMinMax(5, 25), Math::RandIntMinMax(3, 16), -1);
	int temp = Math::RandIntMinMax(0, 1);
	switch (temp)
	{
	case 0:
		currentState = IDLE;
		break;
	case 1:
		currentState = WALKING;
		break;
	default:
		break;
	}
}

ChickenObject::~ChickenObject()
{
	
}

void ChickenObject::setPlayer(Player& player)
{
	this->player = &player;
}

void ChickenObject::setTileMap(TileMap& tilemap)
{
	this->tileMap = &tilemap;
}

void ChickenObject::setCurrentState(CHICKEN_STATES newState)
{
	currentState = newState;
}

void ChickenObject::setDirection(DIRECTION direction)
{
	this->direction = direction;
}

void ChickenObject::setPosition(Vector3 pos)
{
	this->pos = pos;
}

void ChickenObject::setScale(Vector3 scale)
{
	this->scale = scale;
}

void ChickenObject::setVelocity(Vector3 velocity)
{
	vel = velocity;
}

void ChickenObject::setTime(float newTime)
{
	time = newTime;
}

void ChickenObject::setActive(bool active)
{
	this->active = active;
}

ChickenObject::CHICKEN_STATES ChickenObject::getCurrentState()
{
	return currentState;
}

ChickenObject::DIRECTION ChickenObject::getDirection()
{
	return direction;
}

Vector3 ChickenObject::getPosition()
{
	return pos;
}

Vector3 ChickenObject::getScale()
{
	return scale;
}

Vector3 ChickenObject::getVelocity()
{
	return vel;
}

float ChickenObject::getTime()
{
	return time;
}

bool ChickenObject::getActive()
{
	return active;
}

void ChickenObject::movementUpdate(const double& deltaTime)
{
	Vector2 collisionOffset;
	collisionOffset.x = (tileMap->GetTileSize() - scale.x) * 0.5f;
	collisionOffset.y = (tileMap->GetTileSize() - scale.y) * 0.5f;

	int tileX = tileMap->GetTileX(pos.x);
	int tileY = tileMap->GetTileY(pos.y);


	time += (float)deltaTime;
	if (time > Math::RandFloatMinMax(0.f, 3.f) && currentState == IDLE)
	{
		currentState = WALKING;
		vel.Set(Math::RandFloatMinMax(-2.f, 2.f), Math::RandFloatMinMax(-2.f, 2.f), 0);
		time = 0.f;
	}
	else if (time > Math::RandFloatMinMax(0.f, 3.f) && currentState == WALKING)
	{
		currentState = IDLE;
		vel.SetZero();
		time = 0.f;
	}
	if (currentState == RUNNING)
	{
		Vector3 temp = player->transform.position - pos;
		temp.z = 0;
		temp = temp.Normalized();

		vel = temp * Math::RandFloatMinMax(-4.f, 4.f);
		currentState = IDLE;
	}

	if (vel.x < 0)
	{
		if (abs(vel.x) > abs(vel.y))
		{
			direction = LEFT;
		}
		else if (abs(vel.x) < abs(vel.y))
		{
			if (vel.y > 0)
				direction = UP;
			else if (vel.y < 0)
				direction = DOWN;
		}


		if (CheckLeft()) 
		{
			pos.x = (tileX * tileMap->GetTileSize() - collisionOffset.x);
		}

	}
	else if (vel.x > 0)
	{
		if (abs(vel.x) > abs(vel.y))
		{
			direction = RIGHT;
		}
		else if (abs(vel.x) < abs(vel.y))
		{
			if (vel.y > 0)
				direction = UP;
			else if (vel.y < 0)
				direction = DOWN;
		}

		if (CheckRight()) 
		{
			pos.x = (tileX * tileMap->GetTileSize() + collisionOffset.x);
		}
	}
	if (vel.y < 0)
	{
		if (abs(vel.x) < abs(vel.y))
		{
			direction = DOWN;
		}
		else if (abs(vel.x) > abs(vel.y))
		{
			if (vel.x > 0)
				direction = RIGHT;
			else if (vel.y < 0)
				direction = LEFT;
		}
		if (CheckDown())
		{
			pos.y = (tileY * tileMap->GetTileSize() + collisionOffset.y);
		}
	}
	else if (vel.y > 0)
	{
		if (abs(vel.x) < abs(vel.y))
		{
			direction = UP;
		}
		else if (abs(vel.x) > abs(vel.y))
		{
			if (vel.x > 0)
				direction = RIGHT;
			else if (vel.y < 0)
				direction = LEFT;
		}
		if (CheckUp())
		{
			pos.y = (tileY * tileMap->GetTileSize() + collisionOffset.y);
		}
	}

	pos += vel * (float)deltaTime;

	//switch (currentState)
	//{
	//case IDLE:
	//{
	//	
	//	break;
	//}
	//case WALKING:
	//{
	//  /*  vel.Set(Math::RandFloatMinMax(-4.f, 4.f) * (float)deltaTime, Math::RandFloatMinMax(-4.f, 4.f) * (float)deltaTime, 0);
	//    pos += vel;*/
	//    break;
	//}
 //   case RUNNING:
 //   {
 //       break;
 //       //	Vector2 collisionOffset;
 //       //	collisionOffset.x = (tileMap->GetTileSize() - scale.x) * 0.5f;
 //       //	collisionOffset.y = (tileMap->GetTileSize() - scale.y) * 0.5f;

 //       //	int tileX = tileMap->GetTileX(pos.x);
 //       //	int tileY = tileMap->GetTileY(pos.y);

 //       //	Vector3 maxSpeed(75, 75, 0);
 //       //	Vector3 maxSpeedN(-75, -75, 0);
 //       //	Vector3 minSpeed(0, 0, 0);
 //       //	
 //       //	Vector3 temp;

 //       //	Vector3 direction = playerpos - pos;
 //       //	direction.z = 0;
 //       //	
 //       //	if (direction.LengthSquared() > 10.f)
 //       //	{
 //       //		CS = IDLE;
 //       //		break;
 //       //	}

 //       //	/*if (direction.x > 0)
 //       //	{
 //       //		temp.x = maxSpeed.x - direction.x;
 //       //		if (direction.y > 0)
 //       //			temp.y = maxSpeed.y - direction.y;
 //       //		else
 //       //			temp.y = maxSpeedN.y + direction.y;
 //       //	}
 //       //	else
 //       //	{
 //       //		temp.x = maxSpeedN.x + direction.x;
 //       //		if (direction.y > 0)
 //       //			temp.y = maxSpeed.y - direction.y;
 //       //		else
 //       //			temp.y = maxSpeedN.y + direction.y;
 //       //	}*/

 //       //	/*if (direction.x > 0)
 //       //		direction.x = Math::Wrap(direction.x, -10.f, -1.f);
 //       //	else
 //       //		direction.x = Math::Wrap(direction.x, 1.f, 10.f);

 //       //	if (direction.y > 0)
 //       //		direction.y = Math::Wrap(direction.y, -10.f, -1.f);
 //       //	else
 //       //		direction.y = Math::Wrap(direction.y, 1.f, 10.f);*/

 //       //	vel.y = temp.y * (float)deltaTime;

 //       //	if (vel.y > 0) {
 //       //		if (CheckUp(tileMap)) {
 //       //			pos.y = (tileY * tileMap->GetTileSize() + collisionOffset.y) * (float)deltaTime;
 //       //			vel.y = 0;
 //       //		}
 //       //	}
 //       //	else {
 //       //		if (CheckDown(tileMap)) {
 //       //			pos.y = (tileY * tileMap->GetTileSize() - collisionOffset.y) * (float)deltaTime;
 //       //			vel.y = 0;
 //       //		}
 //       //	}

 //       //	vel.x = temp.x* (float)deltaTime;
 //       //	if (vel.x > 0) {
 //       //		if (CheckRight(tileMap)) {
 //       //			pos.x = (tileX * tileMap->GetTileSize() + collisionOffset.x) * (float)deltaTime;
 //       //			vel.x = 0;
 //       //		}
 //       //	}
 //       //	else {
 //       //		if (CheckLeft(tileMap)) {
 //       //			pos.x = (tileX * tileMap->GetTileSize() - collisionOffset.x) * (float)deltaTime;
 //       //			vel.x = 0;
 //       //		}
 //       //	}
 //       //	if (vel.x < 0)
 //       //		isInvert = true;
 //       //	else
 //       //		isInvert = false;
 //       //	pos += vel * (float)deltaTime;
 //       //	break;
 //       //}
 //       //default:
 //       //	break;
 //       //}
 //   }
	//default:
	//	break;
	//}
}

bool ChickenObject::CheckUp()
{
	Vector3 pointA(pos.x - (scale.x * hotspotOffset), pos.y + (scale.y * 0.5f), 0);
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}
	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}
	// Find player's tile location
	Vector3 pointPA(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y + (player->transform.scale.y * hotspotOffset), 0);
	int tilePX = tileMap->GetTileX(pointPA.x);
	int tilePY = tileMap->GetTileY(pointPA.y);

	// Check if cow right is player
	if (tileY == tilePY && tileX == tilePX)
		return true;

	Vector3 pointB(pos.x + (scale.x * hotspotOffset), pos.y + (scale.y * 0.5f), 0);
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}
	return false;
	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}

	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y + (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);

	if (tileY == tilePY && tileX == tilePX)
		return true;
}
bool ChickenObject::CheckDown()
{
	Vector3 pointA(pos.x - (scale.x * hotspotOffset), pos.y - (scale.y * 0.5f), 0);
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}
	// Find player's tile location
	Vector3 pointPA(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y - (player->transform.scale.y * hotspotOffset), 0);
	int tilePX = tileMap->GetTileX(pointPA.x);
	int tilePY = tileMap->GetTileY(pointPA.y);

	// Check if cow right is player
	if (tileY == tilePY && tileX == tilePX)
		return true;

	Vector3 pointB(pos.x + (scale.x * hotspotOffset), pos.y - (scale.y * 0.5f), 0);
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}
	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y - (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);

	if (tileY == tilePY && tileX == tilePX)
		return true;

	return false;

}
bool ChickenObject::CheckLeft()
{

	Vector3 pointA(pos.x - scale.x * 0.5f, pos.y + (scale.y * hotspotOffset), 0);
	//The reason we +0.5f is because we need to round off the number.
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}
	// Find player's tile location
	Vector3 pointPA(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y + (player->transform.scale.y * hotspotOffset), 0);
	int tilePX = tileMap->GetTileX(pointPA.x);
	int tilePY = tileMap->GetTileY(pointPA.y);

	// Check if cow right is player
	if (tileY == tilePY && tileX == tilePX)
		return true;

	Vector3 pointB(pos.x - scale.x * 0.5f, pos.y - (scale.y * hotspotOffset), 0);
	//The reason we +0.5f is because we need to round off the number.
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//We are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}
	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y - (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);

	if (tileY == tilePY && tileX == tilePX)
		return true;

	return false;

}
bool ChickenObject::CheckRight()
{
	Vector3 pointA(pos.x + (scale.x * 0.5f), pos.y + (scale.y * hotspotOffset), 0);
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}
	// Find player's tile location
	Vector3 pointPA(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y + (player->transform.scale.y * hotspotOffset), 0);
	int tilePX = tileMap->GetTileX(pointPA.x);
	int tilePY = tileMap->GetTileY(pointPA.y);

	// Check if cow right is player
	if (tileY == tilePY && tileX == tilePX)
		return true;

	Vector3 pointB(pos.x + (scale.x * 0.5f), pos.y - (scale.y * hotspotOffset), 0);
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//We are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	}
	else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	if (tileMap->map[tileY][tileX] == 4) {
		return true;
	}
	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y - (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);

	if (tileY == tilePY && tileX == tilePX)
		return true;

	return false;
}