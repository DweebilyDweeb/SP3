#ifndef SCENE_3_CHICKEN_2_H
#define SCENE_3_CHICKEN_2_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"
#include "CoopObject.h"
#include "ChickenObject.h"

class Scene3Chicken2 : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_FENCE,
		GEO_TOP_GRASS,
		GEO_CHICKEN_IDLE,
		GEO_CHICKEN_COOP,
		GEO_BACKGROUND_2,
		GEO_BACKGROUND_3,

		//Others
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

	enum SPRITE_TYPE {
		SPRITE_CHICKEN_UP,
		SPRITE_CHICKEN_DOWN,
		SPRITE_CHICKEN_LEFT,
		SPRITE_CHICKEN_RIGHT,

		SPRITE_PLAYER,
		SPRITE_PLAYER_IDLE,
		SPRITE_PLAYER_IDLE_UP,
		SPRITE_PLAYER_IDLE_DOWN,
		SPRITE_PLAYER_MOVE_UP,
		SPRITE_PLAYER_MOVE_DOWN,
		SPRITE_PLAYER_INTERACTION,
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
	void InitChicken();

	void RenderTileMap();
	void RenderPlayer();
	void RenderBackground();
	void RenderText();

	void RenderChicken(ChickenObject*);
	void RenderCoop(CoopObject*);

	void UpdateEgg(const double& deltaTime);
	Camera2D camera;
	PlayerSS player;

	float drop;
	float interaction;
	int Level;
	int chickenCount;
	int maxChickenObject;
	int pos;

	bool changing;

	std::vector<ChickenObject *> m_chickenList;
	std::vector<CoopObject*> m_coopList;

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