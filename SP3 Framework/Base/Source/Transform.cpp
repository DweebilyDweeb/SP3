

#include "Transform.h"

//Constructor(s) & Destructor

/*******************************************************************************/
/*!
\brief
The constructor of Transform.
*/
/*******************************************************************************/
Transform::Transform() : Component("Transform") {

	SetActive();

	SetPosition(0, 0, 0);
	SetRotation(0, 0, 0);
	SetScale(1, 1, 1);

}

/*******************************************************************************/
/*!
\brief
An empty destructor.
*/
/*******************************************************************************/
Transform::~Transform() {
}

//Getter(s)

/*******************************************************************************/
/*!
\brief
Gets the global position.

\return
The position of the GameObject.
*/
/*******************************************************************************/
Vector3 Transform::GetPosition() {

	return this->position;

}

/*******************************************************************************/
/*!
\brief
Gets the global rotation.

\return
The rotation of the GameObject.
*/
/*******************************************************************************/
Vector3 Transform::GetRotation() {

	return this->rotation;

}

/*******************************************************************************/
/*!
\brief
Gets the global scale.

\return
The scale of the GameObject.
*/
/*******************************************************************************/
Vector3 Transform::GetScale() {

	return this->scale;

}

/*******************************************************************************/
/*!
\brief
Gets the forward vector of the GameObject.

\return
The forward vector of the GameObject.
*/
/*******************************************************************************/
Vector3 Transform::GetForward() {

	Mtx44 transformationMatrix;
	transformationMatrix.SetToTranslation(0, 0, 1);
	transformationMatrix = GetRotationMatrix() * transformationMatrix;

	return Vector3(transformationMatrix.a[12], transformationMatrix.a[13], transformationMatrix.a[14]);

}

/*******************************************************************************/
/*!
\brief
Gets the up vector of the GameObject.

\return
The up vector of the GameObject.
*/
/*******************************************************************************/
Vector3 Transform::GetUp() {

	Mtx44 transformationMatrix;
	transformationMatrix.SetToTranslation(0, 1, 0);
	transformationMatrix = GetRotationMatrix() * transformationMatrix;

	return Vector3(transformationMatrix.a[12], transformationMatrix.a[13], transformationMatrix.a[14]);

}

/*******************************************************************************/
/*!
\brief
Gets the left vector of the GameObject.

\return
The left vector of the GameObject.
*/
/*******************************************************************************/
Vector3 Transform::GetLeft() {

	Mtx44 transformationMatrix;
	transformationMatrix.SetToTranslation(1, 0, 0);
	transformationMatrix = GetRotationMatrix() * transformationMatrix;

	return Vector3(transformationMatrix.a[12], transformationMatrix.a[13], transformationMatrix.a[14]);

}

/*******************************************************************************/
/*!
\brief
Gets the rotation of the GameObject in the form of a Mtx44.

\return
The rotationMatrix of the GameObject.
*/
/*******************************************************************************/
Mtx44 Transform::GetRotationMatrix() {

	Mtx44 transformationMatrix;
	Mtx44 rotationMatrix;
	rotationMatrix.SetToIdentity();
	
	transformationMatrix.SetToRotation(this->rotation.y, 0, 1, 0);
	rotationMatrix = rotationMatrix * transformationMatrix;
	transformationMatrix.SetToRotation(this->rotation.x, 1, 0, 0);
	rotationMatrix = rotationMatrix * transformationMatrix;
	transformationMatrix.SetToRotation(this->rotation.z, 0, 0, 1);
	rotationMatrix = rotationMatrix * transformationMatrix;

	return rotationMatrix;

}

//Setter(s)

/*******************************************************************************/
/*!
\brief
Sets the position of the GameObject.

\param position
The position of the GameObject.
*/
/*******************************************************************************/
void Transform::SetPosition(Vector3 position) {

	this->position = position;

}

/*******************************************************************************/
/*!
\brief
Sets the position of the GameObject.

\param x
The position of the GameObject on the x-axis.
\param y
The position of the GameObject on the y-axis.
\param z
The position of the GameObject on the z-axis.
*/
/*******************************************************************************/
void Transform::SetPosition(float x, float y, float z) {

	SetPosition(Vector3(x, y, z));

}

/*******************************************************************************/
/*!
\brief
Sets the rotation of the GameObject.

\param rotation
The rotation of the GameObject.
*/
/*******************************************************************************/
void Transform::SetRotation(Vector3 rotation) {

	this->rotation = rotation;

}

