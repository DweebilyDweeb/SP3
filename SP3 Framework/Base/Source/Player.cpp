#include "Player.h"

Player::Player() {

	tileMap = nullptr;
	hotspotOffset = 0.495f;
    score = 0;
    Level = 1;
}

Player::~Player() {
	
	tileMap = nullptr;

}

void Player::Update(const double& deltaTime) {

	if (tileMap == nullptr) {
		cout << "Unable to update player as no tileMap is attached." << endl;
	
		return;
	}
    

}

void Player::SetTileMap(TileMap& tileMap) {

	this->tileMap = &tileMap;

}

void Player::RemoveTileMap() {

	this->tileMap = nullptr;

}

bool Player::CheckCollisionLeft() {

	/*
	*****************************
	A                           *
	*                           *
	*                           *
	*            X              *
	*                           *
	*                           *
	B                           *
	*****************************
	*/

	Vector3 pointA(transform.position.x - transform.scale.x * 0.5f, transform.position.y + (transform.scale.y * hotspotOffset), 0);
	//The reason we +0.5f is because we need to round off the number.
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}
	
	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }

	Vector3 pointB(transform.position.x - transform.scale.x * 0.5f, transform.position.y - (transform.scale.y * hotspotOffset), 0);
	//The reason we +0.5f is because we need to round off the number.
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//We are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}
	
	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }
	return false;

}

bool Player::CheckCollisionRight() {

	/*
	*****************************
	*                           A
	*                           *
	*                           *
	*            X              *
	*                           *
	*                           *
	*                           B
	*****************************
	*/

	Vector3 pointA(transform.position.x + (transform.scale.x * 0.5f), transform.position.y + (transform.scale.y * hotspotOffset), 0);
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}
	
	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }

	Vector3 pointB(transform.position.x + (transform.scale.x * 0.5f), transform.position.y - (transform.scale.y * hotspotOffset), 0);
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//We are at the edge of the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}
	
	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }
  
	return false;

}

bool Player::CheckCollisionDown() {

	/*
	*****************************
	*                           *
	*                           *
	*                           *
	*            X              *
	*                           *
	*                           *
	*                           *
	***A*********************B***
	*/

	Vector3 pointA(transform.position.x - (transform.scale.x * hotspotOffset), transform.position.y - (transform.scale.y * 0.5f), 0);
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }

	Vector3 pointB(transform.position.x + (transform.scale.x * hotspotOffset), transform.position.y - (transform.scale.y * 0.5f), 0);
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }

	return false;

}

bool Player::CheckCollisionUp() {

	/*
	***A*********************B***
	*                           *
	*                           *
	*                           *
	*            X              *
	*                           *
	*                           *
	*                           *
	*****************************
	*/

	Vector3 pointA(transform.position.x - (transform.scale.x * hotspotOffset), transform.position.y + (transform.scale.y * 0.5f), 0);
	int tileX = tileMap->GetTileX(pointA.x);
	int tileY = tileMap->GetTileY(pointA.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }

	Vector3 pointB(transform.position.x + (transform.scale.x * hotspotOffset), transform.position.y + (transform.scale.y * 0.5f), 0);
	tileX = tileMap->GetTileX(pointB.x);
	tileY = tileMap->GetTileY(pointB.y);

	//Check if we are at the edge/outside the map.
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return true;
	} else if (tileY < 0 || tileY >= tileMap->GetNumRows()) {
		return true;
	}

	for (size_t i = 0; i < collidables.size(); ++i) {
		if (collidables[i] == tileMap->map[tileY][tileX]) {
			return true;
		}
	}
    for (size_t i = 0; i < bounce.size(); ++i) {
        if (bounce[i] == tileMap->map[tileY][tileX]) {
            if (tileMap->map[tileY][tileX] == 7)
            {
                Player::velocity.y += 200 * tileMap->GetTileSize();
                break;
            }
        }

    }
   
	return false;

}

bool Player::CheckIfInsideTileMap() {

	if (tileMap == nullptr) {
		cout << "No level attached to player." << endl;
		return false;
	}

	int tileX = static_cast<float>(transform.position.x / tileMap->GetTileSize());
	int tileY = static_cast<float>(transform.position.y / tileMap->GetTileSize());
	
	if (tileX < 0 || tileX >= tileMap->GetNumColumns()) {
		return false;
	} else if (tileY < 0 || tileY >= tileMap->GetNumColumns()) {
		return false;
	}

	return true;

}

void Player::SetHotspotOffset(float hotspotOffset) {

	float min = 0.0f;
	float max = 0.495f; //It cannot be 0.5f or bigger as it will be outside of the square. Also, 0.5f will have
	//a problem where is is just nice in the next square, screwing up our calculations.
	if (hotspotOffset < 0.0f) {
		this->hotspotOffset = 0.0f;
	} else if (hotspotOffset > 0.495f) {
		this->hotspotOffset = 0.495f;
	} else {
		this->hotspotOffset = hotspotOffset;
	}

}

int Player::CheckPortal() {
    int tileX = tileMap->GetTileX(transform.position.x);
    int tileY = tileMap->GetTileY(transform.position.y);
    for (size_t i = 0; i < portal.size(); ++i) {
        if (portal[i] == tileMap->map[tileY][tileX]) {
            return portal[i];
        }
    }
    return 0;
}

bool Player::CheckTrigger() {
	int tileX = tileMap->GetTileX(transform.position.x);
	int tileY = tileMap->GetTileY(transform.position.y);
	if (tileMap->map[tileY][tileX] == TILE_CHICKEN || 
		tileMap->map[tileY][tileX] == TILE_COW     ||
		tileMap->map[tileY][tileX] == TILE_TRIGGER) {
		return true;
	}
	return false;
}

bool Player::CheckVegetation()
{
	int tileX = tileMap->GetTileX(transform.position.x);
	int tileY = tileMap->GetTileY(transform.position.y);
	if (tileMap->map[tileY][tileX] == TILE_CABBAGE ||
		tileMap->map[tileY][tileX] == TILE_CARROT ||
		tileMap->map[tileY][tileX] == TILE_POTATO ||
		tileMap->map[tileY][tileX] == TILE_WHEAT ||
		tileMap->map[tileY][tileX] == TILE_CORN)
	{
		return true;
	}
	return false;
}

float Player::GetHotspotCentre() {

	return this->hotspotOffset;

}