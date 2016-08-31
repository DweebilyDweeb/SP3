#include "Scene6Well2.h"
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


Scene6Well2::Scene6Well2() {
}

Scene6Well2::~Scene6Well2() {
}

void Scene6Well2::Exit() {

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

void Scene6Well2::Init() {

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


    tileMap.LoadFile("TileMap//Scene6WellSub.csv");
    tileMap.SetTileSize(1.0f);
    InitPlayer();
    InitCamera();

    drop = 0.0f;
    Level = 1;
    BucketCount = 0;
    ropeMove = 0.0f;
	/*BucketObject *bo = FetchBO();
	bo->type = BucketObject::BT_WATER;
	bo->scale.Set(2, 2, 1);
	bo->pos.Set(16.5, 3, 0);
	bo->vel.SetZero();*/
}

void Scene6Well2::InitMeshes() {

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
    meshList[GEO_BACKGROUND_1]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//water_well1.tga");

    meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
    meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//mountains.tga");

    meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
    meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clouds.tga");

    meshList[GEO_BACKGROUND_4] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_BACKGROUND_4]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//water_well.tga");

	meshList[GEO_WELL] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
	meshList[GEO_WELL]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//well.tga");

	meshList[GEO_WELL2] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
	meshList[GEO_WELL2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//well2.tga");

	meshList[GEO_BUCKET] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
	meshList[GEO_BUCKET]->textureArray[0] = LoadTGA("Image//SP3_Texture//Collectibles//water_bucket.tga");

    meshList[GEO_ROPE] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_ROPE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//rope.tga");

    meshList[GEO_PULLEY] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 1);
    meshList[GEO_PULLEY]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//pulley.tga");
}

void Scene6Well2::InitSpriteAnimations() {

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

    spriteAnimationList[SPRITE_WATER] = MeshBuilder::GenerateSpriteAnimation("water", 1, 32);
    spriteAnimationList[SPRITE_WATER]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//water.tga");
    spriteAnimationList[SPRITE_WATER]->animation = new Animation();
    spriteAnimationList[SPRITE_WATER]->animation->Set(0, 31, 0, 5.f, true);
}

void Scene6Well2::InitPlayer() {

    player.SetTileMap(tileMap);

    for (int row = 0; row < tileMap.GetNumRows(); ++row) {
        for (int col = 0; col < tileMap.GetNumColumns(); ++col) {

            if (tileMap.map[row][col] == 99) {
                player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
            }
        }
    }
}


void Scene6Well2::InitCamera() {

    camera.SetPlayer(player);
    camera.SetTileMap(tileMap);

}

void Scene6Well2::Update(const double& deltaTime) {


    for (unsigned int i = 0; i < NUM_SPRITE; ++i)
    {

        spriteAnimationList[i]->Update(deltaTime);
        spriteAnimationList[i]->animation->animActive = true;
    }

    player.Update(deltaTime);
    camera.Update(deltaTime);

    spawningOfBucket(deltaTime);
    displacementOfBucket(deltaTime);
    Scene3D::Update(deltaTime);
    if (player.transform.GetPosition().y < 3)
    {
        SceneManager::GetInstance().chgCurrEnumScene(DEAD);

        player.setVelocity(Vector3(0, 0, 0));
    }
}

void Scene6Well2::Render() {

    Scene3D::Render();
    SetToCameraView(&camera);
    RenderTileMap();
    RenderBackground();
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    RenderPlayer();
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    RenderText();
	for (std::vector<BucketObject *>::iterator it = m_boList.begin(); it != m_boList.end(); ++it)
	{
		BucketObject *bo = (BucketObject *)*it;
		if (bo->active)
		{
			glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			RenderBO(bo);
			glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		}
	}
}

void Scene6Well2::RenderTileMap() {

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
            case 7:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_GRASS]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;

            case 9:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderSpriteAnimation(spriteAnimationList[SPRITE_PORTAL]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;

			case 11:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_WELL]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 12:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_WELL2]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
            case 13:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_WELL2]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            case 14:
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_WELL2]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;

            case 88:
                wellPos.Set(col * tileMap.GetTileSize(), row * tileMap.GetTileSize(), 20);
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                RenderMesh(meshList[GEO_DIRT]);
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
                break;
            }
            modelStack.PopMatrix();
        }
    }

}


