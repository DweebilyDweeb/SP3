
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Component.h"
#include "Vector3.h"
#include "MatrixStack.h"

/*******************************************************************************/
/*!
Class Transform
\brief
Defines Transform, a Component which stores the transformation of an object.
*/
/*******************************************************************************/
class Transform : public Component {

public:
	//Variable(s)
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	//Constructor(s)
	Transform();

	//Destructor
	virtual ~Transform();

	//Getter(s)
	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();

	Vector3 GetForward();
	Vector3 GetUp();
	Vector3 GetLeft();

	Mtx44 GetPositionMatrix();
	Mtx44 GetRotationMatrix();
	Mtx44 GetScaleMatrix();

	//Setters(s)
	void SetPosition(Vector3 position);
	void SetPosition(float x, float y, float z);
	void SetRotation(Vector3 rotation);
	void SetRotation(float x, float y, float z);
	void SetScale(Vector3 scale);
	void SetScale(float x, float y, float z);
	
	//Function(s)
	void Translate(Vector3 translation);
	void Translate(float x, float y, float z);
	void Rotate(Vector3 rotation);
	void Rotate(float x, float y, float z);
	void Scale(Vector3 scale);
	void Scale(float x, float y, float z);
	void Scale(float scale);
	
	//Does Not Work Yet
	void LocalTranslate(Vector3 translation);
	void LocalTranslate(float x, float y, float z);
	void LocalRotate(Vector3 rotation);
	void LocalRotate(float x, float y, float z);

};

#endif