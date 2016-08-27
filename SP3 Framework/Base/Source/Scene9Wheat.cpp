#include "Scene9Wheat.h"
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

Scene9Wheat::Scene9Wheat() {
}

Scene9Wheat::~Scene9Wheat() {
}

void Scene9Wheat::Exit() {

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

	Scene3D::Exit();
}

void Scene9Wheat::Init() {

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


	tileMap.LoadFile("TileMap//Scene9Wheat.csv");
	tileMap.SetTileSize(1.0f);
	InitPlayer();
	InitCamera();
	InitSetList();

	drop = 0.0f;
	interaction = 0.f;
	Level = 1;
}

void Scene9Wheat::InitSetList()
{
	for (int row = 0; row < tileMap.GetNumRows(); ++row)
	{
		for (int col = 0; col < tileMap.GetNumColumns(); ++col)
		{
			switch (tileMap.map[row][col])
			{
			case 16:
			{
				CarrotObject *carrot = new CarrotObject();
				carrot->pos = Vector3(col * tileMap.GetTileSize(), row * tileMap.GetTileSize() - 0.5f, -1);
				carrot->scale = Vector3(tileMap.GetTileSize(), tileMap.GetTileSize(), tileMap.GetTileSize());
				carrot->active = true;
				Vegetable::GetInstance().m_carrotList.push_back(carrot);
				break;
			}
			case 19:
			{
				CornObject *corn = new CornObject();
				corn->pos = Vector3(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), -1);
				corn->scale = Vector3(tileMap.GetTileSize(), tileMap.GetTileSize(), tileMap.GetTileSize());
				corn->active = true;
				Vegetable::GetInstance().m_cornList.push_back(corn);
				break;
			}
			default:
				break;
			}
		}
	}
}

void Scene9Wheat::InitMeshes() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		meshList[i] = nullptr;
	}

	meshList[GEO_DIRT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_DIRT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground.tga");

	meshList[GEO_GRASS] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_GRASS]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground_grass.tga");

	meshList[GEO_CARROT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_CARROT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Collectibles//carrot.tga");

	meshList[GEO_CORN] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_CORN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Collectibles//corn.tga");

	meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
	meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//mountains.tga");

	meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clouds.tga");

}

void Scene9Wheat::InitSpriteAnimations() {

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

	spriteAnimationList[SPRITE_PLAYER_JUMP] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 1);
	spriteAnimationList[SPRITE_PLAYER_JUMP]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//player_jump.tga");
	spriteAnimationList[SPRITE_PLAYER_JUMP]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_JUMP]->animation->Set(0, 0, 0, 1.f, true);

	spriteAnimationList[SPRITE_PLAYER_INTERACTION] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 2);
	spriteAnimationList[SPRITE_PLAYER_INTERACTION]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//player_interaction.tga");
	spriteAnimationList[SPRITE_PLAYER_INTERACTION]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_INTERACTION]->animation->Set(0, 1, 0, 0.8f, true);

	spriteAnimationList[SPRITE_PORTAL] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
	spriteAnimationList[SPRITE_PORTAL]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//portal.tga");
	spriteAnimationList[SPRITE_PORTAL]->animation = new Animation();
	spriteAnimationList[SPRITE_PORTAL]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_WATER] = MeshBuilder::GenerateSpriteAnimation("water", 1, 32);
	spriteAnimationList[SPRITE_WATER]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//water.tga");
	spriteAnimationList[SPRITE_WATER]->animation = new Animation();
	spriteAnimationList[SPRITE_WATER]->animation->Set(0, 31, 0, 5.f, true);

}

