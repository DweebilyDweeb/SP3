
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <list>
#include "Transform.h"

using std::list;

/*******************************************************************************/
/*!
Class GameObject
\brief
Defines GameObject, which defines everything that is in a Scene.
*/
/*******************************************************************************/

class GameObject {

private:
	//Variable(s)
	string name;
	
public:
	//Variable(s)
	Transform transform;
	
	//Destructor
	virtual ~GameObject();

	//Getter(s)
	string GetName();
	
	//Setter(s)
	void SetName(string name);
	
	//Function(s)
	virtual void Update(double deltaTime);
	
protected:
	//Constructor(s)
	GameObject(string name = "Unnamed Object");

};

#endif