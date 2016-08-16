#ifndef MESH_H
#define MESH_H

#include <string>
#include "Material.h"

using std::string;

const unsigned int MAX_TEXTURES = 8;

class Mesh {

public:
	//Enum(s)
	enum DRAW_MODE {

		DRAW_TRIANGLES, //Default Mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,

	};

	//Variable(s)
	const std::string name;
	DRAW_MODE mode;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int indexSize;

	Material material;
	unsigned int textureArray[MAX_TEXTURES];

	//Constructor(s) & Destructor
	Mesh(const std::string &meshName);
	virtual ~Mesh();

	//Function(s)
	virtual void Render();
	virtual void Render(unsigned offset, unsigned count);

};

#endif