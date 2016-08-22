#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include "Scene3D.h"



enum SCENE_TYPE
{
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
	SUB_NONE,
	TOP_DOWN,
	ZOOMED_IN,
	TOTAL_SUBSCENES
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

	void setSubScene(SUBSCENE_TYPE type);
	SUBSCENE_TYPE getSubScene() const;

	void isSubScene();
	bool getIsSubScene() const;

	void Init();
	void Update(double dt);
	void Render();
	void Exit();
	
private:

	SceneManager();
	SCENE_TYPE sceneType;
	SCENE_TYPE prevScene;
	SUBSCENE_TYPE subScene;
	Scene3D* sceneList[TOTAL_SCENES];
	
    bool Home;
    bool World;
    bool Dragon;
	bool subSceneMode;
};

#endif //SCENE_MANAGER_H

