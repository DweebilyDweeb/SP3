#ifndef SCENE_3_CHICKEN_2_H
#define SCENE_3_CHICKEN_2_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"

class Scene3Chicken2 : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_FENCE,
		GEO_TOP_GRASS,
		GEO_BACKGROUND_1,
		GEO_BACKGROUND_2,
		GEO_BACKGROUND_3,
		GEO_BACKGROUND_4,

		//Others
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

	enum SPRITE_TYPE {
		SPRITE_CHICKEN,
		SPRITE_PLAYER,
		SPRITE_PLAYER_IDLE,
		SPRITE_PLAYER_IDLE_UP,
		SPRITE_PLAYER_IDLE_DOWN,
		SPRITE_PLAYER_MOVE_UP,
		SPRITE_PLAYER_MOVE_DOWN,
		SPRITE_PORTAL,
		NUM_SPRITE,
	};

	Mesh* meshList[NUM_GEOMETRY];
	SpriteAnimation* spriteAnimationList[NUM_SPRITE];

	TileMap tileMap;
	TileMap minigame;

	void InitMeshes();
	void InitSpriteAnimations();
	void InitCamera();
	void InitPlayer();

	void RenderTileMap();
	void RenderPlayer();
	void RenderBackground();
	void RenderText();

	/*void RenderSub();
	void UpdateSub(double deltaTime);*/

	Camera2D camera;
	PlayerSS player;

	float drop;
	int Level;

	bool changing;

	Vector3 housePos;

public:
	//Constructor(s) & Destructor
	Scene3Chicken2();
	virtual ~Scene3Chicken2();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void UpdateSub(const double& deltaTime){};
	virtual void Render();
	virtual void RenderSub(){};
	virtual void Exit();

};

#endif