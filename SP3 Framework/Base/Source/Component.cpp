
#include "Component.h"

//Constructor(s) & Destructor

/*******************************************************************************/
/*!
\brief
The constructor of Component. Takes in the name of the Component.

\param name
The name of the Component
*/
/*******************************************************************************/
Component::Component(string name) {

	SetName(name);
	SetActive();

}

/*******************************************************************************/
/*!
\brief
An empty destructor.
*/
/*******************************************************************************/
Component::~Component() {
}

//Getter(s)

/*******************************************************************************/
/*!
\brief
Gets the name of the Component.

\return
The name of the Component.
*/
/*******************************************************************************/
string Component::GetName() {

	return this->name;

}

//Setter(s)

/*******************************************************************************/
/*!
\brief
Sets the name of the Component.

\param name
The name of the Component.
*/
/*******************************************************************************/
void Component::SetName(string name) {

	this->name = name;

}

/*******************************************************************************/
/*!
\brief
Sets the Component active.
*/
/*******************************************************************************/
void Component::SetActive() {

	this->isActive = true;

}

/*******************************************************************************/
/*!
\brief
Sets the Component inactive.
*/
/*******************************************************************************/
void Component::SetInactive() {

	this->isActive = false;

}