void Scene9Wheat::InitPlayer() {

	player.SetTileMap(tileMap);

	for (int row = 0; row < tileMap.GetNumRows(); ++row) {
		for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
			if (SceneManager::GetInstance().getPrevScene() == CABBAGE)
			{
				if (tileMap.map[row][col] == 99) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
			if (SceneManager::GetInstance().getPrevScene() == HOME)
			{
				if (tileMap.map[row][col] == 100) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
		}
	}
}

void Scene9Wheat::InitCamera() {

	camera.SetPlayer(player);
	camera.SetTileMap(tileMap);

}

void Scene9Wheat::Update(const double& deltaTime) 
{
	for (unsigned int i = 0; i < NUM_SPRITE; ++i)
	{

		spriteAnimationList[i]->Update(deltaTime);
		spriteAnimationList[i]->animation->animActive = true;
	}

	if (player.playerState != Player::INTERACTION)
		player.Update(deltaTime);
	else
		player.setVelocity(Vector3(0, 0, 0));

	camera.Update(deltaTime);

	Scene3D::Update(deltaTime);

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_INTERACT])
		UpdateVegetation(deltaTime);
	else
	{
		if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_INTERACT])
			player.playerState = Player::IDLE;
		interaction = 0.f;
	}

}

void Scene9Wheat::UpdateVegetation(const double& deltaTime)
{
	/*for (int row = 0; row < tileMap.GetNumRows(); ++row)
	{
		for (int col = 0; col < tileMap.GetNumColumns(); ++col)
		{
			switch (tileMap.map[row][col])
			{
			case 16:
			{
				for (std::vector<CarrotObject *>::iterator it = m_carrotList.begin(); it != m_carrotList.end(); ++it)
				{
					CarrotObject *carrot = (CarrotObject *)*it;
					if (carrot->pos == Vector3(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), -1) && carrot->active)
					{
						carrot->active = false;
					}
				}
				break;
			}
			case 19:
			{
				for (std::vector<CornObject *>::iterator it = m_cornList.begin(); it != m_cornList.end(); ++it)
				{
					CornObject *corn = (CornObject *)*it;
					if (corn->pos == Vector3(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), -1) && corn->active)
					{
						corn->active = false;
					}
				}
			}
			default:
				break;
			}
		}
	}*/
	/*int tileX = tileMap.GetTileX(player.transform.position.x);
	int tileY = tileMap.GetTileY(player.transform.position.y);

	if (tileMap.map[tileY][tileX] == TILE_CARROT)
	{
		for (std::vector<CarrotObject *>::iterator it = m_carrotList.begin(); it != m_carrotList.end(); ++it)
		{
			CarrotObject *carrot = (CarrotObject *)*it;
			if (carrot->active && carrot->pos == Vector3(tileY * tileMap.GetTileSize(), tileX * tileMap.GetTileSize(), -1))
			{
				
				carrot->active = false;
			}
		}
	}
	else if (tileMap.map[tileY][tileX] == TILE_CORN)
	{
		std::cout << "LOL" << std::endl;
	}*/

	for (std::vector<CarrotObject *>::iterator it = Vegetable::GetInstance().m_carrotList.begin(); it != Vegetable::GetInstance().m_carrotList.end(); ++it)
	{
		CarrotObject *carrot = (CarrotObject *)*it;
		if (Scene3D::getDistXY(carrot->pos, player.transform.position, 0.9f) && carrot->active && player.getOnGround())
		{
			player.playerState = Player::INTERACTION;
			interaction += (float)deltaTime;
			if (interaction > 3.f)
			{
				carrot->active = false;
				ItemManager::GetInstance().addItem(new Carrot(1));
				interaction = 0.f;
				player.playerState = Player::IDLE;
				return;
			}
		}
	}
	for (std::vector<CornObject *>::iterator it = Vegetable::GetInstance().m_cornList.begin(); it != Vegetable::GetInstance().m_cornList.end(); ++it)
	{
		CornObject *corn = (CornObject *)*it;
	
		if (Scene3D::getDistX(corn->pos, player.transform.position, 0.5f) && corn->active && player.getOnGround())
		{

			player.playerState = Player::INTERACTION;
			interaction += (float)deltaTime;
			if (interaction > 3.f)
			{
				corn->active = false;
				ItemManager::GetInstance().addItem(new Corn(1));
				interaction = 0.f;
				player.playerState = Player::IDLE;
				return;
			}
		}
	}
}

