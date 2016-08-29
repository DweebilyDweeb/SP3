#include "CowObject.h"
#include "MyMath.h"
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

Cow::Cow(SpriteAnimation* currSA) :
c_timer(0.0),
hotspotOffset(0.495f),
tileMap(nullptr),
isMoving(false),
isRunning(false),
isTriggered(false),
isDead(false),
c_health(2)
{
	scale.Set(2.f, 2.f, 1);
	pos.Set(Math::RandFloatMinMax(4, 26), Math::RandFloatMinMax(4, 16), 0);
	c_timer = (double)Math::RandFloatMinMax(2, 6);
	int temp = Math::RandIntMinMax(0, 7);
	switch (temp) {
	case 0: invert = false; cowFaces = static_cast<COW_DIRECTION>(temp); break;
	case 1: invert = true; cowFaces = static_cast<COW_DIRECTION>(temp); break;
	case 2: invert = false; cowFaces = static_cast<COW_DIRECTION>(temp); break;
	case 3: invert = true; cowFaces = static_cast<COW_DIRECTION>(temp); break;
 	}
	state = new State_Idle();
}

Cow::~Cow() {
	if (state)
		delete state;
}

void Cow::setPosition(const Vector3& pos) {
	this->pos = pos;
}

Vector3 Cow::getPosition() const {
	return pos;
}

void Cow::setScale(const Vector3& scale) {
	this->scale = scale;
}

Vector3 Cow::getScale() const {
	return scale;
}

void Cow::setInvert(const bool& invert) {
	this->invert = invert;
}

bool Cow::getInvert() const {
	return invert;
}

void Cow::setMoving(const bool& move) {
	isMoving = move;
}

bool Cow::getMoving() const {
	return isMoving;
}

void Cow::setRunning(const bool& run) {
	isRunning = run;
}

bool Cow::getRunning() const {
	return isRunning;
}

void Cow::setHealth(const int& health) {
	c_health = health;
}

int Cow::getHealth() const {
	return c_health;
}

void Cow::setTriggered(const bool& trigger) {
	isTriggered = trigger;
}

bool Cow::getTriggered() const {
	return isTriggered;
}

void Cow::setDead(const bool& trigger) {
	isDead = trigger;
}

bool Cow::getDead() const {
	return isDead;
}

bool Cow::CheckCollisionLeft() {

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

	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
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

	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
		return true;
	}
	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y - (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);

	if (tileY == tilePY && tileX == tilePX)
		return true;
	
	return false;
}

bool Cow::CheckCollisionRight() {

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

	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
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

	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
		return true;
	}
	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y - (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);
	
	if (tileY == tilePY && tileX == tilePX)
		return true;

	return false;

}

bool Cow::CheckCollisionDown() {

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

	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
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

	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
		return true;
	}
	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y - (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);

	if (tileY == tilePY && tileX == tilePX)
		return true;

	return false;

}

bool Cow::CheckCollisionUp() {

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
	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
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
	if (tileMap->map[tileY][tileX] != 0 && tileMap->map[tileY][tileX] != 99) {
		return true;
	}

	Vector3 pointPB(player->transform.position.x - player->transform.scale.x * 0.5f, player->transform.position.y + (player->transform.scale.y * hotspotOffset), 0);
	tilePX = tileMap->GetTileX(pointPB.x);
	tilePY = tileMap->GetTileY(pointPB.y);

	if (tileY == tilePY && tileX == tilePX)
		return true;

}

bool Cow::CheckPlayer() {
	if ((pos.x > player->transform.position.x * player->transform.scale.x - tileMap->GetTileSize() && pos.y > player->transform.position.y * player->transform.scale.y - tileMap->GetTileSize()) &&
		(pos.x < player->transform.position.x * player->transform.scale.x + tileMap->GetTileSize() && pos.y < player->transform.position.y * player->transform.scale.y + tileMap->GetTileSize())) {
		return true;
	}
	return false;
}

void Cow::setTileMap(TileMap& tileMap) {
	this->tileMap = &tileMap;
}

void Cow::setPlayer(Player& player) {
	this->player = &player;
}

int Cow::getDirectionFace() const {
	return cowFaces;
}

void Cow::Update(const double& deltaTime) {

	if (!isDead) {
		c_timer += deltaTime;
		if (c_timer > c_time_limit) {
			if (!isRunning)
				c_time_limit = (double)Math::RandFloatMinMax(2, 6);
			else
				c_time_limit = (double)Math::RandFloatMinMax(0.5f, 1.f);
			cowFaces = static_cast<COW_DIRECTION>(Math::RandIntMinMax(0, 3));
			isMoving = Math::RandIntMinMax(0, 1);
			c_timer = 0.0;
		}

		if (!isRunning && !isTriggered) {
			switch (static_cast<int>(cowFaces)) {

			case 0: invert = true;
				if (!isMoving)
					ChangeStateIdle(deltaTime);
				else
					ChangeStateWalk(deltaTime);
				break;
			case 1: invert = false;
				if (!isMoving)
					ChangeStateIdle(deltaTime);
				else
					ChangeStateWalk(deltaTime);
				break;
			case 2:
				if (!isMoving)
					ChangeStateIdle(deltaTime);
				else
					ChangeStateWalk(deltaTime);
				break;
			case 3:
				if (!isMoving)
					ChangeStateIdle(deltaTime);
				else
					ChangeStateWalk(deltaTime);
				break;

			}
		}
		else if (isRunning)
		{
			switch (static_cast<int>(cowFaces)) {
			case 0: invert = true;
				ChangeStateRun(deltaTime);
				break;
			case 1: invert = false;
				ChangeStateRun(deltaTime);
				break;
			case 2:
				ChangeStateRun(deltaTime);
				break;
			case 3:
				ChangeStateRun(deltaTime);
				break;
			};
		}
	}
}

