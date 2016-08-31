#include "Scene3D.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Utility.h"
#include "MeshBuilder.h"
#include "Application.h"
#include "LoadTGA.h"
#include "InputManager.h"
#include "ItemManager.h"
#include "SceneManager.h"

//#include "Application.h"

//Constructor(s) & Destructor


Scene3D::Scene3D() {

	referenceAxes = MeshBuilder::GenerateAxes("Reference Axes", 5000000.0f, 5000000.0f, 5000000.0f);
	fontList[FONT_CONSOLAS] = MeshBuilder::GenerateText("Consolas", 16, 16, "Image//Fonts//Consolas.tga");
	currentShader = NONE;
	InitAttributeUI();
	InitInventoryUI();
	InitSceneName();
	InitShowDay();
	InitWin();

	zoomAmount = 1;
	zoomOffsetY = 0;
	zoomOffsetX = 0;
	dir = 1;
	distMoved = 0.f;
	isFading = false;
	fadeAway = 0.f;
}

Scene3D::~Scene3D() {
}

//Exit

void Scene3D::Exit() {

	DeleteShaders();
	glDeleteVertexArrays(1, &vertexArrayID);
	delete referenceAxes;
	delete fontList[FONT_CONSOLAS];
	for (unsigned int i = 0; i < TOTAL_TITLES; ++i) {
		if (titleList[i]) {
			delete titleList[i];
		}
	}
	for (unsigned int i = 0; i < TOTAL_DAY; ++i) {
		if (dayList[i]) {
			delete dayList[i];
		}
	}
	
	while (Vegetable::GetInstance().m_carrotList.size() > 0) {
		CarrotObject *im = Vegetable::GetInstance().m_carrotList.back();
		delete im;
		Vegetable::GetInstance().m_carrotList.pop_back();
	}
	while (Vegetable::GetInstance().m_cornList.size() > 0) {
		CornObject *im = Vegetable::GetInstance().m_cornList.back();
		delete im;
		Vegetable::GetInstance().m_cornList.pop_back();
	}
	while (Vegetable::GetInstance().m_potatoList.size() > 0) {
		PotatoObject *im = Vegetable::GetInstance().m_potatoList.back();
		delete im;
		Vegetable::GetInstance().m_potatoList.pop_back();
	}
	while (Vegetable::GetInstance().m_cabbageList.size() > 0) {
		CabbageObject *im = Vegetable::GetInstance().m_cabbageList.back();
		delete im;
		Vegetable::GetInstance().m_cabbageList.pop_back();
	}

	delete healthBar;
	delete statsBar;
	delete healthUiBackground;
	delete statUiBackground;
	delete barBackground;
	delete inventoryBar;
    delete pause;
    delete bigClock;
    delete clockHandH;
	delete clockHandM;
	delete winScreen;
}

void Scene3D::DeleteShaders() {

	for (unsigned int n = 0; n < NUM_SHADER; ++n) {
		glDeleteProgram(shaderProgramID[n]);
	}

}

//Initialisation

void Scene3D::Init() {

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

}

void Scene3D::InitGL() {

	//Dark Blue background
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	//Enable Culling
	//glEnable(GL_CULL_FACE);
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Polygon Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Stencil Buffer
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//Outline
	glEnable(GL_LINE_SMOOTH);

}

