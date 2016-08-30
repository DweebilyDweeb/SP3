#ifndef SCENE_5_DRAGON_2_H
#define SCENE_5_DRAGON_2_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"

class Scene5Dragon2 : public Scene3D {

private:
    enum GEOMETRY_TYPE {
        //Tiles
        GEO_EMPTY,
        GEO_DIRT,
        GEO_GRASS,
        GEO_BACKGROUND_1,
        GEO_BACKGROUND_2,
        GEO_BACKGROUND_3,
        GEO_BACKGROUND_4,
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
        SPRITE_WISH1,
        SPRITE_WISH2,
        SPRITE_WISH3,
        SPRITE_DRAGON,
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
    Scene5Dragon2();
    virtual ~Scene5Dragon2();

    //Virtual Function(s)
    virtual void Init();
    virtual void Update(const double& deltaTime);
    virtual void Render();
    virtual void Exit();
    virtual void UpdateSub(const double& deltaTime) {};
    virtual void RenderSub() {};
};

#endif