/*******************************************************************************/
/*!
\brief
Sets the rotation of the GameObject.

\param x
The rotation of the GameObject on the x-axis.
\param y
The rotation of the GameObject on the y-axis.
\param z
The rotation of the GameObject on the z-axis.
*/
/*******************************************************************************/
void Transform::SetRotation(float x, float y, float z) {

	SetRotation(Vector3(x, y, z));

}

/*******************************************************************************/
/*!
\brief
Sets the scale of the GameObject.

\param scale
The scale of the GameObject.
*/
/*******************************************************************************/
void Transform::SetScale(Vector3 scale) {

	this->scale = scale;

}

/*******************************************************************************/
/*!
\brief
Sets the scale of the GameObject.

\param x
The scale of the GameObject on the x-axis.
\param y
The scale of the GameObject on the y-axis.
\param z
The scale of the GameObject on the z-axis.
*/
/*******************************************************************************/
void Transform::SetScale(float x, float y, float z) {

	SetScale(Vector3(x, y, z));

}

//Function(s)

/*******************************************************************************/
/*!
\brief
Translate the GameObject.

\param translation
The amount to translate the GameObject by.
*/
/*******************************************************************************/
void Transform::Translate(Vector3 translation) {

	this->position += translation;

}

/*******************************************************************************/
/*!
\brief
Translate the GameObject.

\param x
The amount to translate the GameObject by on the x-axis.
\param y
The amount to translate the GameObject by on the y-axis.
\param z
The amount to translate the GameObject by on the z-axis.
*/
/*******************************************************************************/
void Transform::Translate(float x, float y, float z) {

	Translate(Vector3(x, y, z));

}

/*******************************************************************************/
/*!
\brief
Rotate the GameObject.

\param rotation
The amount to rotate the GameObject by.
*/
/*******************************************************************************/
void Transform::Rotate(Vector3 rotation) {

	this->rotation += rotation;

}

/*******************************************************************************/
/*!
\brief
Rotate the GameObject.

\param x
The amount to rotate the GameObject by on the x-axis.
\param y
The amount to rotate the GameObject by on the y-axis.
\param z
The amount to rotate the GameObject by on the z-axis.
*/
/*******************************************************************************/
void Transform::Rotate(float x, float y, float z) {

	Rotate(Vector3(x, y, z));

}

/*******************************************************************************/
/*!
\brief
Scale the GameObject on its 3 axis.

\param scale
The amount to scale the GameObject by.
*/
/*******************************************************************************/
void Transform::Scale(Vector3 scale) {

	this->scale.x *= scale.x;
	this->scale.y *= scale.y;
	this->scale.z *= scale.z;

}

/*******************************************************************************/
/*!
\brief
Scale the GameObject on its 3 axis.

\param x
The amount to scale the GameObject by on the x-axis.
\param y
The amount to scale the GameObject by on the y-axis.
\param z
The amount to scale the GameObject by on the z-axis.
*/
/*******************************************************************************/
void Transform::Scale(float x, float y, float z) {

	Scale(Vector3(x, y, z));

}

/*******************************************************************************/
/*!
\brief
Scale the GameObject uniformly.

\param scale
The amount to scale the GameObject by.
*/
/*******************************************************************************/
void Transform::Scale(float scale) {

	this->scale *= scale;

}

/*******************************************************************************/
/*!
\brief
Translate the GameObject along it's own axis.

\param translation
The amount to translate the GameObject by.
*/
/*******************************************************************************/
void Transform::LocalTranslate(Vector3 translation) {

	LocalTranslate(translation.x, translation.y, translation.z);

}

/*******************************************************************************/
/*!
\brief
Translate the GameObject along it's own axis.

\param x
The amount to translate the GameObject by on the local x-axis.
\param y
The amount to translate the GameObject by on the local y-axis.
\param z
The amount to translate the GameObject by on the local z-axis.
*/
/*******************************************************************************/
void Transform::LocalTranslate(float x, float y, float z) {

	Translate(x * GetLeft());
	Translate(y * GetUp());
	Translate(z * GetForward());

}

/*******************************************************************************/
/*!
\brief
Rotate the GameObject along it's own axis.

\param rotation
The amount to rotate the GameObject by on its own axis.
*/
/*******************************************************************************/
void Transform::LocalRotate(Vector3 rotation) {

	LocalRotate(rotation.x, rotation.y, rotation.z);

}

/*******************************************************************************/
/*!
\brief
Rotate the GameObject along it's own axis.

\param x
The amount to rotate the GameObject by on its own x-axis.
\param y
The amount to rotate the GameObject by on its own y-axis.
\param z
The amount to rotate the GameObject by on its own z-axis.
*/
/*******************************************************************************/
void Transform::LocalRotate(float x, float y, float z) {
}