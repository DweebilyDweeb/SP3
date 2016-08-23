#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include "Scene3D.h"



enum SCENE_TYPE
{
<<<<<<< HEAD
    LOSE,
    DEAD,
=======
	LOSE,
	DEAD,
>>>>>>> e6672cdb6cba78f9c86d717302693dbda0d6f869
	HOME,
    COW,
    CHICKEN,
	FISH,
	DRAGON,
	WELL,
	APPLE,
	CABBAGE,
	WHEAT,

	TOTAL_SCENES,

	SUB_WELL,

	TOTAL_FINALSCENES
};

enum CHANGESCENE_TYPE
{
	CHG_NONE,
	CHG_HOME,
	CHG_FISH,
	CHG_APPLE,
	TOTAL_CHGSCENES
};

class SceneManager : public Singleton<SceneManager>	
{
	friend class Singleton<SceneManager>;

public:
	~SceneManager();
	
	void chgCurrEnumScene(SCENE_TYPE type);
	SCENE_TYPE getCurrSceneEnum() const;

	void setPrevScene(SCENE_TYPE prev);
	SCENE_TYPE getPrevScene() const;

	void setChgScene(CHANGESCENE_TYPE type);
	CHANGESCENE_TYPE getChgScene() const;

	void isChgScene(bool mode);
	bool getIsChgScene() const;

	void Init();
	void Update(double dt);
	void Render();
	void Exit();
	
private:

	SceneManager();
	SCENE_TYPE sceneType;
	SCENE_TYPE prevScene;
	CHANGESCENE_TYPE chgScene;
	Scene3D* sceneList[TOTAL_FINALSCENES];

    bool Home;
    bool World;
    bool Dragon;
	bool chgSceneMode;
};

#endif //SCENE_MANAGER_H

