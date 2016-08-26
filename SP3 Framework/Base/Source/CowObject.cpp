#include "CowObject.h"
#include "MyMath.h"

Cow::Cow(/*Cow_state *state,*/ SpriteAnimation* currSA) :
sanim(currSA),
scale(1.f),
vel(0.f),
active(true),
invert(false)
{
	pos.Set(Math::RandFloatMinMax(-30, 30), Math::RandFloatMinMax(-15, 15), 1);
	//this->state = state;
}

/*void Cow::setCurrState(Cow_state *state, SpriteAnimation* currSA) {
	this->state = state;
	this->sanim = currSA;
}*/

