#include "SceneManager.h"
#include "MainMenu.h"
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
#include "DeathScreen.h"
#include "LoseScreen.h"
#include "Sound.h"

SceneManager::~SceneManager() 
{
};

void SceneManager::Init()
{
    Home = true;
    World = false;
    Dragon = false;
	chgScene = CHG_NONE;
	chgSceneMode = false;

    sceneList[LOSE] = new LoseScreen;
    sceneList[DEAD] = new DeathScreen;
	sceneList[MAIN_MENU] = new MainMenu;
    sceneList[HOME] = new Scene1House;
    sceneList[COW] = new Scene2Cow;
    sceneList[CHICKEN] = new Scene3Chicken;
    sceneList[FISH] = new Scene4FishingPond;
    sceneList[DRAGON] = new Scene5Dragon;
    sceneList[WELL] = new Scene6Well;
    sceneList[APPLE] = new Scene7Apple;
    sceneList[CABBAGE] = new Scene8Cabbage;
    sceneList[WHEAT] = new Scene9Wheat;

	//sceneList[SUB_WELL] = new Scene6Well2
	sceneList[SUB_WELL] = new Scene6Well2;

    setPrevScene(WHEAT);
    sceneType = MAIN_MENU;

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
        PlayHome();
    }

    if (World == true)
    {
        PlayWorld();
    }
    if (Dragon == true)
    {
        PlayDragon();
    }

    for (int i = 0; i < TOTAL_SCENES; ++i)
    {
        sceneList[i]->Init();
    }
	
	for (int i = TOTAL_SCENES + 1; i < TOTAL_FINALSCENES; ++i)
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

void SceneManager::setChgScene(CHANGESCENE_TYPE type)
{
	chgScene = type;
}

CHANGESCENE_TYPE SceneManager::getChgScene() const
{
	return chgScene;
}

void SceneManager::isChgScene(bool mode)
{
	chgSceneMode = mode;
}

bool SceneManager::getIsChgScene() const
{
	return chgSceneMode;
}

void SceneManager::Update(double dt)
{
	sceneList[sceneType]->Update(dt);

	if (chgScene != CHG_NONE)
		sceneList[sceneType]->UpdateSub(dt);

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
        PlayHome();
        StopWorld();
        StopDragon();
    }

    if (World == true)
    {
        PlayWorld();
        StopHome();
        StopDragon();
    }
    if (Dragon == true)
    {
        PlayDragon();
        StopHome();
        StopWorld();
    }
}

void SceneManager::Render()
{
	sceneList[sceneType]->Render();

	if (chgScene != CHG_NONE)
		sceneList[sceneType]->RenderSub();
}

void SceneManager::Exit()
{
	for (int i = 0; i < TOTAL_FINALSCENES; ++i)
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

