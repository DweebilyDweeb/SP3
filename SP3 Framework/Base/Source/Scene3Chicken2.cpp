#include "Scene3Chicken2.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Utility.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"
#include "LoadHmap.h"
#include "GenerateRange.h"
#include "Collision.h"
#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"

Scene3Chicken2::Scene3Chicken2() {
}

Scene3Chicken2::~Scene3Chicken2() {
}

void Scene3Chicken2::Exit() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		if (meshList[i]) {
			delete meshList[i];
		}
	}

	for (unsigned int i = 0; i < NUM_SPRITE; ++i) {
		if (spriteAnimationList[i]) {
			delete spriteAnimationList[i];
		}
	}

	while (m_chickenList.size() > 0)
	{
		ChickenObject *CO = m_chickenList.back();
		delete CO;
		m_chickenList.pop_back();
	}

	Scene3D::Exit();

}

void Scene3Chicken2::Init() {

	InitGL();

	//Create & User Our Shader
	InitShaders("Shader//Default.vertexshader", "Shader//Default.fragmentshader", DEFAULT);
	UseShader(DEFAULT);

	Scene3D::Init();
	InitMeshes();
	InitSpriteAnimations();

	InitLights();
	InitFog(Color(0.5f, 0.5f, 0.5f), 2, 20.0f, 800.0f, 0.005f);
	EnableFog(false);


	tileMap.LoadFile("TileMap//Scene3Chicken2.csv");
	tileMap.SetTileSize(1.0f);

	InitPlayer();
	InitCamera();
	maxChickenObject = 10;
	chickenCount = maxChickenObject;
	for (int i = 0; i < maxChickenObject; i++)
	{
		ChickenObject* CO = new ChickenObject;
		CO->CS = ChickenObject::IDLE;
		CO->pos.Set(Math::RandIntMinMax(5, 25), Math::RandIntMinMax(3, 16), -1);
		CO->scale.Set(2, 1.8f, 2);
		int inverting = Math::RandIntMinMax(1, 2);
		if (inverting == 1)
			CO->isInvert = true;
		else if (inverting == 2)
			CO->isInvert = false;
		CO->active = true;
		m_chickenList.push_back(CO);
	}

	CoopObject* COO = new CoopObject;
	COO->pos.Set(15, 8, -1);
	COO->scale.Set(6, 6, 6);
	COO->active = true;
	m_coopList.push_back(COO);

	drop = 0.0f;
	Level = 1;	
	pos = 0;
	interaction = 0.f;
}

