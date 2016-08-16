#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "SpriteAnimation.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder {

public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX=0.0f, float lengthY=0.0f, float lengthZ=0.0f);
	static Mesh* GenerateCrossHair(const std::string &meshName, float colour_r=1.0f, float colour_g=1.0f, float colour_b=0.0f, float length=1.0f);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float length = 1.0f);
	static Mesh* Generate2DTile(const string& meshName, Color color = Color(1, 1, 1), float width = 1.0f, float height = 1.0f);
	static Mesh* GeneratePlane(const std::string &meshName, Color color, float length = 1.0f, unsigned int uTile = 1, unsigned int vTile = 1);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float length = 1.0f);
	static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR = 1.0f, float innerR = 0.0f);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius = 1.0f);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlice, float radius, float height);
	static Mesh* GenerateSkyPlane(const std::string &meshName, Color color, unsigned int numSlices, float planetRadius, float atmosphereRadius, float uTile, float vTile);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string& filePath);
	static Mesh* GenerateText(const std::string &meshName, unsigned row, unsigned col, const char* textureFile);
	static Mesh* GenerateTerrain(const std::string &meshName, const std::string filePath, std::vector<unsigned char> &heightMap, unsigned int uTile, unsigned int vTile);
	static SpriteAnimation* GenerateSpriteAnimation(const string& meshName, unsigned int numRow, unsigned int numColumn);

};

#endif