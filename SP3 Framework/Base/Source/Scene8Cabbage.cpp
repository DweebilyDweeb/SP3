#include "Scene8Cabbage.h"
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

Scene8Cabbage::Scene8Cabbage() {
}

Scene8Cabbage::~Scene8Cabbage() {
}

void Scene8Cabbage::Exit() {

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

void Scene8Cabbage::Init() {

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


	tileMap.LoadFile("TileMap//Scene8Cabbage.csv");
	tileMap.SetTileSize(1.0f);
	InitPlayer();
	InitCamera();
	InitSetList();

	drop = 0.0f;
	interaction = 0.f;
	Level = 1;
}

void Scene8Cabbage::InitSetList()
{
	for (int row = 0; row < tileMap.GetNumRows(); ++row)
	{
		for (int col = 0; col < tileMap.GetNumColumns(); ++col)
		{
			switch (tileMap.map[row][col])
			{
			case 15:
			{
				CabbageObject *cab = new CabbageObject();
				cab->pos = Vector3(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), -1);
				cab->scale = Vector3(tileMap.GetTileSize(), tileMap.GetTileSize(), tileMap.GetTileSize());
				cab->active = true;
				m_cabbageList.push_back(cab);
				break;
			}
			case 17:
			{
				PotatoObject *potat = new PotatoObject();
				potat->pos = Vector3(col * tileMap.GetTileSize(), row * tileMap.GetTileSize() - 0.2f, -1);
				potat->scale = Vector3(tileMap.GetTileSize(), tileMap.GetTileSize(), tileMap.GetTileSize());
				potat->active = true;
				m_potatoList.push_back(potat);
				break;
			}
			default:
				break;
			}
		}
	}
}

void Scene8Cabbage::InitMeshes() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		meshList[i] = nullptr;
	}

	meshList[GEO_DIRT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_DIRT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground.tga");

	meshList[GEO_GRASS] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_GRASS]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground_grass.tga");

	meshList[GEO_CABBAGE] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_CABBAGE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Collectibles//cabbage.tga");

	meshList[GEO_POTATO] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_POTATO]->textureArray[0] = LoadTGA("Image//SP3_Texture//Collectibles//potato.tga");

	meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
	meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//mountains.tga");

	meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clouds.tga");

}

void Scene8Cabbage::InitSpriteAnimations() {

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

void Scene8Cabbage::InitPlayer() {

	player.SetTileMap(tileMap);

	for (int row = 0; row < tileMap.GetNumRows(); ++row) {
		for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
			if (SceneManager::GetInstance().getPrevScene() == APPLE)
			{
				if (tileMap.map[row][col] == 99) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
			if (SceneManager::GetInstance().getPrevScene() == WHEAT)
			{
				if (tileMap.map[row][col] == 100) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
		}
	}
}

void Scene8Cabbage::InitCamera() {

	camera.SetPlayer(player);
	camera.SetTileMap(tileMap);

}

void Scene8Cabbage::UpdateVegetation(const double& deltaTime)
{
	for (std::vector<CabbageObject *>::iterator it = m_cabbageList.begin(); it != m_cabbageList.end(); ++it)
	{
		CabbageObject *cabbage = (CabbageObject *)*it;
		if (Scene3D::getDistX(cabbage->pos, player.transform.position, 0.5f) && cabbage->active)
		{
			player.playerState = Player::INTERACTION;
			interaction += (float)deltaTime;
			if (interaction > 3.f)
			{
				cabbage->active = false;
				ItemManager::GetInstance().addItem(new Cabbage(1));
				interaction = 0.f;
				player.playerState = Player::IDLE;
				return;
			}
		}
	}
	for (std::vector<PotatoObject *>::iterator it = m_potatoList.begin(); it != m_potatoList.end(); ++it)
	{
		PotatoObject *potato = (PotatoObject *)*it;
		if (Scene3D::getDistX(potato->pos, player.transform.position, 0.5f) && potato->active)
		{
			player.playerState = Player::INTERACTION;
			interaction += (float)deltaTime;
			if (interaction > 3.f)
			{
				potato->active = false;
				ItemManager::GetInstance().addItem(new Potato(1));
				interaction = 0.f;
				player.playerState = Player::IDLE;
				return;
			}
		}
	}
}

void Scene8Cabbage::Update(const double& deltaTime) {


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
		player.playerState = Player::IDLE;
		interaction = 0.f;
	}
}

void Scene8Cabbage::Render() {

	Scene3D::Render();
	SetToCameraView(&camera);
	RenderLists();
	RenderTileMap();
	RenderBackground();
	RenderPlayer();
	RenderText();

}

void Scene8Cabbage::RenderTileMap() {

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
				break;
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

void Scene8Cabbage::RenderPlayer() {

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

void Scene8Cabbage::RenderText() {


}

void Scene8Cabbage::RenderBackground()
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

void Scene8Cabbage::RenderLists()
{
	for (std::vector<CabbageObject *>::iterator it = m_cabbageList.begin(); it != m_cabbageList.end(); ++it)
	{
		CabbageObject *cab = (CabbageObject *)*it;
		if (cab->active)
		{
			RenderCabbage(cab);
		}
	}
	for (std::vector<PotatoObject *>::iterator it = m_potatoList.begin(); it != m_potatoList.end(); ++it)
	{
		PotatoObject *potat = (PotatoObject *)*it;
		if (potat->active)
		{
			RenderPotato(potat);
		}
	}
}

void Scene8Cabbage::RenderCabbage(CabbageObject* cab)
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.Translate(cab->pos.x, cab->pos.y, cab->pos.z);
	modelStack.Scale(cab->scale.x, cab->scale.y, cab->scale.z);
	modelStack.Rotate(-40, 0, 0, 1);
	RenderMesh(meshList[GEO_CABBAGE]);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Scene8Cabbage::RenderPotato(PotatoObject* potato)
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.Translate(potato->pos.x, potato->pos.y, potato->pos.z);
	modelStack.Scale(potato->scale.x, potato->scale.y, potato->scale.z);
	RenderMesh(meshList[GEO_POTATO]);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}