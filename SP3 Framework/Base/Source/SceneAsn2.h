#ifndef SCENE_ASN2_H
#define SCENE_ASN2_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"

class SceneAsn2 : public Scene3D {

private:
	enum GEOMETRY_TYPE {
		//Tiles
		GEO_EMPTY,
		GEO_TILE_BRICK,
        GEO_SPIKE,
        GEO_BOUNCE,
        GEO_PORTAL,
        GEO_FLAG,
        GEO_POLE,
        GEO_BLOCK,
        GEO_PLATFORM,
        GEO_BACKGROUND_1,
        GEO_BACKGROUND_2,
        GEO_BACKGROUND_3,

		//Others
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

	enum SPRITE_TYPE {
		SPRITE_PENGUIN,

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

public:
	//Constructor(s) & Destructor
	SceneAsn2();
	virtual ~SceneAsn2();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif