#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include "Scene3D.h"

enum SCENE_TYPE
{
	HOME,
	COW,
	CHICKEN,
	//POND,
	DRAGON,
	WELL,
	APPLE,
	//CABBAGE,
	//WHEAT,
	TOTAL_SCENES
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

	void Init();

	void Update(double dt);

	void Render();

	void Exit();
	
private:

	SceneManager();
	SCENE_TYPE sceneType;
	SCENE_TYPE prevScene;
	Scene3D* sceneList[TOTAL_SCENES];
};

#endif //SCENE_MANAGER_H

