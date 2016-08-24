#ifndef SCENE_8_CABBAGE_H
#define SCENE_8_CABBAGE_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"
#include "CabbageObject.h"
#include "PotatoObject.h"

class Scene8Cabbage : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_DIRT,
		GEO_GRASS,
		GEO_CABBAGE,
		GEO_POTATO,
		//GEO_BACKGROUND_1,
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
		SPRITE_PLAYER_INTERACTION,
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

	void InitSetList();
	void RenderLists();
	void RenderCabbage(CabbageObject *);
	void RenderPotato(PotatoObject *);

	void UpdateVegetation(const double& deltaTime);

	Camera2D camera;
	PlayerSS player;

	float drop;
	float interaction;
	int Level;

	Vector3 housePos;


public:

	//Constructor(s) & Destructor
	Scene8Cabbage();
	virtual ~Scene8Cabbage();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void UpdateSub(const double& deltaTime){};
	virtual void Render();
	virtual void RenderSub(){};
	virtual void Exit();

	std::vector<CabbageObject *> m_cabbageList;
	std::vector<PotatoObject *> m_potatoList;
};

#endif