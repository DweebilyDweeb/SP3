#include "Scene4FishingPond.h"
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


Scene4FishingPond::Scene4FishingPond() {
}

Scene4FishingPond::~Scene4FishingPond() {
}

void Scene4FishingPond::Exit() {

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

	while (m_foList.size() > 0)
	{
		FishObject *fo = m_foList.back();
		delete fo;
		m_foList.pop_back();
	}

	Scene3D::Exit();
}

void Scene4FishingPond::Init() {

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


	tileMap.LoadFile("TileMap//Scene4FishingPond.csv");
	tileMap.SetTileSize(1.0f);
	InitPlayer();
	InitCamera();

	drop = 0.0f;
	Level = 1;
	maxFish = stoi(getDataFromCSV("CSV//data.csv", "maxFish"));
	chanceOfFish = stof(getDataFromCSV("CSV//data.csv", "chanceOfFish(1-10)"));
	fishCount = 0;
	accumTime = 0.5f;
    player.onElectricity = false;
    for (std::vector<FishObject *>::iterator it = m_foList.begin(); it != m_foList.end(); ++it)
    {
        FishObject *fo = (FishObject *)*it;
        if (fo->active)
        {
            fo->active = false;
        }
		fishCount = 0;
    }
}

void Scene4FishingPond::InitMeshes() {

	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
		meshList[i] = nullptr;
	}
	//meshList[GEO_PLAYER] = MeshBuilder::Generate2DTile("Player", Color(1, 1, 1), 1);

	//meshList[GEO_TILE_BRICK] = MeshBuilder::Generate2DTile("Tile Brick", Color(1, 1, 1), 1);

	meshList[GEO_DIRT] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_DIRT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground.tga");

	meshList[GEO_GRASS] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_GRASS]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//ground_grass.tga");

	meshList[GEO_GENERATOR] = MeshBuilder::GenerateQuad("Tile Brick", Color(1, 1, 1), 1);
	meshList[GEO_GENERATOR]->textureArray[0] = LoadTGA("Image//SP3_Texture//Tiles//generator.tga");

	meshList[GEO_BACKGROUND_1] = MeshBuilder::GenerateQuad("Background1", Color(1, 1, 1), 1);
	meshList[GEO_BACKGROUND_1]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//fishing_rod.tga");

	meshList[GEO_BACKGROUND_2] = MeshBuilder::GenerateQuad("Background2", Color(1, 1, 1), 0.7);
	meshList[GEO_BACKGROUND_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//mountains.tga");

	meshList[GEO_BACKGROUND_3] = MeshBuilder::GenerateQuad("Background3", Color(1, 1, 1), 0.4);
	meshList[GEO_BACKGROUND_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clouds.tga");

	meshList[GEO_TROUT] = MeshBuilder::GenerateQuad("trout", Color(1, 1, 1), 0.4);
	meshList[GEO_TROUT]->textureArray[0] = LoadTGA("Image//SP3_Texture//Collectibles//fish3.tga");

	meshList[GEO_SHARK] = MeshBuilder::GenerateQuad("shark", Color(1, 1, 1), 0.4);
	meshList[GEO_SHARK]->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//shark3.tga");

}

void Scene4FishingPond::InitSpriteAnimations() {

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

	spriteAnimationList[SPRITE_ELECTRICITY] = MeshBuilder::GenerateSpriteAnimation("electricity", 5, 5);
	spriteAnimationList[SPRITE_ELECTRICITY]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//electric.tga");
	spriteAnimationList[SPRITE_ELECTRICITY]->animation = new Animation();
	spriteAnimationList[SPRITE_ELECTRICITY]->animation->Set(0, 24, 0, 1.f, true);

	spriteAnimationList[SPRITE_BIRD] = MeshBuilder::GenerateSpriteAnimation("bird", 2, 1);
	spriteAnimationList[SPRITE_BIRD]->textureArray[0] = LoadTGA("Image//SP3_Texture//Sprite_Animation//flying_birds.tga");
	spriteAnimationList[SPRITE_BIRD]->animation = new Animation();
	spriteAnimationList[SPRITE_BIRD]->animation->Set(0, 1, 0, 0.5f, true);
}

void Scene4FishingPond::InitPlayer() {

	player.SetTileMap(tileMap);

	for (int row = 0; row < tileMap.GetNumRows(); ++row) {
		for (int col = 0; col < tileMap.GetNumColumns(); ++col) {
			if (SceneManager::GetInstance().getPrevScene() == CHICKEN)
			{
				if (tileMap.map[row][col] == 99) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
				if (SceneManager::GetInstance().getPrevScene() == DRAGON)
			{
				if (tileMap.map[row][col] == 100) {
					player.transform.SetPosition(tileMap.GetTileSize() * col, tileMap.GetTileSize() * row, 0);
				}
			}
		}
	}
	for (std::vector<FishObject *>::iterator it = m_foList.begin(); it != m_foList.end(); ++it)
	{
		FishObject *fo = (FishObject *)*it;
		if (fo->active)
		{
			fo->active = false;
		}
		fishCount = 0;
	}

}

void Scene4FishingPond::InitCamera() {

	camera.SetPlayer(player);
	camera.SetTileMap(tileMap);

}

void Scene4FishingPond::Update(const double& deltaTime) {


	for (unsigned int i = 0; i < NUM_SPRITE; ++i)
	{

		spriteAnimationList[i]->Update(deltaTime);
		spriteAnimationList[i]->animation->animActive = true;
	}

	player.Update(deltaTime);
	camera.Update(deltaTime);

	spawningOfFish(deltaTime);
	displacementOfFish(deltaTime);

	if (SceneManager::GetInstance().getIsChgScene()) {
        player.onElectricity = true;
	}
	else
        player.onElectricity = false;

    if (player.transform.GetPosition().y < 2)
    {
        SceneManager::GetInstance().chgCurrEnumScene(DEAD);

        player.setVelocity(Vector3(0, 0, 0));
    }
	Scene3D::Update(deltaTime);
}

void Scene4FishingPond::Render() {

	SetToCameraView(&camera);
	Scene3D::Render();
	Scene3D::setZoomValues(2, 0, -5);
	bool b = Scene3D::getDistXY(player.transform.position, Vector3(21.5,5,0), 15);
	if (b)
		SetToCameraView(&camera, 1);
	else
		SetToCameraView(&camera);
	
	for (std::vector<FishObject *>::iterator it = m_foList.begin(); it != m_foList.end(); ++it)
	{
		FishObject *fo = (FishObject *)*it;
		if (fo->active)
		{
			RenderFO(fo);
		}
	}
	RenderTileMap();
	RenderBackground();
	RenderPlayer();
	RenderText();

}

void Scene4FishingPond::RenderTileMap() {

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
			case 8:
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				RenderMesh(meshList[GEO_GENERATOR]);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				break;
			case 23:
                if (player.onElectricity == true)
				{
					glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
					RenderSpriteAnimation(spriteAnimationList[SPRITE_ELECTRICITY]);
					glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				}
				break;
			}
			modelStack.PopMatrix();
		}
	}

}


void Scene4FishingPond::RenderPlayer() {
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
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
	//cout << player.transform.position<<endl;
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Scene4FishingPond::RenderText() {


}
void Scene4FishingPond::RenderBackground()
{

	float xRatio = (static_cast<float>(camera.aspectRatio.x / static_cast<float>(camera.aspectRatio.y)));
	float camWidth = xRatio * camera.GetOrthoSize();
	float backgroundScaleX = camWidth * 2.0f;
	float backgroundScaleY = camera.GetOrthoSize() * 2.0f;

	/*glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	modelStack.PushMatrix();
	modelStack.Translate(fishingRodPos.x + 1.f, fishingRodPos.y + 0.5f, fishingRodPos.z);
	modelStack.Scale(2, 2, 1);
	RenderMesh(meshList[GEO_BACKGROUND_1], false);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);*/

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


FishObject* Scene4FishingPond::FetchFO()
{
	for (std::vector<FishObject *>::iterator it = m_foList.begin(); it != m_foList.end(); ++it)
	{
		FishObject *fo = (FishObject *)*it;
		if (!fo->active)
		{
			fo->active = true;
			//m_objectCount;
			return fo;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		FishObject *fo = new FishObject(FishObject::FT_TROUT);
		m_foList.push_back(fo);
	}
	FishObject *fo = m_foList.back();
	fo->active = true;
	//++m_objectCount;
	return fo;
}

void Scene4FishingPond::RenderFO(FishObject *fo)
{
	switch (fo->type)
	{
	case FishObject::FT_TROUT:
		modelStack.PushMatrix();
		modelStack.Translate(fo->pos.x, fo->pos.y, fo->pos.z);
		modelStack.Rotate(fo->rotation - 90, 0, 0, 1);
		if (fo->invert)
			modelStack.Scale(-fo->scale.x, fo->scale.y, fo->scale.z);
		else
			modelStack.Scale(fo->scale.x, fo->scale.y, fo->scale.z);
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		RenderMesh(meshList[GEO_TROUT], false, fo->invert);
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		modelStack.PopMatrix();
		break;
	case FishObject::FT_SHARK:
		modelStack.PushMatrix();
		modelStack.Translate(fo->pos.x, fo->pos.y, fo->pos.z);
		modelStack.Rotate(fo->rotation - 90, 0, 0, 1);
		if (fo->invert)
			modelStack.Scale(-fo->scale.x, fo->scale.y, fo->scale.z);
		else
			modelStack.Scale(fo->scale.x, fo->scale.y, fo->scale.z);
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		RenderMesh(meshList[GEO_SHARK], false, fo->invert);
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		modelStack.PopMatrix();
		break;
	}
}

void Scene4FishingPond::spawningOfFish(const double& deltaTime)
{
    if (fishCount < maxFish && player.onElectricity)
	{
		int randNo = Math::RandFloatMinMax(1, 10);
		FishObject * fo = FetchFO();
		fo->active = true;
		if (randNo < chanceOfFish)
		{
			fo->type = FishObject::FT_TROUT;
			fo->scale.Set(1, 1, 1);
			fo->mass = 1.7;
			fo->pos.Set(Math::RandFloatMinMax(18, 24), 4, -1.1);
			fo->vel.Set(Math::RandFloatMinMax(-1, 1), Math::RandFloatMinMax(8, 10), 0);
            if (SceneManager::GetInstance().bAudio == true)
            PlayBloop();
		}
		else
		{
			fo->type = FishObject::FT_SHARK;
			float temp = Math::RandFloatMinMax(4, 10);
			fo->scale.Set(temp, temp, temp);
			fo->mass = temp;
			fo->pos.Set(Math::RandFloatMinMax(19, 23), 4, -1.1);
            fo->vel.Set(Math::RandFloatMinMax(-0.5, 0.5), Math::RandFloatMinMax(2, 5), 0);
            if (SceneManager::GetInstance().bAudio == true)
            PlayBloop();
		}

		

		fishCount += 1;
	}
}
void Scene4FishingPond::displacementOfFish(const double& deltaTime)
{
	for (std::vector<FishObject *>::iterator it = m_foList.begin(); it != m_foList.end(); ++it)
	{
		FishObject *fo = (FishObject *)*it;
		if (fo->active)
		{
			Vector3 acceleration, gravity;
			gravity.Set(0, 1, 0);
			acceleration = (gravity * Math::RandFloatMinMax(1, 15)) * (1 / fo->mass);
			fo->vel -= acceleration * (float)deltaTime;
			if (fo->vel.LengthSquared() > 25)
			{
				fo->vel.Normalize();
				fo->vel *= 5;
				//go->active = false;

			}
			if (fo->pos.y < 4)
			{
				fishCount -= 1;
				fo->active = false;
			}
			
			if (fo->vel.x > 0)
			{
				fo->invert = true;
			}
			else
			{
				fo->invert = false;
			}
			fo->rotation = Math::RadianToDegree(atan2(fo->vel.y, fo->vel.x));
			Mtx44 rotate;
			rotate.SetToRotation(fo->rotation, 0, 0, 1);
			fo->normal = rotate * fo->normal2;
			fo->rotation = Math::RadianToDegree(atan2(fo->normal.y, fo->normal.x));


			if (fo->type == FishObject::FT_TROUT)
			{
				if (Scene3D::getDistXY(player.transform.position, fo->pos, tileMap.GetTileSize()))
				{
					//item in inventory increase herre
					ItemManager::GetInstance().addItem(new Fish(1));
					fishCount -= 1;
					fo->active = false;
				}
				fo->pos += (float)deltaTime * fo->vel * 2;
			}
			if (fo->type == FishObject::FT_SHARK)
			{
				//if (CheckCollision(player, fo, deltaTime))
				if (Scene3D::getDistXY(player.transform.position, fo->pos, fo->scale.x/4))
				{
					//kills player leads him to death screen
					fishCount -= 1;
					fo->active = false;
					SceneManager::GetInstance().chgCurrEnumScene(DEAD);

					player.setVelocity(Vector3(0, 0, 0));
				}
				fo->pos += (float)deltaTime * fo->vel * 4;
			}
			
		}

		
	}
}