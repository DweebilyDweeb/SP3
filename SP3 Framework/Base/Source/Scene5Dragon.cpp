#include "Scene5Dragon.h"
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


Scene5Dragon::Scene5Dragon() {
}

Scene5Dragon::~Scene5Dragon() {
}

void Scene5Dragon::Exit() {

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

void Scene5Dragon::Init() {

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


    tileMap.LoadFile("TileMap//Scene5Dragon.csv");
    tileMap.SetTileSize(1.0f);
    InitPlayer();
    InitCamera();

    drop = 0.0f;
    Level = 1;
    
}

void Scene5Dragon::InitMeshes() {

    for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
        meshList[i] = nullptr;
    }
    //meshList[GEO_PLAYER] = MeshBuilder::Generate2DTile("Player", Color(1, 1, 1), 1);

    //meshList[GEO_TILE_BRICK] = MeshBuilder::Generate2DTile("Tile Brick", Color(1, 1, 1), 1);

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

    meshList[GEO_CLOUD] = MeshBuilder::GenerateQuad("Cloud3", Color(1, 1, 1), 1);
    meshList[GEO_CLOUD]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//flying_nimbus.tga");
}

void Scene5Dragon::InitSpriteAnimations() {

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

	spriteAnimationList[SPRITE_BIRD] = MeshBuilder::GenerateSpriteAnimation("bird", 2, 1);
	spriteAnimationList[SPRITE_BIRD]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//flying_birds.tga");
	spriteAnimationList[SPRITE_BIRD]->animation = new Animation();
	spriteAnimationList[SPRITE_BIRD]->animation->Set(0, 1, 0, 0.5f, true);

}

void Scene5Dragon::InitPlayer() {

    player.SetTileMap(tileMap);

    for (int row = 0; row < tileMap.GetNumRows(); ++row) {
        for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
            if (SceneManager::GetInstance().getPrevScene() == FISH)
            {
                if (tileMap.map[row][col] == 99) {
                    player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
                }
            }
            if (SceneManager::GetInstance().getPrevScene() == SUB_DRAGON)
            {
                if (tileMap.map[row][col] == 101) {
                    player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
                }
            }
           if (SceneManager::GetInstance().getPrevScene() == WELL)
            {
                if (tileMap.map[row][col] == 100) {
                    player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
                }
            }
        }
    }



}

void Scene5Dragon::InitCamera() {

    camera.SetPlayer(player);
    camera.SetTileMap(tileMap);

}

void Scene5Dragon::Update(const double& deltaTime) {


    for (unsigned int i = 0; i < NUM_SPRITE; ++i)
    {

        spriteAnimationList[i]->Update(deltaTime);
        spriteAnimationList[i]->animation->animActive = true;
    }
	updateClouds(deltaTime);
    player.Update(deltaTime);
    camera.Update(deltaTime);
    //if (player.transform.position.y < 1){

    //    tileMap.LoadFile("TileMap//Scene5Dragon.csv");
    //    tileMap.SetTileSize(1.0f);
    //    for (int row = 0; row < tileMap.GetNumRows(); ++row) {
    //        for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
    //            if (tileMap.map[row][col] == 99) {
    //                player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
    //            }
    //        }
    //    }
    //    Level = 2;
    //}
    if (player.transform.position.y > 60 && SceneManager::GetInstance().bWish == true)
    {
        SceneManager::GetInstance().chgCurrEnumScene(SUB_DRAGON);

        player.setVelocity(Vector3(0, 0, 0));

    }


}

void Scene5Dragon::Render() {

    Scene3D::Render();
    SetToCameraView(&camera);
    RenderTileMap();
    RenderBackground();
    RenderPlayer();
    RenderText();

}

void Scene5Dragon::RenderTileMap() {

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
            case 7:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                modelStack.Scale(2, 1, 1);
                RenderMesh(meshList[GEO_CLOUD]);
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


void Scene5Dragon::RenderPlayer() {

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

void Scene5Dragon::RenderText() {


}
void Scene5Dragon::RenderBackground()
{

    float xRatio = (static_cast<float>(camera.aspectRatio.x / static_cast<float>(camera.aspectRatio.y)));
    float camWidth = xRatio * camera.GetOrthoSize();
    float backgroundScaleX = camWidth * 2.0f;
    float backgroundScaleY = camera.GetOrthoSize() * 2.0f;

    //glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    //modelStack.PushMatrix();
    //modelStack.Translate(housePos.x, housePos.y + 2, housePos.z);
    //modelStack.Scale(10, 10, 1);
    //RenderMesh(meshList[GEO_BACKGROUND_1], false);
    //modelStack.PopMatrix();
    //glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

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
}


