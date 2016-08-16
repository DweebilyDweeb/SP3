#ifndef MINIMAP_H
#define MINIMAP_H

#include "Mesh.h"
#include "Vertex.h"
#include "Vector3.h"
#include <vector>

using std::vector;

class Minimap {

private:
	//Variable(s)
	float mapSize;
	float viewLength;
	Vector3 centre;

public:
	//Variable(s)
	Mesh* avatarMesh;
	Mesh* mapMesh;
	Mesh* borderMesh;

	//Constructor(s) & Destructor
	Minimap(float mapSize = 1.0f, float viewLength = 1.0f);
	virtual ~Minimap();

	//The centre of the minimap. Usually the position of the player.
	void UpdateMap(Vector3 centre, float rotation);
	Vector3 GetCentre();

	//How far the map shows
	bool SetViewLength(const float& viewLength);
	float GetViewLength();
	bool IncreaseViewLength(const float& viewLength);
	bool DecreaseViewLength(const float& viewLength);

	bool SetMapSize(const float& mapSize);
	float GetMapSize();

};

#endif