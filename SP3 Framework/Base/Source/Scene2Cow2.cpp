#include "Scene2Cow2.h"
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
#include "InputManager.h"

#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

Scene2Cow2::Scene2Cow2() {
}

Scene2Cow2::~Scene2Cow2() {
}

void Scene2Cow2::Exit() {

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

    while (m_cowList.size() > 0) {
        Cow* im = m_cowList.back();
        delete im;
        m_cowList.pop_back();
    }
    Scene3D::Exit();
}

void Scene2Cow2::Init() {

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


    tileMap.LoadFile("TileMap//Scene2Cow2.csv");
    tileMap.SetTileSize(1.0f);

    InitPlayer();
    InitCamera();
    InitCows();

    subsubScene = false;

    barPosUI.Set(0.f, -4.f, 0.f);
    barScaleUI.Set(3.f, 15.f, 0.f);
    playBarPosUI.Set(0.f, barPosUI.y, 0.f);
    playBarScaleUI.Set(3, 0.35f, 0.f);
}

void Scene2Cow2::InitMeshes() {

    for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
        meshList[i] = nullptr;
    }
    meshList[GEO_EMPTY] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
    meshList[GEO_EMPTY]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//top_grass.tga");

    meshList[GEO_FENCE] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
    meshList[GEO_FENCE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//fence.tga");

    meshList[GEO_FENCE2] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
    meshList[GEO_FENCE2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//fence_side.tga");

    meshList[GEO_MEAT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
    meshList[GEO_MEAT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Collectibles//beef.tga");

    meshList[GEO_TRANSPORT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
    meshList[GEO_TRANSPORT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//top_grass_special.tga");

    meshList[GEO_BAR] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
    meshList[GEO_BAR]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//cowBar.tga");

    meshList[GEO_PLAYBAR] = MeshBuilder::GenerateQuad("Play Bar", Color(1, 1, 1), 1);
}

void Scene2Cow2::InitSpriteAnimations() {

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

    spriteAnimationList[SPRITE_PORTAL] = MeshBuilder::GenerateSpriteAnimation("portal", 1, 4);
    spriteAnimationList[SPRITE_PORTAL]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//portal.tga");
    spriteAnimationList[SPRITE_PORTAL]->animation = new Animation();
    spriteAnimationList[SPRITE_PORTAL]->animation->Set(0, 3, 0, 1.f, true);

    spriteAnimationList[SPRITE_COW] = MeshBuilder::GenerateSpriteAnimation("cow", 1, 12);
    spriteAnimationList[SPRITE_COW]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//cow2.tga");
    spriteAnimationList[SPRITE_COW]->animation = new Animation();

    spriteAnimationList[SPRITE_COW_IDLE_UP] = MeshBuilder::GenerateSpriteAnimation("cow", 1, 3);
    spriteAnimationList[SPRITE_COW_IDLE_UP]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//cow_idle_up.tga");
    spriteAnimationList[SPRITE_COW_IDLE_UP]->animation = new Animation();
    spriteAnimationList[SPRITE_COW_IDLE_UP]->animation->Set(0, 2, 0, 1.f, true);

    spriteAnimationList[SPRITE_COW_IDLE_DOWN] = MeshBuilder::GenerateSpriteAnimation("cow", 1, 1);
    spriteAnimationList[SPRITE_COW_IDLE_DOWN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//cow_idle_down.tga");
    spriteAnimationList[SPRITE_COW_IDLE_DOWN]->animation = new Animation();
    spriteAnimationList[SPRITE_COW_IDLE_DOWN]->animation->Set(0, 0, 0, 1.f, true);

    spriteAnimationList[SPRITE_COW_MOVE_UP] = MeshBuilder::GenerateSpriteAnimation("cow", 1, 2);
    spriteAnimationList[SPRITE_COW_MOVE_UP]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//cow_move_up.tga");
    spriteAnimationList[SPRITE_COW_MOVE_UP]->animation = new Animation();
    spriteAnimationList[SPRITE_COW_MOVE_UP]->animation->Set(0, 1, 0, 1.f, true);

    spriteAnimationList[SPRITE_COW_MOVE_DOWN] = MeshBuilder::GenerateSpriteAnimation("cow", 1, 2);
    spriteAnimationList[SPRITE_COW_MOVE_DOWN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//cow_move_down.tga");
    spriteAnimationList[SPRITE_COW_MOVE_DOWN]->animation = new Animation();
    spriteAnimationList[SPRITE_COW_MOVE_DOWN]->animation->Set(0, 1, 0, 1.f, true);

    spriteAnimationList[SPRITE_COW_TRIGGERED_SIDE] = MeshBuilder::GenerateSpriteAnimation("cow", 1, 2);
    spriteAnimationList[SPRITE_COW_TRIGGERED_SIDE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//cow_triggered_side.tga");
    spriteAnimationList[SPRITE_COW_TRIGGERED_SIDE]->animation = new Animation();
    spriteAnimationList[SPRITE_COW_TRIGGERED_SIDE]->animation->Set(0, 1, 1, 1.f, true);

    spriteAnimationList[SPRITE_MILKCOW] = MeshBuilder::GenerateSpriteAnimation("cow", 1, 12);
    spriteAnimationList[SPRITE_MILKCOW]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//cow2.tga");
    spriteAnimationList[SPRITE_MILKCOW]->animation = new Animation();
    spriteAnimationList[SPRITE_MILKCOW]->animation->Set(0, 1, 0, 1.f, true);
}

void Scene2Cow2::InitPlayer() {

    player.SetTileMap(tileMap);

    for (int row = 0; row < tileMap.GetNumRows(); ++row) {
        for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
            if (tileMap.map[row][col] == 99) {
                player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
            }
        }
    }
}

void Scene2Cow2::InitCamera() {

    camera.SetPlayer(player);
    camera.SetTileMap(tileMap);

}

void Scene2Cow2::InitCows() {

    for (size_t i = 0; i < 10; ++i) {
        Cow* cow = new Cow(spriteAnimationList[SPRITE_COW]);
        cow->setTileMap(tileMap);
        cow->setPlayer(player);
        m_cowList.push_back(cow);
    }
}

void Scene2Cow2::Update(const double& deltaTime) {

    spriteAnimationList[SPRITE_COW]->animation->Set(0, 7, 0, 5, true);

    for (unsigned int i = 0; i < NUM_SPRITE; ++i)
    {
        spriteAnimationList[i]->Update(deltaTime);
        spriteAnimationList[i]->animation->animActive = true;
    }

    player.Update(deltaTime);
    camera.Update(deltaTime);

    Scene3D::Update(deltaTime);

    for (int i = 0; i < m_cowList.size(); ++i){
        m_cowList[i]->Update(deltaTime);
    }

    static bool isInteracted = false;
    if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_INTERACT] && !isInteracted) {
        for (int i = 0; i < m_cowList.size(); ++i){
            if (!m_cowList[i]->getDead()) {
                if (m_cowList[i]->CheckPlayer()) {
                    if (!m_cowList[i]->getTriggered()) {
                        m_cowList[i]->setHealth(m_cowList[i]->getHealth() - 1);
                        m_cowList[i]->ChangeStateTriggered(deltaTime);
                    }
                    if (m_cowList[i]->getHealth() <= 0) {
                        m_cowList[i]->ChangeStateDead(deltaTime);
                    }
                }
                isInteracted = true;
            }
            else {
                ItemManager::GetInstance().addItem(new Meat(1));
                m_cowList.erase(m_cowList.begin() + i);
            }
        }
    }
    else if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_INTERACT] && isInteracted) {
        isInteracted = false;
    }

    if (tileMap.map[player.transform.position.y + 0.5f][player.transform.position.x] == -1) {
        player.setVelocity(Vector3(0, 0, 0));
        SceneManager::GetInstance().isChgScene(false);
        SceneManager::GetInstance().chgCurrEnumScene(COW);
    }
    if (tileMap.map[player.transform.position.y][player.transform.position.x] == -2)
        subsubScene = true;
    else
        subsubScene = false;

    if (subsubScene) {
        static bool reverse = false;
        static int rdmSpd = Math::RandIntMinMax(8, 16);
        if (!reverse) {
            playBarPosUI.y += (float)deltaTime * rdmSpd;
            if (playBarPosUI.y > barPosUI.y + barScaleUI.y / 2) {
                reverse = true;
            }
        }
        if (reverse) {
            playBarPosUI.y -= (float)deltaTime * rdmSpd;
            if (playBarPosUI.y < barPosUI.y - barScaleUI.y / 2) {
                reverse = false;
            }
        }
        static bool isInteracted2 = false;
        if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_INTERACT] && !isInteracted2) {

            if (((playBarPosUI.y + playBarScaleUI.y) < (barPosUI.y + barScaleUI.y / 12)) &&
                ((playBarPosUI.y + playBarScaleUI.y) > (barPosUI.y - barScaleUI.y / 12))) {
                ItemManager::GetInstance().addItem(new Milk(Math::RandIntMinMax(1, 2)));
                rdmSpd = Math::RandIntMinMax(8, 16);
            }
            playBarPosUI.y = barPosUI.y + barScaleUI.y / 2;
            reverse = true;
            isInteracted2 = true;
        }
        else if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_INTERACT] && isInteracted2) {
            isInteracted2 = false;
        }
    }
}