void Scene3Chicken2::InitMeshes() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		meshList[i] = nullptr;
	}
	meshList[GEO_FENCE] = MeshBuilder::GenerateQuad("Fence", Color(1, 1, 1));
	meshList[GEO_FENCE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//fence.tga");

	meshList[GEO_TOP_GRASS] = MeshBuilder::GenerateQuad("Game Time", Color(1, 1, 1));
	meshList[GEO_TOP_GRASS]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//top_grass.tga");

	meshList[GEO_CHICKEN_IDLE] = MeshBuilder::GenerateQuad("Chicken Idle", Color(1, 1, 1), 0.4);
	meshList[GEO_CHICKEN_IDLE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//chicken_idle.tga");

	meshList[GEO_CHICKEN_COOP] = MeshBuilder::GenerateQuad("Chicken Idle", Color(1, 1, 1), 0.4);
	meshList[GEO_CHICKEN_COOP]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//chicken_coop.tga");

	meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
	meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//mountains.tga");

	meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clouds.tga");
	
}

void Scene3Chicken2::InitSpriteAnimations() {

	for (unsigned int i = 0; i < NUM_SPRITE; ++i) {
		spriteAnimationList[i] = nullptr;
	}

	spriteAnimationList[SPRITE_PLAYER] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 4);
	spriteAnimationList[SPRITE_PLAYER]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//player.tga");
	spriteAnimationList[SPRITE_PLAYER]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_PLAYER_IDLE] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 2);
	spriteAnimationList[SPRITE_PLAYER_IDLE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//player_idle.tga");
	spriteAnimationList[SPRITE_PLAYER_IDLE]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_IDLE]->animation->Set(0, 1, 0, 1.f, true);

	spriteAnimationList[SPRITE_PLAYER_IDLE_UP] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 1);
	spriteAnimationList[SPRITE_PLAYER_IDLE_UP]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//idle_up.tga");
	spriteAnimationList[SPRITE_PLAYER_IDLE_UP]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_IDLE_UP]->animation->Set(0, 1, 0, 1.f, true);

	spriteAnimationList[SPRITE_PLAYER_IDLE_DOWN] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 1);
	spriteAnimationList[SPRITE_PLAYER_IDLE_DOWN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//idle_down.tga");
	spriteAnimationList[SPRITE_PLAYER_IDLE_DOWN]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_IDLE_DOWN]->animation->Set(0, 0, 0, 1.f, true);

	spriteAnimationList[SPRITE_PLAYER_MOVE_UP] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 4);
	spriteAnimationList[SPRITE_PLAYER_MOVE_UP]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//walk_up.tga");
	spriteAnimationList[SPRITE_PLAYER_MOVE_UP]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_MOVE_UP]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_PLAYER_MOVE_DOWN] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 4);
	spriteAnimationList[SPRITE_PLAYER_MOVE_DOWN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//walk_down.tga");
	spriteAnimationList[SPRITE_PLAYER_MOVE_DOWN]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_MOVE_DOWN]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_PLAYER_INTERACTION] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 2);
	spriteAnimationList[SPRITE_PLAYER_INTERACTION]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//player_interaction.tga");
	spriteAnimationList[SPRITE_PLAYER_INTERACTION]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_INTERACTION]->animation->Set(0, 1, 0, 0.8f, true);

	spriteAnimationList[SPRITE_PORTAL] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
	spriteAnimationList[SPRITE_PORTAL]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//portal.tga");
	spriteAnimationList[SPRITE_PORTAL]->animation = new Animation();
	spriteAnimationList[SPRITE_PORTAL]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_CHICKEN] = MeshBuilder::GenerateSpriteAnimation("chicken", 4, 6);
	spriteAnimationList[SPRITE_CHICKEN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//chicken.tga");
	spriteAnimationList[SPRITE_CHICKEN]->animation = new Animation();
	spriteAnimationList[SPRITE_CHICKEN]->animation->Set(0, 23, true, 2, true);

}

void Scene3Chicken2::InitPlayer() {

	player.SetTileMap(tileMap);

	for (int row = 0; row < tileMap.GetNumRows(); ++row) {
		for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
			if (SceneManager::GetInstance().getPrevScene() == CHICKEN)
			{
				if (tileMap.map[row][col] == 99) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
		}
	}
}

void Scene3Chicken2::InitCamera() {

	camera.SetPlayer(player);
	camera.SetTileMap(tileMap);

}

void Scene3Chicken2::UpdateEgg(const double& deltaTime)
{
	
	for (std::vector<CoopObject*>::iterator it = m_coopList.begin(); it != m_coopList.end(); it++)
	{
		CoopObject* COO = (CoopObject*)*it;
		if (COO->active)
		{
			if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_INTERACT] && Scene3D::getDistXY(player.transform.position, COO->pos, 1.5f))
			{
				player.playerState = Player::INTERACTION;
				interaction += (float)deltaTime;
			}
			if (interaction > 2.f)
			{
				ItemManager::GetInstance().addItem(new Egg(Math::RandIntMinMax(1, 3)));
				interaction = 0.f;
				return;
			}
		}
	}
	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_INTERACT])
	{
		player.playerState = Player::IDLE;
		interaction = 0.f;
	}
}

