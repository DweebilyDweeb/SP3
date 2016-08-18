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
			//delete spriteAnimationList[i];
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

	drop = 0.0f;
	Level = 1;
}

void Scene8Cabbage::InitMeshes() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		meshList[i] = nullptr;
	}

	meshList[GEO_PLAYER] = MeshBuilder::GenerateQuad("Player", Color(1, 1, 1), 1);
	//meshList[GEO_PLAYER] = MeshBuilder::Generate2DTile("Player", Color(1, 1, 1), 1);
	meshList[GEO_PLAYER]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Balls//Ball_Loco.tga");

	//meshList[GEO_TILE_BRICK] = MeshBuilder::Generate2DTile("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_TILE_BRICK] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_TILE_BRICK]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Tiles//Tile_Leaf2.tga");

	meshList[GEO_SPIKE] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_SPIKE]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Items//Item_Spike.tga");

	meshList[GEO_BOUNCE] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_BOUNCE]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Items//Item_Bounce.tga");

	meshList[GEO_PORTAL] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_PORTAL]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Items//Item_Portal.tga");

	meshList[GEO_FLAG] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_FLAG]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Tiles//Tile_Flag.tga");

	meshList[GEO_POLE] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_POLE]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Tiles//Tile_Pole.tga");

	meshList[GEO_BLOCK] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_BLOCK]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Tiles//Tile_Block.tga");

	meshList[GEO_BACKGROUND_1] = MeshBuilder::GenerateQuad("Background1", Color(1, 1, 1), 1);
	meshList[GEO_BACKGROUND_1]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Backgrounds//trees.tga");

	meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
	meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Backgrounds//trees2.tga");

	meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Backgrounds//trees1.tga");

	meshList[SPRITE_PENGUIN] = MeshBuilder::GenerateSpriteAnimation("Penguin", 8, 8);
	meshList[SPRITE_PENGUIN]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn2//Items//Item_Penguin.tga");


}

void Scene8Cabbage::InitSpriteAnimations() {

	for (unsigned int i = 0; i < NUM_SPRITE; ++i) {
		spriteAnimationList[i] = nullptr;
	}
	spriteAnimationList[SPRITE_PENGUIN] = dynamic_cast<SpriteAnimation*>(meshList[SPRITE_PENGUIN]);
	if (spriteAnimationList[SPRITE_PENGUIN])
	{
		spriteAnimationList[SPRITE_PENGUIN]->animation = new Animation();
		spriteAnimationList[SPRITE_PENGUIN]->animation->Set(0, 63, 0, 5.f, true);
	}

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

void Scene8Cabbage::Update(const double& deltaTime) {


	for (unsigned int i = 0; i < NUM_SPRITE; ++i)
	{
		spriteAnimationList[i]->Update(deltaTime);
		spriteAnimationList[i]->animation->animActive = true;
	}

	player.Update(deltaTime);
	camera.Update(deltaTime);
}

void Scene8Cabbage::Render() {

	Scene3D::Render();
	SetToCameraView(&camera);
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
				RenderMesh(meshList[GEO_TILE_BRICK]);
				break;
			case 2:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderSpriteAnimation(spriteAnimationList[SPRITE_PENGUIN]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 3:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_SPIKE]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 4:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_BOUNCE]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 5:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_PORTAL]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 6:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				modelStack.Translate(0, drop, 0);
				RenderMesh(meshList[GEO_FLAG]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 7:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_POLE]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 8:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_BLOCK]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			}
			modelStack.PopMatrix();
		}
	}

}


void Scene8Cabbage::RenderPlayer() {

	modelStack.PushMatrix();
	modelStack.Translate(player.transform.position.x, player.transform.position.y, player.transform.position.z);
	modelStack.Rotate(player.transform.rotation.z, 0, 0, 1);
	modelStack.Scale(player.transform.scale.x, player.transform.scale.y, player.transform.scale.z);
	RenderMesh(meshList[GEO_PLAYER]);
	modelStack.PopMatrix();

}

void Scene8Cabbage::RenderText() {


	std::ostringstream ssred;
	ssred.precision(10);
	ssred << "x" << player.score;

	RenderMeshIn2D(meshList[SPRITE_PENGUIN], 2.0f, camera.aspectRatio.x * -3.5f, camera.aspectRatio.y * 3.5f, 0.0f, 0.0f, 0.0f);
	RenderTextOnScreen(fontList[FONT_CONSOLAS], ssred.str(), Color(1, 1, 0.2), 1.5, camera.aspectRatio.x * -3.2f, camera.aspectRatio.y * 3.2f);
	if (drop < -14 && Level)
	{
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		modelStack.Translate(16, 16, 20);
		modelStack.Scale(10, 10, 10);
		RenderSpriteAnimation(spriteAnimationList[SPRITE_PENGUIN]);
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

		RenderTextOnScreen(fontList[FONT_CONSOLAS], "YOU WIN", Color(0, 0, 1), 4, camera.aspectRatio.x  * -3.2f, camera.aspectRatio.y * -2.2f);
	}


}
void Scene8Cabbage::RenderBackground()
{

	float xRatio = (static_cast<float>(camera.aspectRatio.x / static_cast<float>(camera.aspectRatio.y)));
	float camWidth = xRatio * camera.GetOrthoSize();
	float backgroundScaleX = camWidth * 2.0f;
	float backgroundScaleY = camera.GetOrthoSize() * 2.0f;


	modelStack.PushMatrix();
	modelStack.Translate(camera.transform.position.x, camera.transform.position.y, -50);
	modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
	RenderMesh(meshList[GEO_BACKGROUND_1], false);
	modelStack.PopMatrix();

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