void Cow::setState(Cow_state* state) {
	this->state = state;
}

void Cow::ChangeStateIdle(const double& deltaTime) {
	state->Idle(this, deltaTime);
	isRunning = false;
	isMoving = false;
	isTriggered = false;
	isDead = false;
}

void Cow::ChangeStateRun(const double& deltaTime){
	state->Run(this, deltaTime);
	isRunning = true;
	isMoving = true;
	isTriggered = false;
	isDead = false;
}

void Cow::ChangeStateWalk(const double& deltaTime){
	state->Walk(this, deltaTime);
	isRunning = false;
	isMoving = true;
	isTriggered = false;
	isDead = false;
}

void Cow::ChangeStateDead(const double& deltaTime){
	state->Dead(this, deltaTime);
	isRunning = false;
	isMoving = false;
	isTriggered = false;
	isDead = true;
}

void Cow::ChangeStateTriggered(const double& deltaTime){
	c_timer = 0.0;
	state->Triggered(this, deltaTime);
	isRunning = false;
	isMoving = false;
	isTriggered = true;
	isDead = false;
}

void State_Idle::Idle(Cow* c, const double& deltaTime) {
	c->setState(new State_Idle());
	delete this;
}
void State_Idle::Run(Cow* c, const double& deltaTime) {
	c->setState(new State_Run());
	delete this;
}
void State_Idle::Walk(Cow* c, const double& deltaTime) {
	c->setState(new State_Walk());
	delete this;
}
void State_Idle::Dead(Cow* c, const double& deltaTime) {
	c->setState(new State_Dead());
	delete this;
}
void State_Idle::Triggered(Cow* c, const double& deltaTime) {
	c->setState(new State_Triggered());
	delete this;
}

void State_Walk::Idle(Cow* c, const double& deltaTime) {
	c->setState(new State_Idle());
	delete this;
}
void State_Walk::Run(Cow* c, const double& deltaTime) {
	c->setState(new State_Run());
	delete this;
}
void State_Walk::Walk(Cow* c, const double& deltaTime) {
	c->setState(new State_Walk());
	switch (c->getDirectionFace()) {

	case 0: if (c->CheckCollisionLeft() == false)  c->setPosition(Vector3(c->getPosition().x - 3 * deltaTime, c->getPosition().y, c->getPosition().z));  break;
	case 1: if (c->CheckCollisionRight() == false) c->setPosition(Vector3(c->getPosition().x + 3 * deltaTime, c->getPosition().y, c->getPosition().z));  break;
	case 2: if (c->CheckCollisionUp() == false)    c->setPosition(Vector3(c->getPosition().x, c->getPosition().y + 3 * deltaTime, c->getPosition().z));  break;
	case 3: if (c->CheckCollisionDown() == false)  c->setPosition(Vector3(c->getPosition().x, c->getPosition().y - 3 * deltaTime, c->getPosition().z));  break;

	}

	delete this;
}
void State_Walk::Dead(Cow* c, const double& deltaTime) {
	c->setState(new State_Dead());
	delete this;
}
void State_Walk::Triggered(Cow* c, const double& deltaTime) {
	c->setState(new State_Triggered());
	delete this;
}

void State_Run::Idle(Cow* c, const double& deltaTime) {
	c->setState(new State_Idle());
	delete this;
}
void State_Run::Run(Cow* c, const double& deltaTime) {
	c->setState(new State_Run());
	switch (c->getDirectionFace()) {

	case 0: if (c->CheckCollisionLeft() == false)  
		c->setPosition(Vector3(c->getPosition().x - 6 * deltaTime, c->getPosition().y, c->getPosition().z));  
		break;
	case 1: if (c->CheckCollisionRight() == false) 
		c->setPosition(Vector3(c->getPosition().x + 6 * deltaTime, c->getPosition().y, c->getPosition().z));  
		break;
	case 2: if (c->CheckCollisionUp() == false)    
		c->setPosition(Vector3(c->getPosition().x, c->getPosition().y + 6 * deltaTime, c->getPosition().z));  
		break;
	case 3: if (c->CheckCollisionDown() == false)  
		c->setPosition(Vector3(c->getPosition().x, c->getPosition().y - 6 * deltaTime, c->getPosition().z));  
		break;

	}
	delete this;
}
void State_Run::Walk(Cow* c, const double& deltaTime) {
	c->setState(new State_Walk());
	delete this;
}
void State_Run::Dead(Cow* c, const double& deltaTime) {
	c->setState(new State_Dead());
	delete this;
}
void State_Run::Triggered(Cow* c, const double& deltaTime) {
	c->setState(new State_Triggered());
	delete this;
}

void State_Triggered::Idle(Cow* c, const double& deltaTime) {
	c->setState(new State_Idle());
	delete this;
}
void State_Triggered::Run(Cow* c, const double& deltaTime) {
	c->setState(new State_Run());
	delete this;
}
void State_Triggered::Walk(Cow* c, const double& deltaTime) {
	c->setState(new State_Walk());
	delete this;
}
void State_Triggered::Dead(Cow* c, const double& deltaTime) {
	c->setState(new State_Dead());
	delete this;
}
void State_Triggered::Triggered(Cow* c, const double& deltaTime) {
	c->setState(new State_Triggered());
	delete this;
}