void Scene9Wheat::Render() {

	Scene3D::Render();
	SetToCameraView(&camera);
	RenderLists();
	RenderTileMap();
	RenderBackground();
	RenderPlayer();
	RenderText();

}

void Scene9Wheat::RenderTileMap() {

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
			case 1:
				RenderMesh(meshList[GEO_DIRT]);
				break;
			case 2:
				RenderMesh(meshList[GEO_GRASS]);
				break;
			case 3:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 5:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_WATER]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			case 9:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			}
			modelStack.PopMatrix();
		}
	}

}

void Scene9Wheat::RenderPlayer() {

	modelStack.PushMatrix();
	modelStack.Translate(player.transform.position.x, player.transform.position.y - 0.1f, player.transform.position.z);
	//modelStack.Rotate(player.transform.rotation.z, 0, 0, 1);
	if (player.getInvert())
		modelStack.Scale(-player.transform.scale.x, player.transform.scale.y, player.transform.scale.z);
	else
		modelStack.Scale(player.transform.scale.x, player.transform.scale.y, player.transform.scale.z);
	if (player.playerState == Player::WALKING)
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER], false, player.getInvert());
	else if (player.playerState == Player::IDLE)
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_IDLE], false, player.getInvert());
	else if (player.playerState == Player::JUMPING)
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_JUMP], false, player.getInvert());
	else if (player.playerState == Player::INTERACTION)
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_INTERACTION], false);
	modelStack.PopMatrix();

}

void Scene9Wheat::RenderText() {


}

void Scene9Wheat::RenderBackground()
{

	float xRatio = (static_cast<float>(camera.aspectRatio.x / static_cast<float>(camera.aspectRatio.y)));
	float camWidth = xRatio * camera.GetOrthoSize();
	float backgroundScaleX = camWidth * 2.0f;
	float backgroundScaleY = camera.GetOrthoSize() * 2.0f;

	for (int i = 0; i < 5; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate((0.7 * camera.transform.position.x) + (i * backgroundScaleX), 12, -49);
		modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
		RenderMesh(meshList[GEO_BACKGROUND_2], false);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 5; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate((0.5 * camera.transform.position.x) + (i * backgroundScaleX) + distMoved, 8.7, -48);
		modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
		RenderMesh(meshList[GEO_BACKGROUND_3], false);
		modelStack.PopMatrix();
	}
}

void Scene9Wheat::RenderLists()
{
	for (std::vector<CarrotObject *>::iterator it = Vegetable::GetInstance().m_carrotList.begin(); it != Vegetable::GetInstance().m_carrotList.end(); ++it)
	{
		CarrotObject *carrot = (CarrotObject *)*it;
		if (carrot->active)
			RenderCarrot(carrot);
	}
	for (std::vector<CornObject *>::iterator it = Vegetable::GetInstance().m_cornList.begin(); it != Vegetable::GetInstance().m_cornList.end(); ++it)
	{
		CornObject *corn = (CornObject *)*it;
		if (corn->active)
			RenderCorn(corn);
	}
}

void Scene9Wheat::RenderCarrot(CarrotObject * carrot)
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.Translate(carrot->pos.x, carrot->pos.y, carrot->pos.z);
	modelStack.Scale(carrot->scale.x, carrot->scale.y, carrot->scale.z);
	RenderMesh(meshList[GEO_CARROT]);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Scene9Wheat::RenderCorn(CornObject * corn)
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.Translate(corn->pos.x, corn->pos.y, corn->pos.z);
	modelStack.Scale(corn->scale.x, corn->scale.y, corn->scale.z);
	RenderMesh(meshList[GEO_CORN]);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}