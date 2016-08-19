#include "MainMenu.h"
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

MainMenu::MainMenu() {
}

MainMenu::~MainMenu() {
}

void MainMenu::Exit() {

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

void MainMenu::Init() {

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

	tileMap.LoadFile("TileMap//Scene1House.csv");
	tileMap.SetTileSize(1.0f);
	InitPlayer();
	InitCamera();

	drop = 0.0f;
	Level = 1;
	moveCam = -7;
	alpha = 0;
}

void MainMenu::InitMeshes() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		meshList[i] = nullptr;
	}

	meshList[GEO_BLACKFADE] = MeshBuilder::GenerateQuad("Fading", Color(0, 0, 0));

	meshList[GEO_DIRT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_DIRT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground.tga");

	meshList[GEO_GRASS] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_GRASS]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground_grass.tga");

	meshList[GEO_BACKGROUND_1] = MeshBuilder::GenerateQuad("Background1", Color(1, 1, 1), 1);
	meshList[GEO_BACKGROUND_1]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//house.tga");

	meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
	meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//mountains.tga");

	meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clouds.tga");

}

void MainMenu::InitSpriteAnimations() {

	for (unsigned int i = 0; i < NUM_SPRITE; ++i) {
		spriteAnimationList[i] = nullptr;
	}

	spriteAnimationList[SPRITE_PLAYER_IDLE] = MeshBuilder::GenerateSpriteAnimation("Player", 1, 2);
	spriteAnimationList[SPRITE_PLAYER_IDLE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//player_idle.tga");
	spriteAnimationList[SPRITE_PLAYER_IDLE]->animation = new Animation();
	spriteAnimationList[SPRITE_PLAYER_IDLE]->animation->Set(0, 1, 0, 1.f, true);

	spriteAnimationList[SPRITE_PORTAL] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
	spriteAnimationList[SPRITE_PORTAL]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//portal.tga");
	spriteAnimationList[SPRITE_PORTAL]->animation = new Animation();
	spriteAnimationList[SPRITE_PORTAL]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_MOTHER] = MeshBuilder::GenerateSpriteAnimation("mother", 1, 4);
	spriteAnimationList[SPRITE_MOTHER]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//mother.tga");
	spriteAnimationList[SPRITE_MOTHER]->animation = new Animation();
	spriteAnimationList[SPRITE_MOTHER]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_SON] = MeshBuilder::GenerateSpriteAnimation("son", 1, 4);
	spriteAnimationList[SPRITE_SON]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//son.tga");
	spriteAnimationList[SPRITE_SON]->animation = new Animation();
	spriteAnimationList[SPRITE_SON]->animation->Set(0, 3, 0, 1.f, true);

	spriteAnimationList[SPRITE_DAUGHTER] = MeshBuilder::GenerateSpriteAnimation("daughter", 1, 4);
	spriteAnimationList[SPRITE_DAUGHTER]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//daughter.tga");
	spriteAnimationList[SPRITE_DAUGHTER]->animation = new Animation();
	spriteAnimationList[SPRITE_DAUGHTER]->animation->Set(0, 3, 0, 1.f, true);



}

void MainMenu::InitPlayer() {

	player.SetTileMap(tileMap);

	for (int row = 0; row < tileMap.GetNumRows(); ++row) {
		for (int col = 0; col < tileMap.GetNumColumns(); ++col) {

			if (SceneManager::GetInstance().getPrevScene() == WHEAT)

			{
				if (tileMap.map[row][col] == 99) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}

			}

			if (SceneManager::GetInstance().getPrevScene() == COW)

			{
				if (tileMap.map[row][col] == 100) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
		}
	}


}

void MainMenu::InitCamera() {

	camera.SetPlayer(player);
	camera.SetTileMap(tileMap);

}

void MainMenu::Update(const double& deltaTime) {


	for (unsigned int i = 0; i < NUM_SPRITE; ++i)
	{

		spriteAnimationList[i]->Update(deltaTime);
		spriteAnimationList[i]->animation->animActive = true;
	}


	if (alpha < 1)
		alpha += 0.1 * (float)deltaTime;
	else
		alpha = 0;

	//player.Update(deltaTime);
	if (moveCam < 10)
		moveCam += (float)deltaTime;
	else
		moveCam = -8;
	camera.Update(deltaTime);
}

void MainMenu::Render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	modelStack.LoadIdentity();
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.transform.position.x + moveCam, camera.transform.position.y - 2.5, camera.transform.position.z,
		camera.transform.position.x + camera.transform.GetForward().x + moveCam,
		camera.transform.position.y + camera.transform.GetForward().y - 2.5,
		camera.transform.position.z + camera.transform.GetForward().z,
		camera.transform.GetUp().x, camera.transform.GetUp().y, camera.transform.GetUp().z);

	float aspectRatio = static_cast<float>(camera.aspectRatio.x) / static_cast<float>(camera.aspectRatio.y);
	if (camera.IsOrtho()) {
		Mtx44 orthoMatrix;
		orthoMatrix.SetToOrtho(-aspectRatio * camera.GetOrthoSize() / 2, aspectRatio * camera.GetOrthoSize() / 2,
			-camera.GetOrthoSize() / 2, camera.GetOrthoSize() / 2,
			camera.GetNearClippingPlane(), camera.GetFarClippingPlane());

		projectionStack.LoadMatrix(orthoMatrix);
	}
	else {
		Mtx44 perspMatrix;
		perspMatrix.SetToPerspective(camera.GetFOV(),
			aspectRatio,
			camera.GetNearClippingPlane(),
			camera.GetFarClippingPlane());

		projectionStack.LoadMatrix(perspMatrix);
	}
	RenderTileMap();
	RenderBackground();
	RenderPlayer();
	RenderText();

}

void MainMenu::RenderTileMap() {

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
			case 9:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 20:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_DAUGHTER]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 21:
				housePos.Set(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), -20);
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_MOTHER]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 22:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_SON]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			}
			modelStack.PopMatrix();
		}
	}

}


void MainMenu::RenderPlayer() {

	modelStack.PushMatrix();
	modelStack.Translate(player.transform.position.x  + 22, player.transform.position.y - 0.1f, player.transform.position.z);
	//modelStack.Rotate(player.transform.rotation.z, 0, 0, 1);
	if (player.playerState == Player::IDLE)
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PLAYER_IDLE], false, player.getInvert());

}

void MainMenu::RenderText() {

}
void MainMenu::RenderBackground()
{

	float xRatio = (static_cast<float>(camera.aspectRatio.x / static_cast<float>(camera.aspectRatio.y)));
	float camWidth = xRatio * camera.GetOrthoSize();
	float backgroundScaleX = camWidth * 2.0f;
	float backgroundScaleY = camera.GetOrthoSize() * 2.0f;

	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.Translate(housePos.x, housePos.y + 2, housePos.z);
	modelStack.Scale(10, 10, 1);
	RenderMesh(meshList[GEO_BACKGROUND_1], false);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	/*modelStack.PushMatrix();
	glColor4f(0, 0, 0, alpha);
	modelStack.Translate(camera.transform.position.x, camera.transform.position.y, 0);
	modelStack.Scale(100, 100, 1);
	RenderMesh(meshList[GEO_BLACKFADE], false);
	modelStack.PopMatrix();*/

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


