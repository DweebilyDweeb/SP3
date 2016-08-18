#ifndef SCENE_4_FISHINGPOND_H
#define SCENE_4_FISHINGPOND_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"

class Scene4FishingPond : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_DIRT,
		GEO_GRASS,
		GEO_BACKGROUND_1,
		GEO_BACKGROUND_2,
		GEO_BACKGROUND_3,

		//Others
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

	enum SPRITE_TYPE {
		SPRITE_PLAYER,
		SPRITE_PLAYER_IDLE,
		SPRITE_PLAYER_JUMP,
		SPRITE_PORTAL,
		SPRITE_WATER,
		NUM_SPRITE,
	};

	Mesh* meshList[NUM_GEOMETRY];
	SpriteAnimation* spriteAnimationList[NUM_SPRITE];

	TileMap tileMap;

	void InitMeshes();
	void InitSpriteAnimations();
	void InitCamera();
	void InitPlayer();

	void RenderTileMap();
	void RenderPlayer();
	void RenderBackground();
	void RenderText();

	Camera2D camera;
	PlayerSS player;

	float drop;
	int Level;

	Vector3 fishingRodPos;

public:
	//Constructor(s) & Destructor
	Scene4FishingPond();
	virtual ~Scene4FishingPond();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif