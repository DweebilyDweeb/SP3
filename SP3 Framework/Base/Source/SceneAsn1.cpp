//#include "SceneAsn1.h"
//#include "GL\glew.h"
//#include "shader.hpp"
//#include "Utility.h"
//#include "MeshBuilder.h"
//#include "LoadTGA.h"
//#include "LoadOBJ.h"
//#include "LoadHmap.h"
//#include "GenerateRange.h"
//#include "Collision.h"
//#include "Application.h"
//
//SceneAsn1::SceneAsn1() {
//}
//
//SceneAsn1::~SceneAsn1() {
//}
//
//void SceneAsn1::Exit() {
//
//	player.camera = nullptr;
//	delete camera;
//
//	Gun* deleteGun = player.guns[0];
//	player.guns[0] = nullptr;
//	delete deleteGun;
//	deleteGun = player.guns[1];
//	player.guns[1] = nullptr;
//	delete deleteGun;
//
//	bulletManager.ClearBulletInfo();
//
//	Application::GetInstance().audioSystem->GetInstance().ClearAudioList2D();
//	Application::GetInstance().audioSystem->GetInstance().ClearAudioList3D();
//
//	Scene3D::Exit();
//
//}
//
//void SceneAsn1::Init() {
//
//	InitGL();
//
//	//Create & use our shader
//	InitShaders("Shader//Default.vertexshader", "Shader//Default.fragmentshader", DEFAULT);
//	UseShader(DEFAULT);
//
//	Scene3D::Init();
//	InitMeshes();
//
//	InitLights();
//	lights[0].type = Light::LIGHT_DIRECTIONAL;
//	lights[0].position.Set(20, 10, -20);
//	lights[0].on = true;
//	lights[0].power = 1.0f;
//	UpdateLightAttributes(0);
//	
//	InitFog(Color(0.5f, 0.5f, 0.5f), 2, 20.0f, 800.0f, 0.005f);
//
//	camera = new Camera();
//	camera->transform.SetPosition(player.transform.position);
//	camera->transform.SetRotation(player.transform.rotation);
//	InitPlayer();
//
//	InitEnemies();
//
//	//Projection matrix: 45° Field of View, 16:9 ratio, display range : 0.1 unit <-> 1000 units
//	Mtx44 perspective;
//	perspective.SetToPerspective(camera->GetFOV(),
//								 camera->aspectRatio.x / camera->aspectRatio.y,
//								 camera->GetNearClippingPlane(),
//								 camera->GetFarClippingPlane());
//	projectionStack.LoadMatrix(perspective);
//
//	Application::GetInstance().audioSystem->GetInstance().PlayAudio2D("Audio//BGM//Lonely_BGM.flac", true);
//	Application::GetInstance().audioSystem->GetInstance().PlayAudio3D("Audio//Ambient//Thunder.flac", true, 100.0f,
//																	  player.transform.position, player.transform.GetForward(),
//																	  Vector3(0, 20, 200));
//
//}
//
//void SceneAsn1::InitMeshes() {
//
//	for (unsigned int i = 0; i < NUM_GEOMETRY; ++i) {
//		meshList[i] = nullptr;
//	}
//
//	//Environment
//	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("Skyplane", Color(1.0f, 1.0f, 1.0f), 256, 500.0f, 200.0f, 4, 4);
//	meshList[GEO_SKYPLANE]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//Skyplane//Sky_Texture.tga");
//
//	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("Terrain", "Image//Terrain//Terrain_0.raw", heightMap, 16, 16);
//	meshList[GEO_TERRAIN]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//Environment//Grass_1.tga");
//	meshList[GEO_TERRAIN]->textureArray[1] = LoadTGA("Image//Game_Dev_Asn1//Environment//Rock_1.tga");
//	mapScaleXZ = 500.0f;
//	mapScaleY = 25.0f;
//
//	//Guns
//	meshList[GEO_BULLET] = MeshBuilder::GenerateOBJ("Bullet", "OBJ//Game_Dev_Asn1//Bullet.obj");
//	meshList[GEO_BULLET]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//Models//Bullet_Diffuse.tga");
//	meshList[GEO_BULLET]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
//	meshList[GEO_BULLET]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
//	meshList[GEO_BULLET]->material.kSpecular.Set(0.4f, 0.4f, 0.4f);
//	meshList[GEO_BULLET]->material.kShininess = 0.5f;
//	meshList[GEO_RIFLE] = MeshBuilder::GenerateOBJ("Rifle", "OBJ//Game_Dev_Asn1//AKM.obj");
//	meshList[GEO_RIFLE]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//Models//AKM_Diffuse.tga");
//	meshList[GEO_PISTOL] = MeshBuilder::GenerateOBJ("Pistol", "OBJ//Game_Dev_Asn1//45ACP.obj");
//	meshList[GEO_PISTOL]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//Models//45ACP_Diffuse.tga");
//
//	//UI
//	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("Crosshair", Color(1.0f, 1.0f, 1.0f), 1.0f);
//	meshList[GEO_CROSSHAIR]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//UI//Crosshair.tga");
//	meshList[GEO_SCOPE] = MeshBuilder::GenerateQuad("Scope", Color(1.0f, 1.0f, 1.0f), 1.0f);
//	meshList[GEO_SCOPE]->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//UI//Scope.tga");
//
//	//Minimap
//	minimap.mapMesh->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//UI//Minimap.tga");
//	minimap.avatarMesh->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//UI//Minimap_Avatar.tga");
//	minimap.SetMapSize(mapScaleXZ);
//	minimap.SetViewLength(80.0f);
//
//	//Enemy
//	meshList[GEO_ENEMY] = MeshBuilder::GenerateSphere("Enemy", Color(1.0f, 0.0f, 0.0f), 12, 12, 1.0f);
//
//	//Lightning
//	lightningAnimation = MeshBuilder::GenerateSpriteAnimation("Lightning", 1, 10);
//	lightningAnimation->textureArray[0] = LoadTGA("Image//Game_Dev_Asn1//Sprite_Animation//Lightning.tga");
//	lightningAnimation->animation = new Animation(0, 9, true, 1.0f, true);
//
//}
//
//void SceneAsn1::InitPlayer() {
//
//	player.camera = camera;
//	player.guns[0] = new Gun("Rifle", 5, 100.0f, 4.0, 30);
//	player.guns[0]->mesh = meshList[GEO_RIFLE];
//	player.guns[0]->gunShotFile = "Audio//Sound_Effects//Gunshot//AK_47_Gunshot.flac";
//	player.guns[0]->reloadFile = "Audio//Sound_Effects//Reload//Reload.flac";
//	player.guns[1] = new Gun("Pistol", 15, 100.0f, 2.0, 9);
//	player.guns[1]->mesh = meshList[GEO_PISTOL];
//	player.guns[1]->gunShotFile = "Audio//Sound_Effects//Gunshot//45_ACP_Gunshot.flac";
//	player.guns[1]->reloadFile = "Audio//Sound_Effects//Reload//Reload.flac";
//	player.transform.position.Set(0, 0, 0);
//
//	canSwapWeapon = true;
//	gunSway = 0.0f;
//	gunRecoil = 0.0f;
//
//}
//
//void SceneAsn1::InitEnemies() {
//
//	for (unsigned int i = 0; i < 5; ++i) {
//		enemies[i].health = 25;
//		enemies[i].radius = 0.5f;
//		enemies[i].transform.position.Set(20 * cos(Math::DegreeToRadian(i * 72)), 13, 20 * sin(Math::DegreeToRadian(i * 72)));
//		enemies[i].timer = 0.0;
//	}
//
//}
//
//void SceneAsn1::ResetEnemy() {
//
//	for (unsigned int i = 0; i < 5; ++i) {
//		if (enemies[i].health <= 0 && enemies[i].timer > 10.0) {
//			enemies[i].health = 25;
//			enemies[i].timer = 0.0;
//		}
//	}
//
//}
//
//void SceneAsn1::Update(const double& deltaTime) {
//
//	ResetEnemy();
//
//	for (unsigned int i = 0; i < 5; ++i) {
//		if (enemies[i].health <= 0) {
//			enemies[i].timer += deltaTime;
//			if (enemies[i].transform.position.y > 7.0f) {
//				enemies[i].transform.position.y -= deltaTime * 3.0f;
//				if (enemies[i].transform.position.y < 7.0f) {
//					enemies[i].transform.position.y = 7.0f;
//				}
//			}
//		} else {
//			if (enemies[i].transform.position.y < 13.0f) {
//				enemies[i].transform.position.y += deltaTime * 3.0f;
//				if (enemies[i].transform.position.y > 13.0f) {
//					enemies[i].transform.position.y = 13.0f;
//				}
//			}
//		}
//	}
//
//	for (vector<BulletInfo>::iterator iter = bulletManager.GetBulletInfos().begin(); iter != bulletManager.GetBulletInfos().end(); ++iter) {
//		if (iter->GetStatus()) {
//			for (unsigned int i = 0; i < 5; ++i) {
//				if (enemies[i].health > 0 && LineSphereCollide(iter->GetPosition(), iter->GetDirection(), deltaTime * iter->GetSpeed(), enemies[i].transform.position, enemies[i].radius)) {
//					enemies[i].health -= iter->GetDamage();
//					iter->SetStatus(false);
//					Application::GetInstance().audioSystem->GetInstance().PlayAudio3D("Audio//Sound_Effects//Ricochet.flac",
//																		  false, 5.0f,
//																		  player.transform.position,
//																		  player.transform.GetForward(),
//																		  enemies[i].transform.position);
//					break;
//				}
//			}
//		}
//	}
//
//	bulletManager.Update(deltaTime);
//	player.GetActiveGun()->Update(deltaTime);
//
//	if (player.onGround) {
//		gunSway += deltaTime * player.rigidBody.velocity.LengthSquared() * 0.1f;
//	}
//
//	if (gunRecoil > 0.0f) {
//		gunRecoil -= player.GetActiveGun()->GetFireRate() * deltaTime / 20.0f;
//	}
//	if (gunRecoil < 0.0f) {
//		gunRecoil = 0.0f;
//	}
//
//	minimap.UpdateMap(player.transform.position, player.transform.rotation.y);
//	if (player.isSprinting == false && minimap.GetViewLength() > 90.0f) {
//		minimap.DecreaseViewLength(deltaTime * 100.0f);
//		if (minimap.GetViewLength() < 90.0f) {
//			minimap.SetViewLength(90.0f);
//		}
//	} else if (player.isSprinting && minimap.GetViewLength() < 140.0f) {
//		minimap.IncreaseViewLength(deltaTime * 100.0f);
//		if (minimap.GetViewLength() > 140.0f) {
//			minimap.SetViewLength(140.0f);
//		}
//	}
//
//	lightningAnimation->Update(deltaTime);
//
//	if (player.transform.position.x > 240) {
//		player.transform.position.x = 240;
//	} else if (player.transform.position.x < -240) {
//		player.transform.position.x = -240;
//	}
//
//	if (player.transform.position.z > 240) {
//		player.transform.position.z = 240;
//	} else if (player.transform.position.z < -240) {
//		player.transform.position.z = -240;
//	}
//
//	Application::GetInstance().audioSystem->GetInstance().UpdateListener3D(camera->transform.GetPosition(), camera->transform.GetForward(), Vector3(0, 1, 0));
//	Application::GetInstance().audioSystem->GetInstance().Update();
//
//}
//
//void SceneAsn1::Render() {
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//	SetToCameraView(camera);
//
//	UpdateLights();
//
//	EnableFog(true);
//	Render3D();
//		
//	SetHUD(true, camera->aspectRatio.x, camera->aspectRatio.y, 10.0f);
//	Render2D();
//	SetHUD(false);
//
//}
//
//void SceneAsn1::Render2D() {
//
//	//UI
//	if (!player.isZoomed) {
//		RenderMeshIn2D(meshList[GEO_CROSSHAIR], 1.0f, 0.0f, 0.0f, 0.0f);
//		RenderMeshIn2D(player.GetActiveGun()->mesh, 5.0f, -0.85 * camera->aspectRatio.x, -0.8 * camera->aspectRatio.y, 0, 90, 0);
//		RenderTextOnScreen(fontList[FONT_CONSOLAS], "Ammo: " + std::to_string(player.GetActiveGun()->GetMagAmmo()) + "/" + std::to_string(player.GetActiveGun()->GetMagSize()), Color(0.0f, 1.0f, 0.0f), 0.5f, -0.99f * camera->aspectRatio.x, -0.7 * camera->aspectRatio.y);
//		RenderMinimap();
//	} else {
//		float scale = camera->aspectRatio.y;
//		if (camera->aspectRatio.x < camera->aspectRatio.y) {
//			scale = camera->aspectRatio.x;
//		}
//		RenderMeshIn2D(meshList[GEO_SCOPE], 2.0f * scale);
//	}
//
//}
//
//void SceneAsn1::Render3D() {
//
//	//Skyplane
//	modelStack.PushMatrix();
//		modelStack.Translate(player.transform.position.x, -50.0f, player.transform.position.z);
//		RenderMesh(meshList[GEO_SKYPLANE], false);
//	modelStack.PopMatrix();
//
//	//Terrain
//	modelStack.PushMatrix();
//		modelStack.Scale(mapScaleXZ, mapScaleY, mapScaleXZ);
//		RenderMesh(meshList[GEO_TERRAIN], true);
//	modelStack.PopMatrix();
//
//	RenderPlayerGun();
//	RenderBullets();
//
//	RenderEnemy();
//
//	modelStack.PushMatrix();
//		modelStack.Translate(0, 50, 200);
//		modelStack.Rotate(180, 0, 1, 0);
//		modelStack.Scale(100, 100, 1);
//		RenderSpriteAnimation(lightningAnimation, false);
//	modelStack.PopMatrix();
//
//}
//
//void SceneAsn1::RenderEnemy() {
//
//	for (unsigned int i = 0; i < 5; ++i) {
//		modelStack.PushMatrix();
//			modelStack.Translate(enemies[i].transform.position.x, enemies[i].transform.position.y, enemies[i].transform.position.z);
//			modelStack.Scale(enemies[i].radius / 2.0f, enemies[i].radius / 2.0f, enemies[i].radius / 2.0f);
//			RenderMesh(meshList[GEO_ENEMY], true);
//		modelStack.PopMatrix();
//	}
//
//}
//
//void SceneAsn1::RenderPlayerGun() {
//
//	if (player.GetActiveGun() != nullptr) {
//		modelStack.PushMatrix();
//			modelStack.Translate(camera->transform.GetPosition().x, camera->transform.GetPosition().y, camera->transform.GetPosition().z);
//			modelStack.Rotate(camera->transform.GetRotation().y, 0, 1, 0);
//			modelStack.Rotate(camera->transform.GetRotation().x, 1, 0, 0);
//			modelStack.Rotate(camera->transform.GetRotation().z, 0, 0, 1);
//			if (!player.isSprinting) {
//				modelStack.Translate((sin(gunSway) * 0.001f) - 0.12f, -0.1f, 0.37f - gunRecoil);
//			} else {
//				float offset = sin(gunSway * 0.4f) * 0.01f;
//				modelStack.Translate(0.0f, -0.15f + offset, 0.37f + offset * 0.2f);
//				modelStack.Rotate(90, 0, 1, 0);
//				modelStack.Rotate(15, 1, 0, 0);
//			}
//			RenderMesh(player.GetActiveGun()->mesh, true);
//		modelStack.PopMatrix();
//	}
//
//}
//
//void SceneAsn1::RenderBullets() {
//
//	int numBullets = 0;
//
//	for (vector<BulletInfo>::const_iterator iter = bulletManager.GetBulletInfos().begin(); iter != bulletManager.GetBulletInfos().end(); ++iter) {
//		if (iter->GetStatus()) {
//			modelStack.PushMatrix();
//				modelStack.Translate(iter->GetPosition().x, iter->GetPosition().y, iter->GetPosition().z);
//				modelStack.Rotate(iter->GetRotation().y, 0, 1, 0);
//				modelStack.Rotate(iter->GetRotation().x, 1, 0, 0);
//				modelStack.Rotate(iter->GetRotation().z, 0, 0, 1);
//				RenderMesh(meshList[GEO_BULLET], true);
//			modelStack.PopMatrix();
//			++numBullets;
//		}
//	}
//
//}
//
//void SceneAsn1::RenderMinimap() {
//	
//	RenderMeshIn2D(minimap.borderMesh, 5.0f, camera->aspectRatio.x * 0.8f, -camera->aspectRatio.y * 0.7f, 0.0f, 0.0f, 0.0f);
//	RenderMeshIn2D(minimap.mapMesh, 5.0f, camera->aspectRatio.x * 0.8f, -camera->aspectRatio.y * 0.7f, 0.0f, 0.0f, 0.0f);
//	RenderMeshIn2D(minimap.avatarMesh, 5.0f, camera->aspectRatio.x * 0.8f, -camera->aspectRatio.y * 0.7f, 0.0f, 0.0f, 0.0f);
//
//}
//
//void SceneAsn1::GetInput(const InputInfo& inputInfo, const double& deltaTime) {
//
//	player.UpdatePosition(inputInfo, deltaTime);
//	TerrainCollision(deltaTime);
//	player.UpdateRotation(inputInfo, deltaTime);
//
//	if (inputInfo.keysDown[SWAP_WEAPON] == false) {
//		canSwapWeapon = true;
//	}
//
//	if (player.isSprinting == false) {
//		if (inputInfo.keysDown[SHOOT]) {
//			if (player.GetActiveGun()->Shoot()) {
//				BulletInfo* bullet = &(bulletManager.FetchBulletInfo());
//				bullet->Init(camera->transform.GetPosition() + (camera->transform.GetForward() * 0.3f)
//							 + (GenerateRange(-0.005f, 0.005f) * -camera->transform.GetLeft())
//							 + (GenerateRange(-0.005f, 0.005f) * camera->transform.GetUp()),
//							 camera->transform.GetRotation(), player.GetActiveGun()->GetSpeed(),
//							 5.0f, player.GetActiveGun()->GetDamage());
//				gunRecoil = 0.025f;
//				Application::GetInstance().audioSystem->GetInstance().PlayAudio2D(player.GetActiveGun()->gunShotFile, false);
//			}
//		} else if (inputInfo.keysDown[SWAP_WEAPON] && canSwapWeapon) {
//			player.SwapWeapon();
//			canSwapWeapon = false;
//		} else if (inputInfo.keysDown[RELOAD]) {
//			if (player.GetActiveGun()->Reload()) {
//				Application::GetInstance().audioSystem->GetInstance().PlayAudio2D(player.GetActiveGun()->reloadFile, false);
//			}
//		}
//	}
//
//	while (gunRecoil > 180.0f) {
//		gunRecoil -= 180.0f;
//	}
//
//}
//
//void SceneAsn1::TerrainCollision(const double& deltaTime) {
//
//	float offset = 1.0f;
//	float terrainHeightLeft = mapScaleY * ReadHeightMap(heightMap, (player.transform.position.x - offset) / mapScaleXZ, player.transform.position.z / mapScaleXZ);
//	float terrainHeightRight = mapScaleY * ReadHeightMap(heightMap, (player.transform.position.x + offset) / mapScaleXZ, player.transform.position.z / mapScaleXZ);
//	float terrainHeightFront = mapScaleY * ReadHeightMap(heightMap, player.transform.position.x / mapScaleXZ, (player.transform.position.z + offset) / mapScaleXZ);
//	float terrainHeightBack = mapScaleY * ReadHeightMap(heightMap, player.transform.position.x / mapScaleXZ, (player.transform.position.z - offset) / mapScaleXZ);
//	float terrainHeightCentre = mapScaleY * ReadHeightMap(heightMap, player.transform.position.x / mapScaleXZ, player.transform.position.z/ mapScaleXZ);
//	float terrainHeight = (terrainHeightLeft + terrainHeightRight + terrainHeightFront + terrainHeightBack + terrainHeightCentre) / 5.0f;
//
//	if (player.transform.position.y > terrainHeight) {
//		player.onGround = false;
//	} else if (player.transform.position.y <= terrainHeight) {
//		player.onGround = true;
//		player.transform.position.y = terrainHeight;
//	}
//
//}