#ifndef SCENE_7_APPLE_H
#define SCENE_7_APPLE_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"
#include "ItemManager.h"

class Scene7Apple : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_DIRT,
		GEO_GRASS,
		GEO_APPLE,
		GEO_BACKGROUND_1,
		GEO_BACKGROUND_2,
		GEO_BACKGROUND_3,
		GEO_BASKET,

		//Others
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

	enum SPRITE_TYPE {
		SPRITE_PLAYER,
		SPRITE_PLAYER_IDLE,
		SPRITE_PLAYER_JUMP,
		SPRITE_PORTAL,
		NUM_SPRITE,
	};

	Mesh* meshList[NUM_GEOMETRY];
	SpriteAnimation* spriteAnimationList[NUM_SPRITE];
	TileMap tileMap;

	void InitMeshes();
	void InitSpriteAnimations();
	void InitCamera();
	void InitPlayer();

	Item* FetchApples();
	void RenderApples(Item* item);

	void RenderTileMap();
	void RenderPlayer();
	void RenderBackground();
	void RenderText();
	void RenderBasket();

	Camera2D camera;
	PlayerSS player;
	Vector3 treePos;
	const float treeScale = 20.f;
	Vector3 spawnOffset;
	vector<Item*> appList;

public:
	//Constructor(s) & Destructor
	Scene7Apple();
	virtual ~Scene7Apple();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void UpdateSub(const double& deltaTime);
	virtual void Render();
	virtual void RenderSub();
	virtual void Exit();

};

#endif