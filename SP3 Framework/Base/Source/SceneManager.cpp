#include "SceneManager.h"
#include "Scene1House.h"
#include "Scene2Cow.h"
#include "Scene3Chicken.h"
#include "Scene4FishingPond.h"
#include "Scene5Dragon.h"
#include "Scene6Well.h"
#include "Scene6Well2.h"
#include "Scene7Apple.h"
#include "Scene8Cabbage.h"
#include "Scene9Wheat.h"
#include "Sound.h"

SceneManager::~SceneManager() 
{
};

void SceneManager::Init()
{
    Home = true;
    World = false;
    Dragon = false;
	subScene = false;


    sceneList[HOME] = new Scene1House;
    sceneList[COW] = new Scene2Cow;
    sceneList[CHICKEN] = new Scene3Chicken;
    sceneList[FISH] = new Scene4FishingPond;
    sceneList[DRAGON] = new Scene5Dragon;
    sceneList[WELL] = new Scene6Well;
    sceneList[APPLE] = new Scene7Apple;
    sceneList[CABBAGE] = new Scene8Cabbage;
    sceneList[WHEAT] = new Scene9Wheat;

    setPrevScene(WHEAT);
    sceneType = WELL;

    if (sceneType == HOME)
    {
        Home = true;
        World = false;
        Dragon = false;
    }
    if (sceneType == COW || sceneType == CHICKEN || sceneType == FISH || sceneType == WELL || sceneType == APPLE || sceneType == CABBAGE || sceneType == WHEAT)
    {
        Home = false;
        World = true;
        Dragon = false;
        
    }
    if (sceneType == DRAGON)
    {
        Home = false;
        World = false;
        Dragon = true;
    }
    if (Home == true)
    {
        //PlayHome();
    }

    if (World == true)
    {
        //PlayWorld();
    }
    if (Dragon == true)
    {
        //PlayDragon();
    }

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

void SceneManager::setSubScene()
{
	subScene = !subScene;
}

bool SceneManager::getSubScene() const
{
	return subScene;
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

