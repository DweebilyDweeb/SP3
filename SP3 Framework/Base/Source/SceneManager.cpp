#include "SceneManager.h"
#include "Scene1House.h"
#include "Scene3Chicken.h"
#include "Scene4FishingPond.h"
#include "Scene5Dragon.h"
#include "Scene6Well.h"
#include "Scene8Cabbage.h"
#include "Scene9Wheat.h"

SceneManager::~SceneManager() 
{

};

void SceneManager::Init()
{
    sceneList[HOME] = new Scene1House;
    sceneList[FISH] = new Scene4FishingPond;
    sceneList[DRAGON] = new Scene5Dragon;
    sceneList[WELL] = new Scene6Well;

    setPrevScene(FISH);
    sceneType = DRAGON;

    for (int i = 0; i < TOTAL_SCENES; ++i)
    {
        sceneList[i]->Init();
    }
}

void SceneManager::chgCurrEnumScene(SCENE_TYPE type)
{
	prevScene = sceneType;
	sceneType = type;
    sceneList[sceneType]->InitPlayer();
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

