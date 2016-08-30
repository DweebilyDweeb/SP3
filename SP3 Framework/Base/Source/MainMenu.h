#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"

class MainMenu : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_DIRT,
		GEO_GRASS,
		GEO_TITLE,
		GEO_STARTGAME,
		GEO_OPTION,
		GEO_ENDGAME,
		GEO_BLACKFADE,
		GEO_HAND,
		GEO_BACKGROUND_1,
		GEO_BACKGROUND_2,
		GEO_BACKGROUND_3,

		//Others
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

	enum SPRITE_TYPE {
		SPRITE_PLAYER_IDLE,
		SPRITE_PORTAL,
		SPRITE_MOTHER,
		SPRITE_SON,
		SPRITE_DAUGHTER,
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
	int Level;
	float alpha;

	float Xstop;

	float moveCam;

	bool transitioning;
    
	Vector3 housePos;
	Vector3 titleScale;
	Vector3 movement1;
	Vector3 movement2;
	Vector3 movement3;
	Vector3 scale1;
	Vector3 scale2;
	Vector3 scale3;
	Vector3 hand;

public:
	//Constructor(s) & Destructor
	MainMenu();
	virtual ~MainMenu();

	static bool endGame;
    
	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderSub(){};
	virtual void UpdateSub(const double& deltaTime){};
	virtual void Exit();

};

#endif