#ifndef SCENE_5_DRAGON_H
#define SCENE_5_DRAGON_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"

class Scene5Dragon : public Scene3D {

private:
    enum GEOMETRY_TYPE {
        //Tiles
        GEO_EMPTY,
        GEO_DIRT,
        GEO_GRASS,
        GEO_BACKGROUND_1,
        GEO_BACKGROUND_2,
        GEO_BACKGROUND_3,
        GEO_CLOUD,
        //Others
        GEO_PLAYER,

        NUM_GEOMETRY,
    };

    enum SPRITE_TYPE {
        SPRITE_PLAYER,
        SPRITE_PLAYER_IDLE,
        SPRITE_PLAYER_JUMP,
        SPRITE_PORTAL,
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
    int Level;
    
    Vector3 housePos;

public:
    //Constructor(s) & Destructor
    Scene5Dragon();
    virtual ~Scene5Dragon();
    //Virtual Function(s)
    virtual void Init();
    virtual void Update(const double& deltaTime);
    virtual void Render();
    virtual void Exit();
    virtual void UpdateSub(const double& deltaTime) {};
    virtual void RenderSub() {};
};

#endif