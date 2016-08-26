#ifndef COW_OBJECT_H
#define COW_OBJECT_H

#include "Vector3.h"
#include "Mesh.h"
#include "SpriteAnimation.h"

class Cow {

public:
	Cow(/*Cow_state *, */SpriteAnimation*);
	//void setCurrState(Cow_state *, SpriteAnimation*);
	void setPosition(const Vector3& pos) {
		this->pos = pos;
	}

	Vector3 getPosition() const {
		return pos;
	}

private:
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;

	SpriteAnimation* sanim;
	//Cow_state* state;

	bool invert;
	bool active;
};



#endif //COW_OBJECT_H