void Scene3D::InitShaders(const char* vertexShaderFile, const char* fragmentShaderFile, SHADER_TYPE shaderType) {

	//Load Shader
	shaderProgramID[shaderType] = LoadShaders(vertexShaderFile, fragmentShaderFile);

	//Get a handle for our uniform
	shaderParameters[shaderType * U_TOTAL + U_MVP] = glGetUniformLocation(shaderProgramID[shaderType], "MVP");
	shaderParameters[shaderType * U_TOTAL + U_MODELVIEW] = glGetUniformLocation(shaderProgramID[shaderType], "MV");
	shaderParameters[shaderType * U_TOTAL + U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(shaderProgramID[shaderType], "MV_inverse_transpose");
	shaderParameters[shaderType * U_TOTAL + U_MATERIAL_AMBIENT] = glGetUniformLocation(shaderProgramID[shaderType], "material.kAmbient");
	shaderParameters[shaderType * U_TOTAL + U_MATERIAL_DIFFUSE] = glGetUniformLocation(shaderProgramID[shaderType], "material.kDiffuse");
	shaderParameters[shaderType * U_TOTAL + U_MATERIAL_SPECULAR] = glGetUniformLocation(shaderProgramID[shaderType], "material.kSpecular");
	shaderParameters[shaderType * U_TOTAL + U_MATERIAL_SHININESS] = glGetUniformLocation(shaderProgramID[shaderType], "material.kShininess");
	shaderParameters[shaderType * U_TOTAL + U_LIGHTENABLED] = glGetUniformLocation(shaderProgramID[shaderType], "lightEnabled");
	shaderParameters[shaderType * U_TOTAL + U_NUMLIGHTS] = glGetUniformLocation(shaderProgramID[shaderType], "numLights");

	//Lights
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT0_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[0].exponent");
	
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT1_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[1].exponent");
	
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT2_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[2].exponent");
					 
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT3_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[3].exponent");
					 
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT4_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[4].exponent");
					 
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT5_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[5].exponent");
					 
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT6_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[6].exponent");
					 
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_ON] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].on");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].type");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_POSITION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].position_cameraspace");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].color");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_POWER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].power");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_KC] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].kC");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_KL] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].kL");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_KQ] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].kQ");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_SPOTDIRECTION] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].spotDirection");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_COSCUTOFF] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].cosCutoff");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_COSINNER] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].cosInner");
	shaderParameters[shaderType * U_TOTAL + U_LIGHT7_EXPONENT] = glGetUniformLocation(shaderProgramID[shaderType], "lights[7].exponent");

	//Get a handle for our "colorTexture" uniform
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED0] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[0]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[1]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED2] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[2]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED3] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[3]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED4] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[4]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED5] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[5]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED6] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[6]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE_ENABLED7] = glGetUniformLocation(shaderProgramID[shaderType], "colorTextureEnabled[7]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE0] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[0]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE1] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[1]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE2] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[2]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE3] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[3]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE4] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[4]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE5] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[5]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE6] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[6]");
	shaderParameters[shaderType * U_TOTAL + U_COLOR_TEXTURE7] = glGetUniformLocation(shaderProgramID[shaderType], "colorTexture[7]");

	//Get a handle for our "textColor" uniform
	shaderParameters[shaderType * U_TOTAL + U_TEXT_ENABLED] = glGetUniformLocation(shaderProgramID[shaderType], "textEnabled");
	shaderParameters[shaderType * U_TOTAL + U_TEXT_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "textColor");

	shaderParameters[shaderType * U_TOTAL + U_FOG_ENABLED] = glGetUniformLocation(shaderProgramID[shaderType], "fogParam.enabled");
	shaderParameters[shaderType * U_TOTAL + U_FOG_COLOR] = glGetUniformLocation(shaderProgramID[shaderType], "fogParam.color");
	shaderParameters[shaderType * U_TOTAL + U_FOG_START] = glGetUniformLocation(shaderProgramID[shaderType], "fogParam.start");
	shaderParameters[shaderType * U_TOTAL + U_FOG_END] = glGetUniformLocation(shaderProgramID[shaderType], "fogParam.end");
	shaderParameters[shaderType * U_TOTAL + U_FOG_DENSITY] = glGetUniformLocation(shaderProgramID[shaderType], "fogParam.density");
	shaderParameters[shaderType * U_TOTAL + U_FOG_TYPE] = glGetUniformLocation(shaderProgramID[shaderType], "fogParam.type");

}

void Scene3D::InitLights() {

	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_TEXT_ENABLED], 0);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_NUMLIGHTS], 8);

	for (unsigned int n = 0; n < sizeof(lights) / sizeof(*lights); ++n) {
		lights[n].on = false;
		lights[n].type = Light::LIGHT_POINT;
		lights[n].position.Set(0, 1, 0);
		lights[n].color.Set(1, 1, 1);
		lights[n].power = 1.0f;
		lights[n].kC = 1.0f;
		lights[n].kL = 0.01f;
		lights[n].kQ = 0.001f;
		lights[n].cosCutoff = cos(Math::DegreeToRadian(60));
		lights[n].cosInner = cos(Math::DegreeToRadian(50));
		lights[n].exponent = 3.0f;
		lights[n].spotDirection.Set(0.f, 1.f, 0.f);

		glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_ON + n], lights[n].on);
		glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_TYPE + n], lights[n].type);
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_COLOR + n], 1, &lights[n].color.r);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POWER + n], lights[n].power);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_KC + n], lights[n].kC);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_KL + n], lights[n].kL);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_KQ + n], lights[n].kQ);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_COSCUTOFF + n], lights[n].cosCutoff);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_COSINNER + n], lights[n].cosInner);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_EXPONENT + n], lights[n].exponent);
		//SpotDirection & Position are done in UpdateLights.

	}

}

void Scene3D::InitFog(Color color, int fogType, float start, float end, float density) {

	glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_FOG_COLOR], 1, &color.r);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_FOG_START], start);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_FOG_END], end);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_FOG_DENSITY], density);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_FOG_ENABLED], 0);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_FOG_TYPE], fogType);

}



//Update

void Scene3D::Update(const double& deltaTime) {
	if (Application::clock->getDay() >= 10){
		UpdateWin(deltaTime);
		//Application::clock->setActive(false);
	}
    //This line below lags up the game. Must be checked
	if (SceneManager::GetInstance().getCurrSceneEnum() != SUB_DRAGON && Application::clock->getDay() < 2)
	{
		UpdateAttributeUI(deltaTime);
		updateClouds(deltaTime);
		Application::clock->UpdateTime(deltaTime);

		//Add the condition if it's not the win scene so time doesnt update
		if (Application::clock->getActive() == false)
		{
			ResetVegetable();
			SceneManager::GetInstance().chgCurrEnumScene(HOME);
			SceneManager::GetInstance().setPrevScene(WHEAT);
			SceneManager::GetInstance().isChgScene(false);
			Application::clock->setActive(true);
		}
	}
	static float timer = 0.f;
	timer += (float)deltaTime;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_CHEAT0] && timer > 0.5f)
	{
		CheatCodeFood();
		timer = 0.f;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_CHEAT1] && timer > 0.5f)
	{
		CheatCodeTimeFastForward();
		timer = 0.f;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_CHEAT2] && timer > 0.5f)
	{
		CheatCodeTimeNormal();
		timer = 0.f;
	}
}

