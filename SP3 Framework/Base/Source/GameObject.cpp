#include "GameObject.h"

//Constructor(s) & Destructor

/*******************************************************************************/
/*!
\brief
The constructor of GameObject.
*/
/*******************************************************************************/
GameObject::GameObject(string name) {

	this->name = name;

}

/*******************************************************************************/
/*!
\brief
The destructor of GameObject.
*/
/*******************************************************************************/
GameObject::~GameObject() {
}

//Getter(s)

/*******************************************************************************/
/*!
\brief
Gets the name of the GameObject.

\return
The name of the GameObject.
*/
/*******************************************************************************/
string GameObject::GetName() {

	return this->name;

}

//Setter(s)
/*******************************************************************************/
/*!
\brief
Sets the name of the GameObject.

\param name
The name of the GameObject.
*/
/*******************************************************************************/
void GameObject::SetName(string name) {

	this->name = name;

}

/*******************************************************************************/
/*!
\brief
Updates the GameObject.
*/
/*******************************************************************************/
void GameObject::Update(double deltaTime) {
}