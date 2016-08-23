#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "TileMap.h"
#include "TileIndex.h"
#include "Vector3.h"
#include "SceneManager.h"

class Player : public GameObject {

protected:
    Vector3 velocity;
    vector<TILE_TYPE> collidables;
    vector<TILE_TYPE> collectibles;
    vector<TILE_TYPE> portal;
    vector<TILE_TYPE> bounce;


    bool CheckIfInsideTileMap();
    bool CheckCollisionLeft();
    bool CheckCollisionRight();
    bool CheckCollisionUp();
    bool CheckCollisionDown();

    int CheckPortal();
<<<<<<< HEAD
    bool CheckTrigger();
    bool CheckCollect();
    bool CheckVegetation();
    bool CheckElectric();

    TileMap* tileMap;
=======
	bool CheckTrigger();
	bool CheckCollect();
	bool CheckVegetation();
	bool CheckElectric();
>>>>>>> e6672cdb6cba78f9c86d717302693dbda0d6f869

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
<<<<<<< HEAD
    bool onElectricity;
    void setVelocity(Vector3 vel);
    Vector3 getVelocity();
=======
	bool onElectricity;
	void setVelocity(Vector3 vel);
	Vector3 getVelocity();
>>>>>>> e6672cdb6cba78f9c86d717302693dbda0d6f869

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