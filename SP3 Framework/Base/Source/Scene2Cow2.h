#ifndef SCENE_2_COW2_H
#define SCENE_2_COW2_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"
#include "CowObject.h"

class Scene2Cow2 : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_FENCE,
		GEO_FENCE2,
		GEO_SHINY,
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

	enum SPRITE_TYPE {
		SPRITE_PLAYER,
		SPRITE_PLAYER_IDLE,

		SPRITE_PLAYER_IDLE_UP,
		SPRITE_PLAYER_IDLE_DOWN,
		SPRITE_PLAYER_MOVE_UP,
		SPRITE_PLAYER_MOVE_DOWN,

		SPRITE_PORTAL,
		SPRITE_COW,
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
	void RenderCows(Cow*);

	Camera2D camera;
	PlayerSS player;

	vector<Cow*>m_cowList;

public:
	//Constructor(s) & Destructor
	Scene2Cow2();
	virtual ~Scene2Cow2();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void UpdateSub(const double& deltaTime){};
	virtual void Render();
	virtual void RenderSub();
	virtual void Exit();

};

#endif