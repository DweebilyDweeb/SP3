#include "Minimap.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Mtx44.h"

Minimap::Minimap(float mapSize, float viewLength) {

	centre = Vector3(0.0f, 0.0f, 0.0f);
	this->mapSize = mapSize;
	viewLength = 1.0f;
	mapMesh = MeshBuilder::GenerateQuad("Minimap", Color(1.0f, 1.0f, 1.0f), 1.0f);
	borderMesh = MeshBuilder::GenerateQuad("Minimap Border", Color(0.0f, 0.0f, 0.0f), 1.03f);
	avatarMesh = MeshBuilder::GenerateQuad("Minimap Avatar", Color(1.0f, 1.0f, 0.0f), 1.0f);

}

Minimap::~Minimap() {

	if (mapMesh) {
		delete mapMesh;
	}
	if (borderMesh) {
		delete borderMesh;
	}
	if (avatarMesh) {
		delete avatarMesh;
	}

}

void Minimap::UpdateMap(Vector3 centre, float rotation) {

	this->centre = centre;

	if (mapMesh != nullptr) {
		float offset = viewLength / 2.0f;
		TexCoord texCoord[4];
		
		Mtx44 rotationMatrix;
		//We need to negate the rotation. Because if our player is rotating right, we need to rotate left.
		rotationMatrix.SetToRotation(-rotation, 0, 1, 0);
		Mtx44 centreMatrix;
		//We need to negate the x-axis as from the top view, left is positive X,
		//while for texture coordinates right is positive X.
		centreMatrix.SetToTranslation(-centre.x, 0.0f, centre.z);

		Mtx44 scaleMatrix;
		scaleMatrix.SetToScale(1.0f / mapSize, 1, 1.0f / mapSize);
		Mtx44 texCoordMatrix;
		
		//TexCoord 0
		texCoordMatrix.SetToTranslation(-offset, 0, offset);
		texCoordMatrix = scaleMatrix * centreMatrix * rotationMatrix * texCoordMatrix;
		texCoord[0].Set(texCoordMatrix.a[12] + 0.5f, texCoordMatrix.a[14] + 0.5f);

		//TexCoord 1
		texCoordMatrix.SetToTranslation(-offset, 0, -offset);
		texCoordMatrix = scaleMatrix * centreMatrix * rotationMatrix * texCoordMatrix;
		texCoord[1].Set(texCoordMatrix.a[12] + 0.5f, texCoordMatrix.a[14] + 0.5f);
		
		//TexCoord 2
		texCoordMatrix.SetToTranslation(offset, 0, offset);
		texCoordMatrix = scaleMatrix * centreMatrix * rotationMatrix * texCoordMatrix;
		texCoord[2].Set(texCoordMatrix.a[12] + 0.5f, texCoordMatrix.a[14] + 0.5f);
		
		//TexCoord 3
		texCoordMatrix.SetToTranslation(offset, 0, -offset);
		texCoordMatrix = scaleMatrix * centreMatrix * rotationMatrix * texCoordMatrix;
		texCoord[3].Set(texCoordMatrix.a[12] + 0.5f, texCoordMatrix.a[14] + 0.5f);

		//Bind the mesh's vertex buffer so we can modify it.
		glBindBuffer(GL_ARRAY_BUFFER, mapMesh->vertexBuffer);
		//Replace the texture coordinates' data.
		for (unsigned int i = 0; i < 4; ++i) {
			//Buffer: (Pos/Color/Normal/TexCoord) (Pos/Color/Normal/TexCoord) (Pos/Color/Normal/TexCoord) (Pos/Color/Normal/TexCoord)
			glBufferSubData(GL_ARRAY_BUFFER, (sizeof(Vertex) - sizeof(TexCoord)) + (i * sizeof(Vertex)),
			sizeof(TexCoord), &texCoord[i]);
		}
		//Unbind the VBO.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

Vector3 Minimap::GetCentre() {

	return this->centre;

}

bool Minimap::SetViewLength(const float& viewLength) {

	if (viewLength <= 0.0f) {
		return false;
	}

	this->viewLength = viewLength;

	return true;

}

bool Minimap::IncreaseViewLength(const float& viewLength) {

	this->viewLength += viewLength;

	if (this->viewLength <= 0.0f) {
		this->viewLength;
		return false;
	}

	return true;

}

bool Minimap::DecreaseViewLength(const float& viewLength) {

	this->viewLength -= viewLength;

	if (this->viewLength <= 0.0f) {
		this->viewLength;
		return false;
	}

	return true;

}

float Minimap::GetViewLength() {

	return this->viewLength;

}

bool Minimap::SetMapSize(const float& mapSize) {

	if (mapSize <= 0.0f) {
		return false;
	}

	this->mapSize = mapSize;

	return true;

}

float Minimap::GetMapSize() {

	return mapSize;

}