void Scene3Chicken2::Update(const double& deltaTime) {


	for (unsigned int i = 0; i < NUM_SPRITE; ++i)
	{
		spriteAnimationList[i]->Update(deltaTime);
		spriteAnimationList[i]->animation->animActive = true;
	}
	for (std::vector<ChickenObject*>::iterator it = m_chickenList.begin(); it != m_chickenList.end(); it++)
	{
		ChickenObject* CO = (ChickenObject*)*it;
		if (CO->active)
		{
			/*if (Scene3D::getDistXY(player.transform.position, CO->pos, 3.f))
			{
				CO->CS = ChickenObject::RUNNING;
			}*/
				
			CO->movementUpdate(deltaTime, player.transform.position, tileMap);
			if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_INTERACT] && Scene3D::getDistXY(player.transform.position, CO->pos, tileMap.GetTileSize()))
			{
				CO->active = false;
				chickenCount--;
				ItemManager::GetInstance().addItem(new Meat(Math::RandIntMinMax(1, 2)));
				CO->pos.Set(Math::RandIntMinMax(5, 25), Math::RandIntMinMax(3, 16), -1);
				CO->CS = ChickenObject::IDLE;
				CO->active = true;
				chickenCount++;
				/*ChickenObject* CO2 = m_chickenList[m_chickenList.size() - 1];
				ChickenObject* temp = m_chickenList[pos];
				m_chickenList[pos] = CO2;
				m_chickenList[m_chickenList.size() - 1] = temp;
				m_chickenList.pop_back();*/
				/*CO->active = false;
				chickenCount--;
				m_chickenList.erase(it);*/
			}
			//pos++;
		}
	}
	for (std::vector<CoopObject*>::iterator it = m_coopList.begin(); it != m_coopList.end(); it++)
	{
		CoopObject* COO = (CoopObject*)*it;
		if (COO->active)
		{

		}
	}
	/*if (m_chickenList.size() < maxChickenObject)
	{
		ChickenObject* CO = new ChickenObject;
		CO->CS = ChickenObject::IDLE;
		for (std::vector<ChickenObject*>::iterator it2 = m_chickenList.begin(); it2 != m_chickenList.end(); it2++)
		{
			ChickenObject* CO2 = (ChickenObject*)*it2;
			CO->pos.Set(Math::RandIntMinMax(5, 20), Math::RandIntMinMax(3, 16), -1);
			if (CO->pos != CO2->pos)
				break;
		}
		CO->scale.Set(2, 1.8f, 2);
		CO->active = true;
		m_chickenList.push_back(CO);
		chickenCount++;
	}
	pos = 0;*/

	
	UpdateEgg(deltaTime);
	if (player.playerState != Player::INTERACTION)
		player.Update(deltaTime);
	else
		player.setVelocity(Vector3(0, 0, 0));
	//player.Update(deltaTime);
	camera.Update(deltaTime);
	Scene3D::Update(deltaTime);
}

void Scene3Chicken2::Render() {

	Scene3D::Render();
	SetToCameraView(&camera);
	RenderTileMap();
	RenderBackground();
	RenderPlayer();
	for (std::vector<ChickenObject*>::iterator it = m_chickenList.begin(); it != m_chickenList.end(); it++)
	{
		ChickenObject* GO = (ChickenObject*)*it;
		if (GO->active)
			RenderChicken(GO);
	}
	for (std::vector<CoopObject*>::iterator it = m_coopList.begin(); it != m_coopList.end(); it++)
	{
		CoopObject* GO = (CoopObject*)*it;
		if (GO->active)
			RenderCoop(GO);
	}
	RenderText();
}