void Scene2Cow2::Render() {

    Scene3D::Render();
    SetToCameraView(&camera);
    RenderTileMap();
    RenderPlayer();
    RenderCGO();

    if (subsubScene)
        RenderBars();

    modelStack.PushMatrix();
    modelStack.Translate(milkcowPos.x + 1, milkcowPos.y - 1, milkcowPos.z);
    modelStack.Scale(5.f, 5.f, 1.f);
    RenderSpriteAnimation(spriteAnimationList[SPRITE_MILKCOW], false);
    modelStack.PopMatrix();
}

void Scene2Cow2::RenderTileMap() {

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
            case -3:
                milkcowPos.Set(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), 2);
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_EMPTY]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case -2:
                modelStack.Rotate(180.f, 0, 0, 1);
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_TRANSPORT]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case -1:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_TRANSPORT]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 0:

            case 11:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_EMPTY]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 1:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_FENCE2]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 4:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_FENCE]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 99:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_EMPTY]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            }
            modelStack.PopMatrix();
        }
    }
}


void Scene2Cow2::RenderPlayer() {

    modelStack.PushMatrix();
    modelStack.Translate(player.transform.position.x, player.transform.position.y - 0.1f, player.transform.position.z);
    //modelStack.Rotate(player.transform.rotation.z, 0, 0, 1);
    if (player.getInvert())
        modelStack.Scale(-player.transform.scale.x, player.transform.scale.y, player.transform.scale.z);
    else
        modelStack.Scale(player.transform.scale.x, player.transform.scale.y, player.transform.scale.z);
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
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
    }
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    modelStack.PopMatrix();
}

