#ifndef SCENE_1_HOUSE_H
#define SCENE_1_HOUSE_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"

class Scene1House : public Scene3D {

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
		SPRITE_MOTHER,
		SPRITE_SON,
		SPRITE_DAUGHTER,
		SPRITE_BIRD,
		NUM_SPRITE,
	};

	Mesh* meshList[NUM_GEOMETRY];
	SpriteAnimation* spriteAnimationList[NUM_SPRITE];

	TileMap tileMap;

	void InitMeshes();
	void InitSpriteAnimations();
	void InitCamera();
	virtual void InitPlayer();

	void RenderTileMap();
	void RenderPlayer();
	void RenderBackground();
	void RenderText();

	Camera2D camera;
	PlayerSS player;

	float drop;
	float accumTime;
	int Level;

	Vector3 housePos;

public:
	//Constructor(s) & Destructor
	Scene1House();
	virtual ~Scene1House();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	 virtual void UpdateSub(const double& deltaTime){};
	virtual void Render();
	virtual void RenderSub(){};
	virtual void Exit();

};

#endif