void Scene3Chicken2::RenderTileMap() {

	float cameraAspectRatio = static_cast<float>(camera.aspectRatio.x) / static_cast<float>(camera.aspectRatio.y);
	float cameraWidth = cameraAspectRatio * camera.GetOrthoSize();

	int startCol = tileMap.GetTileX(camera.transform.position.x - cameraWidth);
	int endCol = tileMap.GetTileX(camera.transform.position.x + cameraWidth) + 1;

	int startRow = tileMap.GetTileX(camera.transform.position.y - camera.GetOrthoSize());
	int endRow = tileMap.GetTileX(camera.transform.position.y + camera.GetOrthoSize()) + 1;

	for (int row = Math::Max(0, startRow); row < Math::Min(endRow, tileMap.GetNumRows()); ++row) {
		for (int col = Math::Max(0, startCol); col < Math::Min(endCol, tileMap.GetNumColumns()); ++col) {
			modelStack.PushMatrix();
			modelStack.Translate(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), -1);
			modelStack.Scale(tileMap.GetTileSize(), tileMap.GetTileSize(), tileMap.GetTileSize());
			switch (tileMap.map[row][col]) {
			case 3:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
				RenderMesh(meshList[GEO_TOP_GRASS]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 4:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_FENCE]);
				RenderMesh(meshList[GEO_TOP_GRASS]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 99:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(0, 0, -5);
				RenderMesh(meshList[GEO_TOP_GRASS]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 111:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(0, 0, -5);
				RenderMesh(meshList[GEO_TOP_GRASS]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			}
			modelStack.PopMatrix();
		}
	}

}


void Scene3Chicken2::RenderPlayer() {
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.Translate(player.transform.position.x, player.transform.position.y - 0.1f, player.transform.position.z);
	//modelStack.Rotate(player.transform.rotation.z, 0, 0, 1);
	if (player.getInvert())
		modelStack.Scale(-player.transform.scale.x, player.transform.scale.y, player.transform.scale.z);
	else
		modelStack.Scale(player.transform.scale.x, player.transform.scale.y, player.transform.scale.z);
	switch (player.playerState) {
	case Player::WALKING:
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER], false, player.getInvert());
		break;
	case Player::IDLE:
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_IDLE], false, player.getInvert());
		break;
	case Player::WALKING_YUP:
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_MOVE_UP], false);
		break;
	case Player::WALKING_YDOWN:
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_MOVE_DOWN], false);
		break;
	case Player::IDLE_YUP:
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_IDLE_UP], false);
		break;
	case Player::IDLE_YDOWN:
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_IDLE_DOWN], false);
		break;
	case Player::INTERACTION:
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_INTERACTION], false);
		break;
	}
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Scene3Chicken2::RenderText() {

}

void Scene3Chicken2::RenderBackground()
{

	float xRatio = (static_cast<float>(camera.aspectRatio.x / static_cast<float>(camera.aspectRatio.y)));
	float camWidth = xRatio * camera.GetOrthoSize();
	float backgroundScaleX = camWidth * 2.0f;
	float backgroundScaleY = camera.GetOrthoSize() * 2.0f;

	for (int i = 0; i < 5; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate((0.7 * camera.transform.position.x) + (i * backgroundScaleX), camera.transform.position.y, -49);
		modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
		RenderMesh(meshList[GEO_BACKGROUND_2], false);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 5; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate((0.5 * camera.transform.position.x) + (i * backgroundScaleX), 8.7, -48);
		modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
		RenderMesh(meshList[GEO_BACKGROUND_3], false);
		modelStack.PopMatrix();
	}
}

void Scene3Chicken2::RenderChicken(ChickenObject* CO)
{
	modelStack.PushMatrix();
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	if (CO->CS == ChickenObject::WALKING || CO->CS == ChickenObject::RUNNING)
	{
		modelStack.Translate(CO->pos.x - 0.5f, CO->pos.y + 0.1f, CO->pos.z);
		if (CO->isInvert)
			modelStack.Scale(-CO->scale.x, CO->scale.y
			, CO->scale.z);
		else
			modelStack.Scale(CO->scale.x, CO->scale.y, CO->scale.z);
		RenderSpriteAnimation(spriteAnimationList[SPRITE_CHICKEN]);
	}
	else if (CO->CS == ChickenObject::IDLE)
	{
		modelStack.Translate(CO->pos.x, CO->pos.y , CO->pos.z);
		if (CO->isInvert)
			modelStack.Scale(-CO->scale.x * 1.2f, CO->scale.y * 1.5f, CO->scale.z);
		else
			modelStack.Scale(CO->scale.x * 1.2f, CO->scale.y * 1.5f, CO->scale.z);
		RenderMesh(meshList[GEO_CHICKEN_IDLE]);
	}
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PopMatrix();
}

void Scene3Chicken2::RenderCoop(CoopObject* coop)
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(coop->pos.x, coop->pos.y, coop->pos.z);
	modelStack.Scale(6, 6, 6);
	RenderMesh(meshList[GEO_CHICKEN_COOP]);
	modelStack.PopMatrix();
	modelStack.Translate(0, 0, -5);
	RenderMesh(meshList[GEO_TOP_GRASS]);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}