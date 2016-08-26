#include "CowObject.h"

Cow::Cow(Cow_state *state) {
	this->state = state;
}


void Cow::change_state(Cow_state *state) {
	this->state = state;
}

