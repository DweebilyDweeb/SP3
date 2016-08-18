//#ifndef SCENE_ASN_1_H
//#define SCENE_ASN_1_H
//
//#include "Scene3D.h"
//#include <vector>
//#include "BulletManager.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "Minimap.h"
//
//using std::vector;
//
//class SceneAsn1 : public Scene3D {
//
//private:
//	enum GEOMETRY_TYPE {
//		//Environment
//		GEO_SKYPLANE,
//		GEO_TERRAIN,
//
//		//Weapons
//		GEO_RIFLE,
//		GEO_PISTOL,
//		GEO_BULLET,
//
//		//UI
//		GEO_CROSSHAIR,
//		GEO_SCOPE,
//
//		//Enemy
//		GEO_ENEMY,
//
//		NUM_GEOMETRY,
//	};
//
//	Mesh* meshList[NUM_GEOMETRY];
//	SpriteAnimation* lightningAnimation;
//
//	vector<unsigned char> heightMap;
//	float mapScaleXZ, mapScaleY;
//
//	BulletManager bulletManager;
//	Player player;
//	Camera* camera;
//	Camera* minimapCamera;
//
//	bool canSwapWeapon;
//	
//	//Gun Animation
//	float gunSway;
//	float gunRecoil;
//
//	Minimap minimap;
//
//public:
//	//Constructor(s) & Destructor
//	SceneAsn1();
//	virtual ~SceneAsn1();
//
//	virtual void Exit();
//	virtual void Init();
//	virtual void Update(const double& deltaTime);
//	virtual void Render();
//	virtual void Render2D();
//	virtual void Render3D();
//	
//	void InitMeshes();
//	virtual void InitPlayer();
//	
//	//Enemy
//	Enemy enemies[5];
//	void InitEnemies();
//	void ResetEnemy();
//	void RenderEnemy();
//
//	//Rendering
//	void RenderSkyplane();
//	void RenderTerrain();
//
//	void RenderPlayerGun();
//	void RenderBullets();
//	void RenderMinimap();
//
//	//Terrain Collision
//	void TerrainCollision(const double& deltaTime);
//
//	virtual void GetInput(const InputInfo& inputInfo, const double& deltaTime);
//
//};
//
//#endif