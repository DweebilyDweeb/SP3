#ifndef SCENE_3D_H
#define SCENE_3D_H

#include "Scene.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "Light.h"
#include "SpriteAnimation.h"
#include "Family.h"
#include "Mother.h"
#include "Son.h"
#include "Daughter.h"
#include "ItemManager.h"

const unsigned int MAX_LIGHTS = 8;

class Scene3D : public Scene {

protected:
	//Shaders
	enum SHADER_TYPE {
		NONE = 0,
		DEFAULT,

		NUM_SHADER,
	};

	//Shader Uniforms
	enum SHADER_UNIFORM {
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHTENABLED,
		U_NUMLIGHTS,
		
		//Textures
		U_COLOR_TEXTURE_ENABLED0,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE_ENABLED2,
		U_COLOR_TEXTURE_ENABLED3,
		U_COLOR_TEXTURE_ENABLED4,
		U_COLOR_TEXTURE_ENABLED5,
		U_COLOR_TEXTURE_ENABLED6,
		U_COLOR_TEXTURE_ENABLED7,
		
		U_COLOR_TEXTURE0,
		U_COLOR_TEXTURE1,
		U_COLOR_TEXTURE2,
		U_COLOR_TEXTURE3,
		U_COLOR_TEXTURE4,
		U_COLOR_TEXTURE5,
		U_COLOR_TEXTURE6,
		U_COLOR_TEXTURE7,

		//Light On
		U_LIGHT0_ON,
		U_LIGHT1_ON,
		U_LIGHT2_ON,
		U_LIGHT3_ON,
		U_LIGHT4_ON,
		U_LIGHT5_ON,
		U_LIGHT6_ON,
		U_LIGHT7_ON,

		//Light Type
		U_LIGHT0_TYPE,
		U_LIGHT1_TYPE,
		U_LIGHT2_TYPE,
		U_LIGHT3_TYPE,
		U_LIGHT4_TYPE,
		U_LIGHT5_TYPE,
		U_LIGHT6_TYPE,
		U_LIGHT7_TYPE,

		//Light Position
		U_LIGHT0_POSITION,
		U_LIGHT1_POSITION,
		U_LIGHT2_POSITION,
		U_LIGHT3_POSITION,
		U_LIGHT4_POSITION,
		U_LIGHT5_POSITION,
		U_LIGHT6_POSITION,
		U_LIGHT7_POSITION,

		//Light Colour
		U_LIGHT0_COLOR,
		U_LIGHT1_COLOR,
		U_LIGHT2_COLOR,
		U_LIGHT3_COLOR,
		U_LIGHT4_COLOR,
		U_LIGHT5_COLOR,
		U_LIGHT6_COLOR,
		U_LIGHT7_COLOR,

		//Light Power
		U_LIGHT0_POWER,
		U_LIGHT1_POWER,
		U_LIGHT2_POWER,
		U_LIGHT3_POWER,
		U_LIGHT4_POWER,
		U_LIGHT5_POWER,
		U_LIGHT6_POWER,
		U_LIGHT7_POWER,

		//Light KC
		U_LIGHT0_KC,
		U_LIGHT1_KC,
		U_LIGHT2_KC,
		U_LIGHT3_KC,
		U_LIGHT4_KC,
		U_LIGHT5_KC,
		U_LIGHT7_KC,
		U_LIGHT6_KC,

		//Light KL
		U_LIGHT0_KL,
		U_LIGHT1_KL,
		U_LIGHT2_KL,
		U_LIGHT3_KL,
		U_LIGHT4_KL,
		U_LIGHT5_KL,
		U_LIGHT6_KL,
		U_LIGHT7_KL,

		//Light KQ
		U_LIGHT0_KQ,
		U_LIGHT1_KQ,
		U_LIGHT2_KQ,
		U_LIGHT3_KQ,
		U_LIGHT4_KQ,
		U_LIGHT5_KQ,
		U_LIGHT6_KQ,
		U_LIGHT7_KQ,

		//Light Spotdirection
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT5_SPOTDIRECTION,
		U_LIGHT6_SPOTDIRECTION,
		U_LIGHT7_SPOTDIRECTION,

		//Light Cosine Cutoff
		U_LIGHT0_COSCUTOFF,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT5_COSCUTOFF,
		U_LIGHT6_COSCUTOFF,
		U_LIGHT7_COSCUTOFF,

