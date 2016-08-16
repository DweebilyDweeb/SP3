#include "Scene3D.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Utility.h"
#include "MeshBuilder.h"

//Constructor(s) & Destructor

Scene3D::Scene3D() {

	referenceAxes = MeshBuilder::GenerateAxes("Reference Axes", 5000000.0f, 5000000.0f, 5000000.0f);
	fontList[FONT_CONSOLAS] = MeshBuilder::GenerateText("Consolas", 16, 16, "Image//Fonts//Consolas.tga");
	currentShader = NONE;

}

Scene3D::~Scene3D() {
}

//Exit

void Scene3D::Exit() {

	DeleteShaders();
	glDeleteVertexArrays(1, &vertexArrayID);

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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
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

void Scene3D::SetToCameraView(Camera* camera) {

	modelStack.LoadIdentity();
	viewStack.LoadIdentity();
	viewStack.LookAt(camera->transform.position.x, camera->transform.position.y, camera->transform.position.z,
					 camera->transform.position.x + camera->transform.GetForward().x,
					 camera->transform.position.y + camera->transform.GetForward().y,
					 camera->transform.position.z + camera->transform.GetForward().z,
					 camera->transform.GetUp().x, camera->transform.GetUp().y, camera->transform.GetUp().z);

	float aspectRatio = static_cast<float>(camera->aspectRatio.x) / static_cast<float>(camera->aspectRatio.y);
	if (camera->IsOrtho()) {
		Mtx44 orthoMatrix;
		orthoMatrix.SetToOrtho(-aspectRatio * camera->GetOrthoSize(), aspectRatio * camera->GetOrthoSize(),
							   -camera->GetOrthoSize(), camera->GetOrthoSize(),
							   camera->GetNearClippingPlane(), camera->GetFarClippingPlane());
		
		projectionStack.LoadMatrix(orthoMatrix);
	} else {
		Mtx44 perspMatrix;
		perspMatrix.SetToPerspective(camera->GetFOV(),
									 aspectRatio,
									 camera->GetNearClippingPlane(),
									 camera->GetFarClippingPlane());

		projectionStack.LoadMatrix(perspMatrix);
	}

}

void Scene3D::Render() {
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

void Scene3D::RenderMeshIn2D(Mesh *mesh, float size, float x, float y, float rotationX, float rotationY, float rotationZ) {

	viewStack.PushMatrix();
		viewStack.LoadIdentity();
		modelStack.PushMatrix();
			modelStack.LoadIdentity();
			modelStack.Translate(x, y, 0);
			modelStack.Rotate(rotationY, 0, 1, 0);
			modelStack.Rotate(rotationX, 1, 0, 0);
			modelStack.Rotate(rotationZ, 0, 0, 1);
			modelStack.Scale(size, size, size);

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

void Scene3D::RenderMesh(Mesh* mesh, bool enableLight) {

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

	mesh->Render();

	if (mesh->textureArray[0] > 0) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void Scene3D::RenderSpriteAnimation(SpriteAnimation* sa, bool enableLight) {

	Mesh* mesh = dynamic_cast<Mesh*>(sa);

	if (mesh) {
		RenderMesh(mesh, enableLight);
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

void Scene3D::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y) {

	if (!mesh || mesh->textureArray[0] <= 0) {
		return;
	}

	viewStack.PushMatrix();
		viewStack.LoadIdentity();
		modelStack.PushMatrix();
			modelStack.LoadIdentity();
			modelStack.Translate(x, y, 0);
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