void Scene6Well2::RenderPlayer() {

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

void Scene6Well2::RenderText() {


}
void Scene6Well2::RenderBackground()
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
    modelStack.PushMatrix();
    modelStack.Translate(wellPos.x + 0.55f, wellPos.y + 1.1f, 2);
	modelStack.Scale(8.9, 6.2, 1);
    RenderMesh(meshList[GEO_BACKGROUND_1], false);
    modelStack.PopMatrix();
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    modelStack.PushMatrix();
    modelStack.Translate(wellPos.x + 0.55f, wellPos.y + 1.1f, -2);
	modelStack.Scale(8.9, 6.2, 1);
    RenderMesh(meshList[GEO_BACKGROUND_4], false);
    modelStack.PopMatrix();
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    modelStack.PushMatrix();
    modelStack.Translate(wellPos.x + 0.55f, ropeMove + 20, -0.1);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(40, 0.5, 1);
    RenderMesh(meshList[GEO_ROPE], false);
    modelStack.PopMatrix();
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    modelStack.PushMatrix();
    modelStack.Translate(wellPos.x - 1.4, 28, -0.05);
    modelStack.Scale(6.2, 9, 1);
    RenderMesh(meshList[GEO_PULLEY], false);
    modelStack.PopMatrix();
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

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
        modelStack.Translate((0.5 * camera.transform.position.x) + (i * backgroundScaleX), 8.7, -48);
        modelStack.Scale(backgroundScaleX, backgroundScaleY, 1);
        RenderMesh(meshList[GEO_BACKGROUND_3], false);
        modelStack.PopMatrix();
    }
}

BucketObject* Scene6Well2::FetchBO()
{
    for (std::vector<BucketObject *>::iterator it = m_boList.begin(); it != m_boList.end(); ++it)
    {
        BucketObject *bo = (BucketObject *)*it;
        if (!bo->active)
        {
            bo->active = true;
            //m_objectCount;
            return bo;
        }
    }
    for (unsigned i = 0; i < 1; ++i)
    {
        BucketObject *bo = new BucketObject(BucketObject::BT_WATER);
        m_boList.push_back(bo);
    }
    BucketObject *bo = m_boList.back();
    bo->active = true;
    //++m_objectCount;
    return bo;
}

void Scene6Well2::RenderBO(BucketObject *bo)
{
	switch (bo->type)
	{
	case BucketObject::BT_WATER:
		modelStack.PushMatrix();
		modelStack.Translate(bo->pos.x, bo->pos.y, bo->pos.z);
		modelStack.Scale(bo->scale.x, bo->scale.y, bo->scale.z);
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		RenderMesh(meshList[GEO_BUCKET], false);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		modelStack.PopMatrix();
		break;

	}
}
void Scene6Well2::spawningOfBucket(const double& deltaTime)
{
   
    if (BucketCount < 1)
    {
        BucketObject * bo = FetchBO();
        bo->active = true;
        bo->type = BucketObject::BT_WATER;
        bo->scale.Set(1, 1, 1);
        bo->mass = 1.7;
        bo->pos.Set(16.5, 3, 0);
        bo->vel.SetZero();
        if (SceneManager::GetInstance().bAudio == true)
            PlayBloop();
        BucketCount++;
    }
}
void Scene6Well2::displacementOfBucket(const double& deltaTime)
{
    for (std::vector<BucketObject *>::iterator it = m_boList.begin(); it != m_boList.end(); ++it)
    {
        BucketObject *bo = (BucketObject *)*it;
        if (bo->active)
        {
            Vector3 acceleration, gravity;
            gravity.Set(0, 1, 0);
            acceleration = (gravity  * (1 / bo->mass));
            bo->vel += acceleration * (float)deltaTime;
            if (bo->vel.LengthSquared() > 25)
            {
                bo->vel.Normalize();
                bo->vel *= 5;
                //go->active = false;
               
            }
            ropeMove = bo->pos.y;
            if (bo->pos.y > 28)
            {
                bo->vel.SetZero();
            }

            if (bo->type == BucketObject::BT_WATER)
            {
                if (Scene3D::getDistXY(player.transform.position, bo->pos, tileMap.GetTileSize()))
                {
                    //item in inventory increase herre
                    ItemManager::GetInstance().addItem(new Water(1));
                    bo->active = false;
                    BucketCount--;
                }
                bo->pos += (float)deltaTime * bo->vel * 2;
            }
          

        }


    }
}