void Scene2Cow2::RenderCows(Cow* cow) {
    modelStack.PushMatrix();
    modelStack.Translate(cow->getPosition().x, cow->getPosition().y, cow->getPosition().z);
    if (!cow->getInvert())
        modelStack.Scale(-cow->getScale().x, cow->getScale().y, cow->getScale().z);
    else
        modelStack.Scale(cow->getScale().x, cow->getScale().y, cow->getScale().z);
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    //TBC


    if (!cow->getDead()) {
        if (cow->getTriggered()) {
            RenderSpriteAnimation(spriteAnimationList[SPRITE_COW_TRIGGERED_SIDE], false, cow->getInvert());
            PlayCow();
            if (spriteAnimationList[SPRITE_COW_TRIGGERED_SIDE]->currentFrame == 1) {
                cow->setRunning(true);
            }
        }
        else {
            switch (cow->getDirectionFace()) {
            case 0:
                RenderSpriteAnimation(spriteAnimationList[SPRITE_COW], false, cow->getInvert());
                break;
            case 1:
                RenderSpriteAnimation(spriteAnimationList[SPRITE_COW], false, cow->getInvert());
                break;
            case 2:
                if (cow->getMoving() || cow->getRunning())
                    RenderSpriteAnimation(spriteAnimationList[SPRITE_COW_MOVE_UP], false);
                else
                    RenderSpriteAnimation(spriteAnimationList[SPRITE_COW_IDLE_UP], false);
                break;
            case 3:
                if (cow->getMoving() || cow->getRunning())
                    RenderSpriteAnimation(spriteAnimationList[SPRITE_COW_MOVE_DOWN], false);
                else
                    RenderSpriteAnimation(spriteAnimationList[SPRITE_COW_IDLE_DOWN], false);
                break;
            }
        }
    }
    else {
        modelStack.Scale(0.5, 0.5, 0.5);
        RenderMesh(meshList[GEO_MEAT], false);

    }
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    modelStack.PopMatrix();
}

void Scene2Cow2::RenderCGO() {
    for (vector<Cow*>::iterator vt = m_cowList.begin(); vt != m_cowList.end(); ++vt) {
        RenderCows(*vt);
    }
}

void Scene2Cow2::RenderBars() {
    modelStack.PushMatrix();
    RenderMeshIn2D(meshList[GEO_BAR], barScaleUI.x, barScaleUI.y, barPosUI.x, barPosUI.y, 3.f);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    RenderMeshIn2D(meshList[GEO_PLAYBAR], playBarScaleUI.x, playBarScaleUI.y, playBarPosUI.x, playBarPosUI.y, 4.f);
    modelStack.PopMatrix();
}