

#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

/*******************************************************************************/
/*!
Class Component
\brief
Defines Component, the abstract base class of the components where most functionality of GameObjects are done.
*/
/*******************************************************************************/

class Component {

private:
	//Variable(s)
	std::string name;
	bool isActive;

public:
	//Destructor
	virtual ~Component();

	//Getter(s)
	string GetName();

	//Setter(s)
	void SetName(string name);
	virtual void SetActive();
	virtual void SetInactive();

	//Function(s)
	bool IsActive();

protected:
	//Constructor(s)
	Component(string name);

};

#endif