//Things that need to be updated every frame.
void Scene3D::UpdateLights() {

	for (unsigned int n = 0; n < sizeof(lights)/sizeof(*lights); ++n) {
		glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_ON + n], lights[n].on);
		if (lights[n].on == true) {
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_TYPE + n], lights[n].type);
			if (lights[n].type == Light::LIGHT_DIRECTIONAL) {
				Vector3 lightDir(lights[n].position.x, lights[n].position.y, lights[n].position.z);
				Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
				glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POSITION + n], 1, &lightDirection_cameraspace.x);
			} else if (lights[n].type == Light::LIGHT_SPOT) {
				Position lightPosition_cameraspace = viewStack.Top() * lights[n].position;
				glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POSITION + n], 1, &lightPosition_cameraspace.x);
				Vector3 spotDirection_cameraspace = viewStack.Top() * lights[n].spotDirection;
				glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_SPOTDIRECTION + n], 1, &spotDirection_cameraspace.x);
			} else { //Point Light
				Position lightPosition_cameraspace = viewStack.Top() * lights[n].position;
				glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POSITION + n], 1, &lightPosition_cameraspace.x);
			}
		}
	}

}

//Only called when a light changes something other than position.
void Scene3D::UpdateLightAttributes(unsigned int n) {

	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_ON + n], lights[n].on);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_TYPE + n], lights[n].type);
	glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_COLOR + n], 1, &lights[n].color.r);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POWER + n], lights[n].power);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_KC + n], lights[n].kC);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_KL + n], lights[n].kL);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_KQ + n], lights[n].kQ);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_COSCUTOFF + n], lights[n].cosCutoff);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_COSINNER + n], lights[n].cosInner);
	glUniform1f(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_EXPONENT+ n], lights[n].exponent);

	if (lights[n].type == Light::LIGHT_DIRECTIONAL) {
		Vector3 lightDir(lights[n].position.x, lights[n].position.y, lights[n].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POSITION + n], 1, &lightDirection_cameraspace.x);
	} else if (lights[n].type == Light::LIGHT_SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * lights[n].position;
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POSITION + n], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[n].spotDirection;
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_SPOTDIRECTION + n], 1, &spotDirection_cameraspace.x);
	} else { //Point Light
		Position lightPosition_cameraspace = viewStack.Top() * lights[n].position;
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_LIGHT0_POSITION + n], 1, &lightPosition_cameraspace.x);
	}

}

//Rendering

void Scene3D::UseShader(SHADER_TYPE shaderType) {
	
	if (currentShader != shaderType) {
		glUseProgram(shaderProgramID[shaderType]);
		currentShader = shaderType;
	}

}

void Scene3D::SetToCameraView(Camera* camera, float zoom) {

	if (zoom == 1)
	{
		modelStack.LoadIdentity();
		viewStack.LoadIdentity();
		viewStack.LookAt(camera->transform.position.x + zoomOffsetX, camera->transform.position.y + zoomOffsetY, camera->transform.position.z,
			camera->transform.position.x + camera->transform.GetForward().x + zoomOffsetX,
			camera->transform.position.y + camera->transform.GetForward().y +zoomOffsetY,
			camera->transform.position.z + camera->transform.GetForward().z,
			camera->transform.GetUp().x, camera->transform.GetUp().y, camera->transform.GetUp().z);

		float aspectRatio = static_cast<float>(camera->aspectRatio.x) / static_cast<float>(camera->aspectRatio.y);
		if (camera->IsOrtho()) {
			Mtx44 orthoMatrix;
			orthoMatrix.SetToOrtho(-aspectRatio * camera->GetOrthoSize() / zoomAmount, aspectRatio * camera->GetOrthoSize() / zoomAmount,
				-camera->GetOrthoSize() / zoomAmount, camera->GetOrthoSize() / zoomAmount,
				camera->GetNearClippingPlane(), camera->GetFarClippingPlane());

			projectionStack.LoadMatrix(orthoMatrix);
		}
		else {
			Mtx44 perspMatrix;
			perspMatrix.SetToPerspective(camera->GetFOV(),
				aspectRatio,
				camera->GetNearClippingPlane(),
				camera->GetFarClippingPlane());

			projectionStack.LoadMatrix(perspMatrix);
		}
		showStats = false;
	}
	else
	{
		modelStack.LoadIdentity();
		viewStack.LoadIdentity();
		viewStack.LookAt(camera->transform.position.x, camera->transform.position.y, camera->transform.position.z,
			camera->transform.position.x + camera->transform.GetForward().x,
			camera->transform.position.y + camera->transform.GetForward().y ,
			camera->transform.position.z + camera->transform.GetForward().z,
			camera->transform.GetUp().x, camera->transform.GetUp().y, camera->transform.GetUp().z);

		float aspectRatio = static_cast<float>(camera->aspectRatio.x) / static_cast<float>(camera->aspectRatio.y);
		if (camera->IsOrtho()) {
			Mtx44 orthoMatrix;
			orthoMatrix.SetToOrtho(-aspectRatio * camera->GetOrthoSize(), aspectRatio * camera->GetOrthoSize(),
				-camera->GetOrthoSize(), camera->GetOrthoSize(),
				camera->GetNearClippingPlane(), camera->GetFarClippingPlane());

			projectionStack.LoadMatrix(orthoMatrix);
		}
		else {
			Mtx44 perspMatrix;
			perspMatrix.SetToPerspective(camera->GetFOV(),
				aspectRatio,
				camera->GetNearClippingPlane(),
				camera->GetFarClippingPlane());

			projectionStack.LoadMatrix(perspMatrix);
		}
	}
}

