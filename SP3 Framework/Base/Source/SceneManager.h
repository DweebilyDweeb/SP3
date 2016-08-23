#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include "Scene3D.h"



enum SCENE_TYPE
{
	LOSE,
	DEAD,
	HOME,
    COW,
    CHICKEN,
	FISH,
	DRAGON,
	WELL,
	APPLE,
	CABBAGE,
	WHEAT,
	TOTAL_SCENES
};

enum SUBSCENE_TYPE
{
	//for those scenes that doesn't need a new scene don't put here
	SUB_NONE,
	SUB_COW,
	SUB_CHICKEN,
	SUB_WELL,
	TOTAL_SUBSCENES
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

	void setSubScene(SUBSCENE_TYPE type){};
	SUBSCENE_TYPE getSubScene() const { return subType; };

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
	SUBSCENE_TYPE subType;
	CHANGESCENE_TYPE chgScene;
	Scene3D* sceneList[TOTAL_SCENES];
	Scene3D* subList[TOTAL_SUBSCENES];

    bool Home;
    bool World;
    bool Dragon;
	bool chgSceneMode;
};

#endif //SCENE_MANAGER_H

