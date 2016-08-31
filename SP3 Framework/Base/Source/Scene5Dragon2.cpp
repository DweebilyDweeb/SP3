#include "Scene5Dragon2.h"
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


Scene5Dragon2::Scene5Dragon2() {
}

Scene5Dragon2::~Scene5Dragon2() {
}

void Scene5Dragon2::Exit() {

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

void Scene5Dragon2::Init() {

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


    tileMap.LoadFile("TileMap//Scene5Dragon2.csv");
    tileMap.SetTileSize(1.0f);
    InitPlayer();
    InitCamera();

    drop = 0.0f;
    Level = 1;
}

void Scene5Dragon2::InitMeshes() {

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

    meshList[GEO_BACKGROUND_4] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_BACKGROUND_4]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//dragoncloud.tga");

    meshList[GEO_ONE_WISH] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_ONE_WISH]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//one_wish.tga");

    meshList[GEO_RED] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_RED]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//red.tga");

    meshList[GEO_GREEN] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_GREEN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//green.tga");

    meshList[GEO_BLUE] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_BLUE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//blue.tga");

    meshList[GEO_CLOUD] = MeshBuilder::GenerateQuad("Cloud3", Color(1, 1, 1), 1);
    meshList[GEO_CLOUD]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//flying_nimbus.tga");
}

void Scene5Dragon2::InitSpriteAnimations() {

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

    spriteAnimationList[SPRITE_WISH1] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
    spriteAnimationList[SPRITE_WISH1]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//wish1.tga");
    spriteAnimationList[SPRITE_WISH1]->animation = new Animation();
    spriteAnimationList[SPRITE_WISH1]->animation->Set(0, 3, 0, 1.f, true);
                              
    spriteAnimationList[SPRITE_WISH2] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
    spriteAnimationList[SPRITE_WISH2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//wish2.tga");
    spriteAnimationList[SPRITE_WISH2]->animation = new Animation();
    spriteAnimationList[SPRITE_WISH2]->animation->Set(0, 3, 0, 1.f, true);
                               
    spriteAnimationList[SPRITE_WISH3] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
    spriteAnimationList[SPRITE_WISH3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//wish3.tga");
    spriteAnimationList[SPRITE_WISH3]->animation = new Animation();
    spriteAnimationList[SPRITE_WISH3]->animation->Set(0, 3, 0, 1.f, true);

    spriteAnimationList[SPRITE_DRAGON] = MeshBuilder::GenerateSpriteAnimation("dragon", 1, 10);
    spriteAnimationList[SPRITE_DRAGON]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//dragon.tga");
    spriteAnimationList[SPRITE_DRAGON]->animation = new Animation();
    spriteAnimationList[SPRITE_DRAGON]->animation->Set(0, 9, 1, 1.5f, true);

}

void Scene5Dragon2::InitPlayer() {

    player.SetTileMap(tileMap);

    for (int row = 0; row < tileMap.GetNumRows(); ++row) {
        for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
                if (tileMap.map[row][col] == 99) {
                    player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
                }
            }
        }
    }





void Scene5Dragon2::InitCamera() {

    camera.SetPlayer(player);
    camera.SetTileMap(tileMap);

}

void Scene5Dragon2::Update(const double& deltaTime) {


    for (unsigned int i = 0; i < NUM_SPRITE; ++i)
    {

        spriteAnimationList[i]->Update(deltaTime);
        spriteAnimationList[i]->animation->animActive = true;
    }

    player.Update(deltaTime);
    camera.Update(deltaTime);
    //if (player.transform.position.y < 1){

    //    tileMap.LoadFile("TileMap//Scene5Dragon2.csv");
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

}

void Scene5Dragon2::Render() {

    Scene3D::Render();
    SetToCameraView(&camera);
    RenderTileMap();
    RenderBackground();
    RenderPlayer();
    RenderText();

}

void Scene5Dragon2::RenderTileMap() {

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
                //RenderMesh(meshList[GEO_DIRT]);
                break;
            case 2:
                //RenderMesh(meshList[GEO_GRASS]);
                break;
            case 3:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 7:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_CLOUD]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 9:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 60:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderSpriteAnimation(spriteAnimationList[SPRITE_WISH1]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 61:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderSpriteAnimation(spriteAnimationList[SPRITE_WISH2]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 62:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderSpriteAnimation(spriteAnimationList[SPRITE_WISH3]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            }
            modelStack.PopMatrix();
        }
    }

}


void Scene5Dragon2::RenderPlayer() {

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

void Scene5Dragon2::RenderText() {


}
void Scene5Dragon2::RenderBackground()
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

    //for (int i = 0; i < 5; ++i)
    //{
    //    modelStack.PushMatrix();
    //    modelStack.Translate((0.7 * camera.transform.position.x) + (i * backgroundScaleX), 12, -49);
    //    modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
    //    RenderMesh(meshList[GEO_BACKGROUND_2], false);
    //    modelStack.PopMatrix();
    //}

    //for (int i = 0; i < 5; ++i)
    //{
    //    modelStack.PushMatrix();
    //    modelStack.Translate((0.5 * camera.transform.position.x) + (i * backgroundScaleX), 8.7, -48);
    //    modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
    //    RenderMesh(meshList[GEO_BACKGROUND_3], false);
    //    modelStack.PopMatrix();
    //}

    for (int i = 0; i < 5; ++i)
    {
        modelStack.PushMatrix();
        modelStack.Translate(16.5, 12, -48);
        modelStack.Scale(backgroundScaleX + 1, backgroundScaleY, 1);
        RenderMesh(meshList[GEO_BACKGROUND_4], false);
        modelStack.PopMatrix();
    }
    for (int i = 0; i < 5; ++i)
    {
        
        modelStack.PushMatrix();
        modelStack.Translate(camWidth, 16, -20);
        modelStack.Scale(backgroundScaleX - 10, backgroundScaleY - 8, 1);
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        RenderSpriteAnimation(spriteAnimationList[SPRITE_DRAGON], false);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        modelStack.PopMatrix();
        
    }
    for (int i = 0; i < 5; ++i)
    {

        modelStack.PushMatrix();
        modelStack.Translate(camWidth, 22, -19);
        modelStack.Scale(15, 2, 1);
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        RenderMesh(meshList[GEO_ONE_WISH], false);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        modelStack.PopMatrix();

    }

    for (int i = 0; i < 5; ++i)
    {

        modelStack.PushMatrix();
        modelStack.Translate(10, 7, -19);
        modelStack.Scale(3.5, 1, 1);
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        RenderMesh(meshList[GEO_RED], false);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        modelStack.PopMatrix();

    }

    for (int i = 0; i < 5; ++i)
    {

        modelStack.PushMatrix();
        modelStack.Translate(17, 7, -19);
        modelStack.Scale(3, 1, 1);
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        RenderMesh(meshList[GEO_GREEN], false);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        modelStack.PopMatrix();

    }

    for (int i = 0; i < 5; ++i)
    {

        modelStack.PushMatrix();
        modelStack.Translate(24, 7, -19);
        modelStack.Scale(3, 1, 1);
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        RenderMesh(meshList[GEO_BLUE], false);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        modelStack.PopMatrix();

    }

}