void Scene3D::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	renderSceneName();
	RenderAttributeUI();
	RenderInventoryUI();
	RenderShowDay();
	RenderWin();
    PauseMenu();
}
void Scene3D::RenderSub() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Scene3D::Render2D() {
}

void Scene3D::Render3D() {
}

void Scene3D::RenderAxes() {

	modelStack.PushMatrix();
		modelStack.LoadIdentity();
		RenderMesh(referenceAxes, false);
	modelStack.PopMatrix();

}

void Scene3D::EnableFog(bool fogOn) {

	if (fogOn == true) {
		glUniform1i(shaderParameters[currentShader * U_TOTAL + U_FOG_ENABLED], 1);
	} else {
		glUniform1i(shaderParameters[currentShader * U_TOTAL + U_FOG_ENABLED], 0);
	}

}

void Scene3D::SetHUD(bool mode, float x, float y, float z) {

	if (mode == true) {
		glDisable(GL_DEPTH_TEST);
		EnableFog(false);
		//Projection Matrix
		Mtx44 ortho;
		ortho.SetToOrtho(-x, x, -y, y, -z, z);
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
	} else {
		projectionStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}

}

void Scene3D::RenderMeshIn2D(Mesh *mesh, float sizeX, float sizeY, float x, float y, float z, float offsetX, float offsetY,float rotationX, float rotationY, float rotationZ) {

	viewStack.PushMatrix();
		viewStack.LoadIdentity();
		modelStack.PushMatrix();
			modelStack.LoadIdentity();
			modelStack.Translate(x, y, z);
			modelStack.Rotate(rotationY, 0, 1, 0);
			modelStack.Rotate(rotationX, 1, 0, 0);
			modelStack.Rotate(rotationZ, 0, 0, 1);
			modelStack.Scale(sizeX, sizeY, sizeX);
			modelStack.Translate(offsetX, offsetY, 0);

			Mtx44 MVP, modelView, modelView_inverse_transpose;

			MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
			glUniformMatrix4fv(shaderParameters[currentShader * U_TOTAL + U_MVP], 1, GL_FALSE, &MVP.a[0]);
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHTENABLED], 0);

			for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
				if (mesh->textureArray[i] > 0) {
					glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE_ENABLED0 + i], 1);
					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
					glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE0 + i], i);
				} else {
					glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE_ENABLED0 + i], 0);
				}
			}

			mesh->Render();
			if (mesh->textureArray[0] > 0) 	{
				glBindTexture(GL_TEXTURE_2D, 0);
			}

		modelStack.PopMatrix();
	viewStack.PopMatrix();

}

void Scene3D::RenderMesh(Mesh* mesh, bool enableLight, bool invert) {

	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(shaderParameters[currentShader * U_TOTAL + U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(shaderParameters[currentShader * U_TOTAL + U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	glUniformMatrix4fv(shaderParameters[currentShader * U_TOTAL + U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight) {
		glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHTENABLED], 1);

		//Load Material
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(shaderParameters[currentShader * U_TOTAL + U_MATERIAL_SHININESS], mesh->material.kShininess);
	} else {
		glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHTENABLED], 0);
	}

	for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
		if (mesh->textureArray[i] > 0) {
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE_ENABLED0 + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE0 + i], i);
		} else {
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE_ENABLED0 + i], 0);
		}
	}

	//mesh->Render();
	
	if (invert)
	{
		glFrontFace(GL_CW);
	}
	mesh->Render();
	if (invert)
		glFrontFace(GL_CCW);
	if (mesh->textureArray[0] > 0) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void Scene3D::RenderSpriteAnimation(SpriteAnimation* sa, bool enableLight, bool invert) {

	Mesh* mesh = dynamic_cast<Mesh*>(sa);

	if (mesh) {
		RenderMesh(mesh, enableLight, invert);
	}

}

