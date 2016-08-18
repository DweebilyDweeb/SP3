#include "SceneManager.h"
#include "Scene1House.h"
#include "SceneAsn2.h"

SceneManager::~SceneManager() 
{

};

void SceneManager::chgCurrEnumScene(SCENE_TYPE type)
{
	prevScene = sceneType;
	sceneType = type;
}

SCENE_TYPE SceneManager::getCurrSceneEnum() const
{
	return sceneType;
}

void SceneManager::setPrevScene(SCENE_TYPE prev)
{
	prevScene = prev;
}

SCENE_TYPE SceneManager::getPrevScene() const
{
	return prevScene;
}

void SceneManager::Init()
{
	sceneList[HOME] = new Scene1House;
	sceneList[COW] = new SceneAsn2;

	for (int i = 0; i < TOTAL_SCENES; ++i)
	{
		sceneList[i]->Init();
	}

	chgCurrEnumScene(COW);
	setPrevScene(HOME);
}

void SceneManager::Update(double dt)
{
	sceneList[sceneType]->Update(dt);
}

void SceneManager::Render()
{
	sceneList[sceneType]->Render();
}

void SceneManager::Exit()
{
	for (int i = 0; i < TOTAL_SCENES; ++i)
	{
		if (sceneList[i])
		{
			sceneList[i]->Exit();
		}
		delete sceneList[i];
	}
}

SceneManager::SceneManager() 
{

}