		//Light Inner Cosine
		U_LIGHT0_COSINNER,
		U_LIGHT1_COSINNER,
		U_LIGHT2_COSINNER,
		U_LIGHT3_COSINNER,
		U_LIGHT4_COSINNER,
		U_LIGHT5_COSINNER,
		U_LIGHT6_COSINNER,
		U_LIGHT7_COSINNER,

		//Light Exponent
		U_LIGHT0_EXPONENT,
		U_LIGHT1_EXPONENT,
		U_LIGHT2_EXPONENT,
		U_LIGHT3_EXPONENT,
		U_LIGHT4_EXPONENT,
		U_LIGHT5_EXPONENT,
		U_LIGHT6_EXPONENT,
		U_LIGHT7_EXPONENT,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_FOG_ENABLED,
		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,

		U_TOTAL,
	};

	enum FONT_TYPE {
	
		FONT_CONSOLAS = 0,

		NUM_FONT,

	};

	//Shaders
	unsigned int shaderProgramID[NUM_SHADER];
	unsigned int shaderParameters[NUM_SHADER * U_TOTAL];
	SHADER_TYPE currentShader;

	//Vertex Array
	unsigned int vertexArrayID;

	//Lights
	Light lights[MAX_LIGHTS];

	//MVP Stack
	MS modelStack, viewStack, projectionStack;

	//Reference Axes
	Mesh* referenceAxes;

	//Fonts
	Mesh* fontList[NUM_FONT];

	//bars

	Mesh* healthBar;
	Mesh* statsBar;
	Mesh* healthUiBackground;
	Mesh* statUiBackground;
	Mesh* barBackground;
    Mesh* bigClock;
    Mesh* clockHandH;
	Mesh* inventoryBar;
    Mesh* pause;
	bool showStats;

	float zoomAmount;
	float zoomOffsetY;
	float zoomOffsetX;
	
public:
	//Constructor(s) & Destructor
	Scene3D();
	virtual ~Scene3D();

	//Exit
	virtual void Exit();
	virtual void DeleteShaders();

	//Initialisation
	virtual void Init();
	virtual void InitGL();
	virtual void InitShaders(const char* vertexShaderFile, const char* fragmentShaderFile, SHADER_TYPE shaderType);
	virtual void InitLights();
	virtual void InitFog(Color color = Color(0.5f, 0.5f, 0.5f), int fogType = 2, float start = 25.0f, float end = 1000.0f, float density = 0.005f);
    virtual void InitPlayer() = 0;
    virtual void EnableFog(bool enable);

	//Update
	virtual void Update(const double& deltaTime);
	virtual void UpdateSub(const double& deltaTime) = 0;
	virtual	void UpdateLights();
	virtual void UpdateLightAttributes(unsigned int n);
	virtual void UseShader(SHADER_TYPE shaderType);
    virtual void PauseMenu();
	//Rendering
	virtual void SetToCameraView(Camera* camera, float zoom = 0.f);
	virtual void Render();
	virtual void RenderSub();
	virtual void RenderAxes();
	virtual void Render3D();
	virtual void Render2D();
	virtual void SetHUD(bool mode, float x = 80.0f, float y = 45.0f, float z = 10.0f);
	virtual void RenderMeshIn2D(Mesh *mesh, float sizeX = 1.0f, float sizeY = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f, float offsetX = 0.0f, float offsetY = 0.0f, float rotationX = 0.0f, float rotationY = 0.0f, float rotationZ = 0.0f);
	virtual void RenderMesh(Mesh* mesh, bool enableLight = false, bool invert = false);
	virtual void RenderSpriteAnimation(SpriteAnimation* sa, bool enableLight = false, bool invert = false);
	void RenderVegetables();
	//virtual void RenderMeshWithOutline(Mesh* mesh, bool enableLight, SHADER_TYPE shaderType = DEFAULT);
	virtual void RenderText(Mesh* mesh, std::string text, Color color);
	virtual void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z = 0);

	bool getDistXY(Vector3 one, Vector3 two, float dist);
	bool getDistX(Vector3 one, Vector3 two, float dist);
	bool getDistY(Vector3 one, Vector3 two, float dist);

	void setZoomValues(float zoomAmount, float zoomOffsetX, float zoomOffsetY);

	void InitAttributeUI();
	void UpdateAttributeUI(const double& deltaTime);
	void RenderAttributeUI();

	void InitInventoryUI();
	void UpdateInventoryUI(const double& deltaTime);
	void RenderInventoryUI();

    void UpdateDeath(const double& deltaTime);
    void RenderDeath();

	void RenderScene1Title();
};

#endif