void Scene3D::RenderText(Mesh* mesh, std::string text, Color color) {

	if (!mesh || mesh->textureArray[0] <= 0) {
		return;
	}

	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_TEXT_ENABLED], 1);
	glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_TEXT_COLOR], 1, &color.r);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHTENABLED], 0);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE_ENABLED0], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE0], 0);
	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(shaderParameters[currentShader * U_TOTAL + U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(shaderParameters[currentShader * U_TOTAL + U_TEXT_ENABLED], 0);

}

void Scene3D::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z) {

	if (!mesh || mesh->textureArray[0] <= 0) {
		return;
	}

	viewStack.PushMatrix();
		viewStack.LoadIdentity();
		modelStack.PushMatrix();
			modelStack.LoadIdentity();
			modelStack.Translate(x, y, z);
			modelStack.Scale(size, size, size);
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_TEXT_ENABLED], 1);
			glUniform3fv(shaderParameters[currentShader * U_TOTAL + U_TEXT_COLOR], 1, &color.r);
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_LIGHTENABLED], 0);
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE_ENABLED0], 1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_COLOR_TEXTURE0], 0);
			for (unsigned i = 0; i < text.length(); ++i) {
				Mtx44 characterSpacing;
				characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
				Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
				glUniformMatrix4fv(shaderParameters[currentShader * U_TOTAL + U_MVP], 1, GL_FALSE, &MVP.a[0]);

				mesh->Render((unsigned)text[i] * 6, 6);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			glUniform1i(shaderParameters[currentShader * U_TOTAL + U_TEXT_ENABLED], 0);
		modelStack.PopMatrix();
	viewStack.PopMatrix();

}

void Scene3D::InitAttributeUI()
{
	healthBar = MeshBuilder::GenerateQuad("healthBar", Color(1, 0, 0), 1);
	statsBar = MeshBuilder::GenerateQuad("statsBar", Color(1, 0.5, 0), 1);
	healthUiBackground = MeshBuilder::GenerateQuad("uiBackground", Color(1, 1, 1), 1);
	healthUiBackground->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//health2.tga");
	statUiBackground = MeshBuilder::GenerateQuad("uiBackground", Color(1, 1, 1), 1);
    statUiBackground->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//stats2.tga");
    barBackground = MeshBuilder::GenerateQuad("barBackground", Color(0.5, 0.5, 0.5), 1);
    barBackground->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//border.tga");
    bigClock = MeshBuilder::GenerateQuad("Clock", Color(1, 1, 1));
    bigClock->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clockWOHands.tga");
    clockHandH = MeshBuilder::GenerateQuad("Hour Hand", Color(1, 1, 1));
    clockHandH->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clockWithHands.tga");
	clockHandM = MeshBuilder::GenerateQuad("Minute Hand", Color(1, 1, 1));
	clockHandM->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//clockWithHands.tga");
	//statUiBackground->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//health.tga");
    pause = MeshBuilder::GenerateQuad("Pause", Color(1, 1, 1));
    pause->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//pause.tga");
	Application::mother->Init();
	Application::son->Init();
	Application::daughter->Init();

	showStats = false;
}
void Scene3D::UpdateAttributeUI(const double& deltaTime)
{
	Application::mother->boundStats();
	Application::son->boundStats();
	Application::daughter->boundStats();

	Application::mother->Update(deltaTime);
	Application::son->Update(deltaTime);
	Application::daughter->Update(deltaTime);

 /*   Application::mother->boundStats();
    Application::son->boundStats();
    Application::daughter->boundStats();*/


	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOW_ATTRIBUTES]) {
		showStats = true;
	}
	else
	{
		showStats = false;
	}

	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_SHOW_ATTRIBUTES]){
		showStats = false;
	}
}
void Scene3D::RenderAttributeUI()
{
	if (!showStats)
	{
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		if (Application::mother->getHealth() > 0)
			RenderMeshIn2D(healthBar, Application::mother->getHealth() / 20000, 0.5, -14.4, 10.2, 5, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -14.4, 10.2, 5, 0.5);
		if (Application::son->getHealth() > 0)
			RenderMeshIn2D(healthBar, Application::son->getHealth() / 20000, 0.5, -14.4, 8.7, 5, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -14.4, 8.7, 5, 0.5);
		if (Application::daughter->getHealth() > 0)
			RenderMeshIn2D(healthBar, Application::daughter->getHealth() / 20000, 0.5, -14.4, 7.2, 5, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -14.4, 7.2, 5, 0.5);
		
		RenderMeshIn2D(healthUiBackground, 11, 11, -12.9, 9.5);

		RenderMeshIn2D(bigClock, 5, 5, 13, 9.1, 0, 0, 0, 0, 0, 0);
		RenderMeshIn2D(clockHandH, 1.5, 1, 13.08, 9.034, 1, -0.38, 0, 0, 0, Application::clock->getRotation());
		RenderMeshIn2D(clockHandM, 2, 1, 13.08, 9.034, 1, -0.38, 0, 0, 0, -90);

		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	}
	else
	{
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		

		if (Application::son->getProtein() > 0)
			RenderMeshIn2D(statsBar, Application::son->getProtein() * 0.05f, 0.5, -5.5, -0.3, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -5.5, -0.3, 5, 0.5);
		if (Application::son->getCarbohydrates() > 0)
			RenderMeshIn2D(statsBar, Application::son->getCarbohydrates() * 0.05f, 0.5, -5.5, -2.75, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -5.5, -2.75, 5, 0.5);
		if (Application::son->getFats() > 0)
			RenderMeshIn2D(statsBar, Application::son->getFats() * 0.05f, 0.5, -5.5, -5, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -5.5, -5, 5, 0.5);
		if (Application::son->getVitamins() > 0)
			RenderMeshIn2D(statsBar, Application::son->getVitamins() * 0.05f, 0.5, -5.5, -7.2, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -5.5, -7.2, 5, 0.5);
		if (Application::son->getHydration() > 0)
			RenderMeshIn2D(statsBar, Application::son->getHydration() * 0.05f, 0.5, -5.5, -9.25, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -5.5, -9.25, 5, 0.5);

		if (Application::mother->getProtein() > 0)
			RenderMeshIn2D(statsBar, Application::mother->getCarbohydrates() * 0.05f, 0.5, -0.25, -0.3, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -0.25, -0.3, 5, 0.5);
		if (Application::mother->getCarbohydrates() > 0)
			RenderMeshIn2D(statsBar, Application::mother->getCarbohydrates() * 0.05f, 0.5, -0.25, -2.75, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -0.25, -2.75, 5, 0.5);
		if (Application::mother->getFats() > 0)
			RenderMeshIn2D(statsBar, Application::mother->getFats() * 0.05f, 0.5, -0.25, -5, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -0.25, -5, 5, 0.5);
		if (Application::mother->getVitamins() > 0)
			RenderMeshIn2D(statsBar, Application::mother->getVitamins() * 0.05f, 0.5, -0.25, -7.2, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -0.25, -7.2, 5, 0.5);
		if (Application::mother->getHydration() > 0)
			RenderMeshIn2D(statsBar, Application::mother->getHydration() * 0.05f, 0.5, -0.25, -9.25, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, -0.25, -9.25, 5, 0.5);

		if (Application::daughter->getProtein() > 0)
			RenderMeshIn2D(statsBar, Application::daughter->getCarbohydrates() * 0.05f, 0.5, 5, -0.3, 11, 0.5);
		RenderMeshIn2D(barBackground,5, 0.5, 5, -0.3, 5, 0.5);
		if (Application::daughter->getCarbohydrates() > 0)
			RenderMeshIn2D(statsBar, Application::daughter->getCarbohydrates() * 0.05f, 0.5, 5, -2.75, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, 5, -2.75, 5, 0.5);
		if (Application::daughter->getFats() > 0)
			RenderMeshIn2D(statsBar, Application::daughter->getFats() * 0.05f, 0.5, 5, -5, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, 5, -5, 5, 0.5);
		if (Application::daughter->getVitamins() > 0)
			RenderMeshIn2D(statsBar, Application::daughter->getVitamins() * 0.05f, 0.5, 5, -7.2, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, 5, -7.2, 5, 0.5);
		if (Application::daughter->getHydration() > 0)
			RenderMeshIn2D(statsBar, Application::daughter->getHydration() * 0.05f, 0.5, 5, -9.25, 11, 0.5);
		RenderMeshIn2D(barBackground, 5, 0.5, 5, -9.25, 5, 0.5);
		

        RenderMeshIn2D(statUiBackground, 30, 30,0,0,10);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	}
   
	
}

