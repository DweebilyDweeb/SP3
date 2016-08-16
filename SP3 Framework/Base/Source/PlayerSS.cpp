#include "PlayerSS.h"
#include "InputManager.h"

PlayerSS::PlayerSS() {

	mass = 1.0f;
	walkAcceleration = 40.0f;	//These values are based on number of tiles
	jumpAcceleration = 950.0f;	//These values are based on number of tiles
	gravity = -20;
	onGround = true;
    rotateClock = false;
    counterClock = false;
    spin = 0.0f;
	collidables.push_back(TILE_BRICK);
	collectibles.push_back(TILE_PENGUIN);
    spikes.push_back(TILE_SPIKES);
    bounce.push_back(TILE_BOUNCE);
    portal.push_back(TILE_PORTAL);
    flag.push_back(TILE_FLAG);
    pole.push_back(TILE_POLE);

}

PlayerSS::~PlayerSS() {
}

void PlayerSS::Update(const double& deltaTime) {
	
	//Assume our player is always the same size as 1 tile.
	Player::Update(deltaTime);

	maxSpeed = tileMap->GetTileSize() * 20;
	transform.scale.Set(tileMap->GetTileSize(), tileMap->GetTileSize(), 1);
    transform.rotation.Set(0, 0, spin);
	//transform.scale.Set(1.0f, 0.5f, 1.0f);

	//If we collide with a wall, how much to offset from the tile we are moving to.
	Vector2 collisionOffset;
	collisionOffset.x = (tileMap->GetTileSize() - transform.scale.x) * 0.5f;
	collisionOffset.y = (tileMap->GetTileSize() - transform.scale.y) * 0.5f;
	
	/*
	    ________________
	   |		  		|
	   |       		    |
	   |       **********
	   |       *	    *
	   |<----->*	        *
	   |       *        *
	   |       **********	
	   |________________|
		  
		The offset is half of the length shown above. Basically, if our player is not the same size as the map tile,
		then when we collide we need to put our player back into a valid tile, then offset it so that it is barely touching
		the wall.

	*/

	//Our current tile
	int tileX = tileMap->GetTileX(transform.position.x);
	int tileY = tileMap->GetTileY(transform.position.y);
	
	//User Input
	Vector3 acceleration;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT]) {
		acceleration.x += walkAcceleration * tileMap->GetTileSize();
        rotateClock = true;
	}

    if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MOVE_RIGHT]) {
        rotateClock = false;
    }

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT]) {
		acceleration.x -= walkAcceleration * tileMap->GetTileSize();
        counterClock = true;
	}

    if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MOVE_LEFT]) {
        counterClock = false;
    }
	acceleration.y = gravity * tileMap->GetTileSize();
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP] && onGround) {
		acceleration.y += jumpAcceleration * tileMap->GetTileSize();
		onGround = false;
	}

    if (rotateClock == true)
    {
        spin -= 1000 * float(deltaTime);
    }

    if (counterClock == true)
    {
        spin += 1000 * float(deltaTime);
    }

	velocity += acceleration * deltaTime;

	//Limit Velocity
	velocity.x = Math::Clamp(velocity.x, -maxSpeed, maxSpeed);
	velocity.y = Math::Clamp(velocity.y, -maxSpeed, maxSpeed);

	//Move Along Y
	transform.position.y += velocity.y * deltaTime;

	//Check Collision Along Y
	if (velocity.y > 0) {
		if (CheckCollisionUp()) {
			transform.position.y = tileY * tileMap->GetTileSize() + collisionOffset.y;
			velocity.y = -velocity.y;
		}
	} else {
		if (CheckCollisionDown()) {
			transform.position.y = tileY * tileMap->GetTileSize() - collisionOffset.y;
			velocity.y = 0;
			onGround = true;
		} else {
			onGround = false;
		}
	}

	//Move Along X
	transform.position.x += velocity.x * deltaTime;
	tileX = tileMap->GetTileX(transform.position.x);

	//Check Collision Along X
	if (velocity.x > 0) {
		if (CheckCollisionRight()) {
			transform.position.x = tileX * tileMap->GetTileSize() + collisionOffset.x;
			velocity.x = 0;
		}
	} else if (velocity.x < 0) {
		if (CheckCollisionLeft()) {
			transform.position.x = tileX * tileMap->GetTileSize() - collisionOffset.x;
			velocity.x = 0;
		}
	}

	velocity.x *= 0.95f * (1.0f - deltaTime);

}