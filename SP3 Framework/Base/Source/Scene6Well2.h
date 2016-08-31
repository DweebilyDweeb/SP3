#ifndef SCENE_6_WELL_2_H
#define SCENE_6_WELL_2_H

#include "Scene3D.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Camera2D.h"
#include "PlayerSS.h"
#include "BucketObject.h"

class Scene6Well2 : public Scene3D {

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
        //Others
        GEO_PLAYER,
		GEO_WELL,
		GEO_WELL2,
		GEO_BUCKET,
        GEO_ROPE,
        GEO_PULLEY,
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
    float BucketCount;
    float ropeMove;
    Vector3 wellPos;
	std::vector<BucketObject *> m_boList;
public:
    //Constructor(s) & Destructor
    Scene6Well2();
    virtual ~Scene6Well2();

    //Virtual Function(s)
    virtual void Init();
    virtual void Update(const double& deltaTime);
    virtual void UpdateSub(const double& deltaTime){};
    virtual void Render();
    virtual void RenderSub(){};
    virtual void Exit();


    void spawningOfBucket(const double& deltaTime);
    void displacementOfBucket(const double& deltaTime);
	void RenderBO(BucketObject *fo);

	BucketObject* FetchBO();
};

#endif