void Scene3D::InitInventoryUI()
{
	inventoryBar = MeshBuilder::GenerateQuad("inventory", Color(0, 0, 0), 1);
	inventoryBar->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//inventory.tga");
	Inventory::GetInstance().setPos(Vector3(0, -9, -5));
	Inventory::GetInstance().setSize(Vector3(30, 5, 0));

 
}

void Scene3D::UpdateInventoryUI(const double& deltaTime)
{

}

void Scene3D::RenderInventoryUI()
{
	if (!SceneManager::GetInstance().getIsChgScene()) {
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		RenderMeshIn2D(inventoryBar, Inventory::GetInstance().getSize().x, Inventory::GetInstance().getSize().y, Inventory::GetInstance().getPos().x, Inventory::GetInstance().getPos().y);
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		float xCoord = -13.1f;
		for (map<string, Item*>::iterator it = ItemManager::GetInstance().itemMap.begin();
			it != ItemManager::GetInstance().itemMap.end();
			++it) {

			ostringstream ss;
			ss << it->second->getNum();
			glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			if (it->first == "Milk") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord, -11, 1);
			}
			if (it->first == "Meat") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 3, -11, 1);
			}
			if (it->first == "Egg") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 6, -11, 1);
			}
			if (it->first == "Water") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 8.9, -11, 1);
			}
			if (it->first == "Apple") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 11.8, -11, 1);
			}
			if (it->first == "Fish") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 14.8, -11, 1);
			}
			if (it->first == "Cabbage") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 17.6, -11, 1);
			}
			if (it->first == "Potato") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 20.6, -11, 1);
			}
			if (it->first == "Corn") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 23.5, -11, 1);
			}
			if (it->first == "Carrot") {
				RenderTextOnScreen(fontList[FONT_CONSOLAS], ss.str(), Color(1, 1, 1), 1, xCoord + 26.5, -11, 1);
			}
			glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		}
	}
}

void Scene3D::PauseMenu()
{
    if (Application::GetInstance().bPaused == true)
    {
        RenderMeshIn2D(pause, 34, 25, 0, 0, 10);
    }
}


