#include "Scene3Chicken.h"
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
#include "SceneManager.h"

Scene3Chicken::Scene3Chicken() {
}

Scene3Chicken::~Scene3Chicken() {
}

void Scene3Chicken::Exit() {

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

void Scene3Chicken::Init() {

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


	tileMap.LoadFile("TileMap//Scene3Chicken.csv");
	tileMap.SetTileSize(1.0f);

	InitPlayer();
	InitCamera();

	drop = 0.0f;
	Level = 1;
}

void Scene3Chicken::InitMeshes() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		meshList[i] = nullptr;
	}

	meshList[GEO_DIRT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1));
	meshList[GEO_DIRT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground.tga");

	meshList[GEO_GRASS] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1));
	meshList[GEO_GRASS]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground_grass.tga");

	meshList[GEO_FENCE] = MeshBuilder::GenerateQuad("Fence", Color(1, 1, 1));
	meshList[GEO_FENCE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//fence.tga");

	meshList[GEO_BACKGROUND_1] = MeshBuilder::GenerateQuad("Background1", Color(1, 1, 1), 1);
	meshList[GEO_BACKGROUND_1]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//chicken_coop.tga");

	meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
	meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//mountains.tga");

	meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clouds.tga");

	meshList[GEO_BACKGROUND_4] = MeshBuilder::GenerateQuad("Background4", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_4]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//top_grass.tga");

}

void Scene3Chicken::InitSpriteAnimations() {

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

	spriteAnimationList[SPRITE_PORTAL] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
	spriteAnimationList[SPRITE_PORTAL]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//portal.tga");
	spriteAnimationList[SPRITE_PORTAL]->animation = new Animation();
	spriteAnimationList[SPRITE_PORTAL]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_CHICKEN] = MeshBuilder::GenerateSpriteAnimation("chicken", 4, 6);
	spriteAnimationList[SPRITE_CHICKEN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//chicken.tga");
	spriteAnimationList[SPRITE_CHICKEN]->animation = new Animation();
	spriteAnimationList[SPRITE_CHICKEN]->animation->Set(0, 23, true, 2, true);

	spriteAnimationList[SPRITE_BIRD] = MeshBuilder::GenerateSpriteAnimation("bird", 2, 1);
	spriteAnimationList[SPRITE_BIRD]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//flying_birds.tga");
	spriteAnimationList[SPRITE_BIRD]->animation = new Animation();
	spriteAnimationList[SPRITE_BIRD]->animation->Set(0, 1, 0, 0.5f, true);
}

void Scene3Chicken::InitPlayer() {

	player.SetTileMap(tileMap);

	for (int row = 0; row < tileMap.GetNumRows(); ++row) {
		for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
			if (SceneManager::GetInstance().getPrevScene() == COW)
			{
				if (tileMap.map[row][col] == 99) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
			if (SceneManager::GetInstance().getPrevScene() == FISH)
			{
				if (tileMap.map[row][col] == 100) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
		}
	}
}

void Scene3Chicken::InitCamera() {

	camera.SetPlayer(player);

	if (SceneManager::GetInstance().getChgScene() == false)
		camera.SetTileMap(tileMap);
	else
		camera.SetTileMap(minigame);

}

void Scene3Chicken::Update(const double& deltaTime) {


	for (unsigned int i = 0; i < NUM_SPRITE; ++i)
	{
		spriteAnimationList[i]->Update(deltaTime);
		spriteAnimationList[i]->animation->animActive = true;
	}

	player.Update(deltaTime);
	camera.Update(deltaTime);
	Scene3D::Update(deltaTime);
}

void Scene3Chicken::Render() {

	Scene3D::Render();
	SetToCameraView(&camera);
	if (SceneManager::GetInstance().getChgScene() == true)
		RenderSub();
	else
	{
		RenderTileMap();
		RenderBackground();
		RenderPlayer();
		RenderText();
	}

}

void Scene3Chicken::RenderTileMap() {

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
			case 4:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_FENCE]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 9:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 30:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(-0.5f, 0.1f, -1);
				modelStack.Scale(2, 1.8f, 2);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_CHICKEN]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 14:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(0, 0.6, 0);
				modelStack.Scale(3, 3, 3);
				RenderMesh(meshList[GEO_BACKGROUND_1]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			}
			modelStack.PopMatrix();
		}
	}

}


void Scene3Chicken::RenderPlayer() {

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
	modelStack.PopMatrix();

}

void Scene3Chicken::RenderText() {


}
void Scene3Chicken::RenderBackground()
{

	float xRatio = (static_cast<float>(camera.aspectRatio.x / static_cast<float>(camera.aspectRatio.y)));
	float camWidth = xRatio * camera.GetOrthoSize();
	float backgroundScaleX = camWidth * 2.0f;
	float backgroundScaleY = camera.GetOrthoSize() * 2.0f;

	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

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
		modelStack.Translate((0.7 * camera.transform.position.x) + (i * backgroundScaleX) + 10 - distMoved, 15, -49);
		if (dir > 0)
		{
			modelStack.Scale(5, 5, 1);
			RenderSpriteAnimation(spriteAnimationList[SPRITE_BIRD], false);
		}
		else
		{
			modelStack.Scale(-5, 5, 1);
			RenderSpriteAnimation(spriteAnimationList[SPRITE_BIRD], true);
		}
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
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	//modelStack.PushMatrix();
	//modelStack.Translate(16.5f, 11, -5);
	//modelStack.Scale(85, 85, 85);
	//RenderMesh(meshList[GEO_BACKGROUND_4]);
	//modelStack.PopMatrix();

}


void Scene3Chicken::RenderSub()
{
	float cameraAspectRatio = static_cast<float>(camera.aspectRatio.x) / static_cast<float>(camera.aspectRatio.y);
	float cameraWidth = cameraAspectRatio * camera.GetOrthoSize();

	int startCol = minigame.GetTileX(camera.transform.position.x - cameraWidth);
	int endCol = minigame.GetTileX(camera.transform.position.x + cameraWidth) + 1;

	int startRow = minigame.GetTileX(camera.transform.position.y - camera.GetOrthoSize());
	int endRow = minigame.GetTileX(camera.transform.position.y + camera.GetOrthoSize()) + 1;

	for (int row = Math::Max(0, startRow); row < Math::Min(endRow, minigame.GetNumRows()); ++row) {
		for (int col = Math::Max(0, startCol); col < Math::Min(endCol, minigame.GetNumColumns()); ++col) {
			modelStack.PushMatrix();
			modelStack.Translate(col * minigame.GetTileSize(), row * minigame.GetTileSize(), -1);
			modelStack.Scale(minigame.GetTileSize(), minigame.GetTileSize(), minigame.GetTileSize());
			switch (minigame.map[row][col]) {
			case 1:
				RenderMesh(meshList[GEO_DIRT]);
				break;
			case 2:
				RenderMesh(meshList[GEO_GRASS]);
				break;
			case 4:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(5, 0, 0);
				RenderMesh(meshList[GEO_FENCE]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 9:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 30:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(4.5f, 0.1f, -1);
				modelStack.Scale(2, 1.8f, 2);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_CHICKEN]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 14:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(0, 0.6, 0);
				modelStack.Scale(3, 3, 3);
				RenderMesh(meshList[GEO_BACKGROUND_1]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			}
			modelStack.PopMatrix();
		}
	}

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
	modelStack.PopMatrix();
}

void Scene3Chicken::UpdateSub(const double& deltaTime)
{
	
}