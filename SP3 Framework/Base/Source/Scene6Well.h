#ifndef SCENE_6_WELL_H
#define SCENE_6_WELL_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"
#include "BucketObject.h"

class Scene6Well : public Scene3D {

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
        GEO_WELL,
        GEO_WELL2,
        GEO_BUCKET,
        //Others
        GEO_PLAYER,

        NUM_GEOMETRY,
    };

    enum SPRITE_TYPE {
        SPRITE_PLAYER,
        SPRITE_PLAYER_IDLE,
        SPRITE_PLAYER_JUMP,
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
    virtual void InitPlayer();

    void RenderTileMap();
    void RenderPlayer();
    void RenderBackground();
    void RenderText();

    Camera2D camera;
    PlayerSS player;

    float drop;
    int Level;

    Vector3 wellPos;
    Vector3 bucketPos;

    std::vector<BucketObject *> m_boList;

public:
    //Constructor(s) & Destructor
    Scene6Well();
    virtual ~Scene6Well();

    //Virtual Function(s)
    virtual void Init();
    virtual void Update(const double& deltaTime);
	virtual void UpdateSub(const double& deltaTime){};
	virtual void Render();
	virtual void RenderSub(){};
	virtual void Exit();

    void RenderBO(BucketObject *fo);

    BucketObject* FetchBO();
};

#endif