bool Scene3D::getDistXY(Vector3 one, Vector3 two, float dist)
{
	Vector3 temp = one - two;
	temp.z = 0;
	
	if (temp.LengthSquared() < dist * dist)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Scene3D::getDistX(Vector3 one, Vector3 two, float dist)
{
	Vector3 temp = one - two;
	temp.z = 0;
	temp.y = 0;
	if (abs(temp.x) < dist)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Scene3D::getDistY(Vector3 one, Vector3 two, float dist)
{
	Vector3 temp = one - two;
	temp.z = 0;
	temp.x = 0;
	if (abs(temp.y) < dist)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Scene3D::setZoomValues(float zoomAmount, float zoomOffsetX, float zoomOffsetY)
{
	this->zoomAmount = zoomAmount;
	this->zoomOffsetX = zoomOffsetX;
	this->zoomOffsetY = zoomOffsetY;
}

void Scene3D::UpdateDeath(const double& deltaTime)
{

}
void Scene3D::RenderDeath()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

void Scene3D::RenderScene1Title()
{
	
}

void Scene3D::ResetVegetable()
{
	for (std::vector<CabbageObject *>::iterator it = Vegetable::GetInstance().m_cabbageList.begin(); it != Vegetable::GetInstance().m_cabbageList.end(); ++it)
	{
		CabbageObject *cab = (CabbageObject *)*it;
		if (!cab->active)
			cab->active = true;
	}
	for (std::vector<PotatoObject *>::iterator it = Vegetable::GetInstance().m_potatoList.begin(); it != Vegetable::GetInstance().m_potatoList.end(); ++it)
	{
		PotatoObject *potat = (PotatoObject *)*it;
		if (!potat->active)
			potat->active = true;
	}
	for (std::vector<CarrotObject *>::iterator it = Vegetable::GetInstance().m_carrotList.begin(); it != Vegetable::GetInstance().m_carrotList.end(); ++it)
	{
		CarrotObject *carrot = (CarrotObject *)*it;
		if (!carrot->active)
			carrot->active = true;
	}
	for (std::vector<CornObject *>::iterator it = Vegetable::GetInstance().m_cornList.begin(); it != Vegetable::GetInstance().m_cornList.end(); ++it)
	{
		CornObject *corn = (CornObject *)*it;
		if (!corn->active)
			corn->active = true;
	}
}

void Scene3D::updateClouds(const double& deltaTime)
{
	if (distMoved * dir > 5)
		dir = -dir;
	distMoved += (float)(dir * deltaTime);
}

void Scene3D::reset()
{
	Application::mother->Init();
	Application::son->Init();
	Application::daughter->Init();

	Application::clock->setTime(0, 0, 1);
	ItemManager::GetInstance().resetItem();
	SceneManager::GetInstance().isChgScene(false);
}

void Scene3D::InitSceneName()
{
	for (unsigned int i = 0; i < TOTAL_TITLES; ++i) {
		titleList[i] = nullptr;
	}

	titleList[TT_HOME] = MeshBuilder::GenerateQuad("home", Color(1, 1, 1), 1);
	titleList[TT_HOME]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//home.tga");
	titleList[TT_COW] = MeshBuilder::GenerateQuad("cow", Color(1, 1, 1), 1);
	titleList[TT_COW]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//cow.tga");
	titleList[TT_CHICKEN] = MeshBuilder::GenerateQuad("chicken", Color(1, 1, 1), 1);
	titleList[TT_CHICKEN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//chicken.tga");
	titleList[TT_FISH] = MeshBuilder::GenerateQuad("home", Color(1, 1, 1), 1);
	titleList[TT_FISH]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//fish.tga");
	titleList[TT_DRAGON] = MeshBuilder::GenerateQuad("home", Color(1, 1, 1), 1);
	titleList[TT_DRAGON]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//dragon.tga");
	titleList[TT_WELL] = MeshBuilder::GenerateQuad("home", Color(1, 1, 1), 1);
	titleList[TT_WELL]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//well.tga");
	titleList[TT_APPLE] = MeshBuilder::GenerateQuad("home", Color(1, 1, 1), 1);
	titleList[TT_APPLE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//apple.tga");
	titleList[TT_CABBAGE] = MeshBuilder::GenerateQuad("home", Color(1, 1, 1), 1);
	titleList[TT_CABBAGE]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//cabbage.tga");
	titleList[TT_CORN] = MeshBuilder::GenerateQuad("home", Color(1, 1, 1), 1);
	titleList[TT_CORN]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//corn.tga");
}

void Scene3D::InitShowDay()
{
	for (unsigned int i = 0; i < TOTAL_DAY; ++i) {
		dayList[i] = nullptr;
	}

	dayList[DAY_1] = MeshBuilder::GenerateQuad("day 1", Color(1, 1, 1), 1);
	dayList[DAY_1]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day1.tga");
	dayList[DAY_2] = MeshBuilder::GenerateQuad("day 2", Color(1, 1, 1), 1);
	dayList[DAY_2]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day2.tga");
	dayList[DAY_3] = MeshBuilder::GenerateQuad("day 3", Color(1, 1, 1), 1);
	dayList[DAY_3]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day3.tga");
	dayList[DAY_4] = MeshBuilder::GenerateQuad("day 4", Color(1, 1, 1), 1);
	dayList[DAY_4]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day4.tga");
	dayList[DAY_5] = MeshBuilder::GenerateQuad("day 5", Color(1, 1, 1), 1);
	dayList[DAY_5]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day5.tga");
	dayList[DAY_6] = MeshBuilder::GenerateQuad("day 6", Color(1, 1, 1), 1);
	dayList[DAY_6]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day6.tga");
	dayList[DAY_7] = MeshBuilder::GenerateQuad("day 7", Color(1, 1, 1), 1);
	dayList[DAY_7]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day7.tga");
	dayList[DAY_8] = MeshBuilder::GenerateQuad("day 8", Color(1, 1, 1), 1);
	dayList[DAY_8]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day8.tga");
	dayList[DAY_9] = MeshBuilder::GenerateQuad("day 9", Color(1, 1, 1), 1);
	dayList[DAY_9]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day9.tga");
	dayList[DAY_10] = MeshBuilder::GenerateQuad("day 10", Color(1, 1, 1), 1);
	dayList[DAY_10]->textureArray[0] = LoadTGA("Image//SP3_Texture//Titles//Day10.tga");
}

void Scene3D::updateSceneName(const double& deltaTime)
{
	if (!SceneManager::GetInstance().getIsChgScene())
	{
		isFading = true;
	}
	else
	{
		isFading = false;
	}
	if (isFading == true)
	{
		fadeAway += deltaTime;
	}
	else
	{
		fadeAway = 0.f;
	}
}

void Scene3D::renderSceneName()
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	if (!showStats)
	{
		string tempString;
		ostringstream ss;
		if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::HOME)
		{
			RenderMeshIn2D(titleList[TT_HOME], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::COW || SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::SUB_COW)
		{
			RenderMeshIn2D(titleList[TT_COW], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::CHICKEN || SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::SUB_CHICKEN)
		{
			RenderMeshIn2D(titleList[TT_CHICKEN], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::FISH)
		{
			RenderMeshIn2D(titleList[TT_FISH], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::DRAGON && SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::SUB_DRAGON)
		{
			RenderMeshIn2D(titleList[TT_DRAGON], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::WELL)
		{
			RenderMeshIn2D(titleList[TT_WELL], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::APPLE)
		{
			RenderMeshIn2D(titleList[TT_APPLE], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::CABBAGE)
		{
			RenderMeshIn2D(titleList[TT_CABBAGE], 10, 10, 0, 12, 2);
		}
		else if (SceneManager::GetInstance().getCurrSceneEnum() == SCENE_TYPE::WHEAT)
		{
			RenderMeshIn2D(titleList[TT_CORN], 10, 10, 0, 12, 2);
		}

		
	}
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Scene3D::RenderShowDay()
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	switch (Application::clock->getDay())
	{
	case 1:
		RenderMeshIn2D(dayList[DAY_1], 6.f, 6.f, 13, 6);
		break;
	case 2:
		RenderMeshIn2D(dayList[DAY_2], 6.f, 6.f, 13, 6);
		break;
	case 3:
		RenderMeshIn2D(dayList[DAY_3], 6.f, 6.f, 13, 6);
		break;
	case 4:
		RenderMeshIn2D(dayList[DAY_4], 6.f, 6.f, 13, 6);
		break;
	case 5:
		RenderMeshIn2D(dayList[DAY_5], 6.f, 6.f, 13, 6);
		break;
	case 6:
		RenderMeshIn2D(dayList[DAY_6], 6.f, 6.f, 13, 6);
		break;
	case 7:
		RenderMeshIn2D(dayList[DAY_7], 6.f, 6.f, 13, 6);
		break;
	case 8:
		RenderMeshIn2D(dayList[DAY_8], 6.f, 6.f, 13, 6);
		break;
	case 9:
		RenderMeshIn2D(dayList[DAY_9], 6.f, 6.f, 13, 6);
		break;
	case 10:
		RenderMeshIn2D(dayList[DAY_10], 6.f, 6.f, 13, 6);
		break;
	}
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Scene3D::CheatCodeFood()
{
	ItemManager::GetInstance().addItem(new Milk(10));
	ItemManager::GetInstance().addItem(new Meat(10));
	ItemManager::GetInstance().addItem(new Egg(10));
	ItemManager::GetInstance().addItem(new Water(10));
	ItemManager::GetInstance().addItem(new Apple(98));
	ItemManager::GetInstance().addItem(new Fish(10));
	ItemManager::GetInstance().addItem(new Cabbage(10));
	ItemManager::GetInstance().addItem(new Potato(10));
	ItemManager::GetInstance().addItem(new Corn(10));
	ItemManager::GetInstance().addItem(new Carrot(10));
}

void Scene3D::CheatCodeTimeFastForward()
{
	Application::clock->setFastForward(true);
}

void Scene3D::CheatCodeTimeNormal()
{
	Application::clock->setFastForward(false);
}

void Scene3D::InitWin() {
	winScreen = MeshBuilder::GenerateQuad("Win", Color(1, 1, 1), 1);
	winScreen->textureArray[0] = LoadTGA("Image//SP3_Texture//Background//win.tga");
}

void Scene3D::UpdateWin(const double& deltaTime) {
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_ENTER]) {
		SceneManager::GetInstance().chgCurrEnumScene(MAIN_MENU);
		SceneManager::GetInstance().setIsReset(true);
		//Application::clock->setActive(true);
	}
}

void Scene3D::RenderWin() {
	if (Application::clock->getDay() >= 10){
		RenderMeshIn2D(winScreen, 34, 25, 0, 0, 10);
	}
}