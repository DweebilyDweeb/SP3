
#include "RigidBody.h"
#include "MyMath.h"

//Constructor(s) & Destructor

/*******************************************************************************/
/*!
\brief
The constructor of RigidBody.
*/
/*******************************************************************************/
RigidBody::RigidBody() : Component("RigidBody") {

	SetActive();
	useGravity = false;
	useFriction = false;

	SetMass(10.0f);
	SetDrag(0.0f);
	SetAngularDrag(0.0f);
	SetVelocity(0.0f, 0.0f, 0.0f);
	SetAngularVelocity(0.0f, 0.0f, 0.0f);
	SetGravity(0.0f, -9.81f, 0.0f);
	SetFrictionCoefficient(0.1f);

	FreezePosition(false, false, false);
	FreezeRotation(false, false, false);

}

/*******************************************************************************/
/*!
\brief
An empty destructor.
*/
/*******************************************************************************/
RigidBody::~RigidBody() {
}

//Getter(s)

/*******************************************************************************/
/*!
\brief
Gets the mass of the GameObject.

\return
The mass of the GameOBject.
*/
/*******************************************************************************/
float RigidBody::GetMass() {

	return this->mass;

}

/*******************************************************************************/
/*!
\brief
Gets the drag of the GameObject.

\return
The drag of the GameOBject.
*/
/*******************************************************************************/
float RigidBody::GetDrag() {

	return this->drag;

}

/*******************************************************************************/
/*!
\brief
Gets the angularDrag of the GameObject.

\return
The angularDrag of the GameOBject.
*/
/*******************************************************************************/
float RigidBody::GetAngularDrag() {

	return this->angularDrag;

}

float RigidBody::GetFrictionCoefficient() {

	return this->frictionCoefficient;

}

/*******************************************************************************/
/*!
\brief
Gets the velocity vector of the GameObject.

\return
The velocity vector of the GameOBject.
*/
/*******************************************************************************/
Vector3 RigidBody::GetVelocity() {
	
	if (freezePosition[X]) {
		velocity.x = 0.0f;
	}

	if (freezePosition[Y]) {
		velocity.y = 0.0f;
	}

	if (freezePosition[Z]) {
		velocity.z = 0.0f;
	}

	return this->velocity;

}

/*******************************************************************************/
/*!
\brief
Gets the angularVelocity vector of the GameObject.

\return
The angularVelocity vector of the GameOBject.
*/
/*******************************************************************************/
Vector3 RigidBody::GetAngularVelocity() {

	if (freezeRotation[X]) {
		angularVelocity.x = 0.0f;
	}
	
	if (freezeRotation[Y]) {
		angularVelocity.y = 0.0f;
	}

	if (freezeRotation[Z]) {
		angularVelocity.z = 0.0f;
	}

	return this->angularVelocity;

}

/*******************************************************************************/
/*!
\brief
Gets the gravity acting on this RigidBody.

\return
A Vector3 of the gravity acting on the RigidBody.
*/
/*******************************************************************************/
Vector3 RigidBody::GetGravity() {

	return this->gravity;

}

//Setter(s)
/*******************************************************************************/
/*!
\brief
Sets the mass of the GameObject.

\param mass
The mass of the GameObject.
*/
/*******************************************************************************/
bool RigidBody::SetMass(float mass) {

	float maxMass = FLT_MAX/10000.0f;

	if (mass >= 0.01f && mass <= maxMass) {
		this->mass = mass;
		return true;
	}
	
	if (mass <= 0.01f || mass >= maxMass) {
		return false;
	}

}

/*******************************************************************************/
/*!
\brief
Sets the drag of the GameObject.

\param mass
The drag of the GameObject.
*/
/*******************************************************************************/
bool RigidBody::SetDrag(float drag) {

	float maxValue = FLT_MAX/1000.0f;

	if (drag >= 0.0f && drag <= maxValue) {
		this->drag = drag;
		return true;
	}
	
	if (drag <= 0.0f || drag >= maxValue) {
		return false;
	}

}

/*******************************************************************************/
/*!
\brief
Sets the angularDrag of the GameObject.

\param mass
The angularDrag of the GameObject.
*/
/*******************************************************************************/
bool RigidBody::SetAngularDrag(float angularDrag) {

	float maxValue = FLT_MAX/10000.0f;

	if (angularDrag >= 0.0f && angularDrag <= maxValue) {
		this->angularDrag = angularDrag;
		return true;
	}
	
	if (angularDrag <= 0.0f || angularDrag > maxValue) {
		return false;
	}

}

/*******************************************************************************/
/*!
\brief
Sets the friction Coefficient of the object.
*/
/*******************************************************************************/
bool RigidBody::SetFrictionCoefficient(float frictionCoefficient) {

	if (frictionCoefficient >= 0.0f) {
		this->frictionCoefficient = frictionCoefficient;
		return true;
	}

	this->frictionCoefficient = 0.0f;
	return false;

}

/*******************************************************************************/
/*!
\brief
Sets the velocity of the GameObject.

\param velocity
The velocity of the GameObject.
*/
/*******************************************************************************/
void RigidBody::SetVelocity(Vector3 velocity) {

	this->velocity = velocity;

}

/*******************************************************************************/
/*!
\brief
Sets the velocity of the GameObject.

\param x
The velocity of the GameObject on the x-axis.
\param y
The velocity of the GameObject on the y-axis.
\param z
The velocity of the GameObject on the z-axis.
*/
/*******************************************************************************/
void RigidBody::SetVelocity(float x, float y, float z) {

	SetVelocity(Vector3(x, y, z));

}

/*******************************************************************************/
/*!
\brief
Sets the acceleration of the GameObject. This will affect the velocity of the GameObject.

\param acceleration
The acceleration of the GameObject.
*/
/*******************************************************************************/
void RigidBody::SetAcceleration(Vector3 acceleration, const double& deltaTime) {

	this->velocity += acceleration * deltaTime;

}

/*******************************************************************************/
/*!
\brief
Sets the acceleration of the GameObject. This will affect the velocity of the GameObject.

\param x
The acceleration of the GameObject on the x-axis.
\param y
The acceleration of the GameObject on the y-axis.
\param z
The acceleration of the GameObject on the z-axis.
*/
/*******************************************************************************/
void RigidBody::SetAcceleration(float x, float y, float z, const double& deltaTime) {

	SetAcceleration(Vector3(x, y, z), deltaTime);

}

/*******************************************************************************/
/*!
\brief
Sets the angularVelocity of the GameObject.

\param angularVelocity
The angularVelocity of the GameObject.
*/
/*******************************************************************************/
void RigidBody::SetAngularVelocity(Vector3 angularVelocity) {

	this->angularVelocity = angularVelocity;

}

/*******************************************************************************/
/*!
\brief
Sets the angularVelocity of the GameObject.

\param x
The angularVelocity of the GameObject on the x-axis.
\param y
The angularVelocity of the GameObject on the y-axis.
\param z
The angularVelocity of the GameObject on the z-axis.
*/
/*******************************************************************************/
void RigidBody::SetAngularVelocity(float x, float y, float z) {

	SetAngularVelocity(Vector3(x, y, z));

}

/*******************************************************************************/
/*!
\brief
Sets the angularAcceleration of the GameObject. This will affect the velocity of the GameObject.

\param angularAcceleration
The angularAcceleration of the GameObject.
*/
/*******************************************************************************/
void RigidBody::SetAngularAcceleration(Vector3 angularAcceleration, const double& deltaTime) {
}

/*******************************************************************************/
/*!
\brief
Sets the angularAcceleration of the GameObject. This will affect the velocity of the GameObject.

\param x
The angularAcceleration of the GameObject on the x-axis.
\param y
The angularAcceleration of the GameObject on the y-axis.
\param z
The angularAcceleration of the GameObject on the z-axis.
*/
/*******************************************************************************/
void RigidBody::SetAngularAcceleration(float x, float y, float z, const double& deltaTime) {
}

/*******************************************************************************/
/*!
\brief
Sets the magnitude and direction of the gravity acting on this RigidBody.

\param gravity
A Vector3 representing the firection and magnitude of the gravity acting on this RigidBody.
*/
/*******************************************************************************/
void RigidBody::SetGravity(Vector3 gravity) {

	this->gravity = gravity;

}

/*******************************************************************************/
/*!
\brief
Sets the magnitude and direction of the gravity acting on this RigidBody.

\param x
A Vector3 representing the firection and magnitude of the gravity acting on this RigidBody on the x-axis.
\param y
A Vector3 representing the firection and magnitude of the gravity acting on this RigidBody on the y-axis.
\param z
A Vector3 representing the firection and magnitude of the gravity acting on this RigidBody on the z-axis.
*/
/*******************************************************************************/
void RigidBody::SetGravity(float x, float y, float z) {

	SetGravity(Vector3(x, y, z));

}

//Function(s)

/*******************************************************************************/
/*!
\brief
Freezes or unfreezes the position of the GameObject, preventing its position from being affected by physics.

\param x
The x-axis of the GameObject.
\param y
The y-axis of the GameObject.
\param z
The z-axis of the GameObject.
*/
/*******************************************************************************/
void RigidBody::FreezePosition(bool x, bool y, bool z) {

	freezePosition[X] = x;
	freezePosition[Y] = y;
	freezePosition[Z] = z;

}

/*******************************************************************************/
/*!
\brief
Freezes or unfreezes the position of the GameObject, preventing its position from being affected by physics.

\param freeze
To freeze or unfreeze the GameObject,
\param axis
The axis of the GameObject to freeze or unfreeze.
*/
/*******************************************************************************/
void RigidBody::FreezePosition(bool freeze, AXIS axis) {

	freezePosition[axis] = freeze;

}

/*******************************************************************************/
/*!
\brief
Freezes or unfreezes the rotation of the GameObject, preventing its rotation from being affected by physics.

\param x
The x-axis of the GameObject.
\param y
The y-axis of the GameObject.
\param z
The z-axis of the GameObject.
*/
/*******************************************************************************/
void RigidBody::FreezeRotation(bool x, bool y, bool z) {

	freezeRotation[X] = x;
	freezeRotation[Y] = y;
	freezeRotation[Z] = z;

}

/*******************************************************************************/
/*!
\brief
Freezes or unfreezes the rotation of the GameObject, preventing its rotation from being affected by physics.

\param freeze
To freeze or unfreeze the GameObject,
\param axis
The axis of the GameObject to freeze or unfreeze.
*/
/*******************************************************************************/
void RigidBody::FreezeRotation(bool freeze, AXIS axis) {

	freezeRotation[axis] = freeze;

}

/*******************************************************************************/
/*!
\brief
Adds the specified force to the GameObject.

\param x
The magnitude of the force vector on the x-axis.
\param y
The magnitude of the force vector on the y-axis.
\param z
The magnitude of the force vector on the z-axis.
*/
/*******************************************************************************/
void RigidBody::AddForce(float x, float y, float z, const double& deltaTime) {

	AddForce(Vector3(x, y, z), deltaTime);

}

/*******************************************************************************/
/*!
\brief
Adds the specified force to the GameObject.

\param forceVector
The direction and magnitude of the force.
*/
/*******************************************************************************/
void RigidBody::AddForce(Vector3 forceVector, const double& deltaTime) {

	if (forceVector.LengthSquared() < Math::EPSILON) {
		return;
	}

	SetAcceleration(forceVector * (1.0f / mass), deltaTime);

}

/*******************************************************************************/
/*!
\brief
Adds the specificed torque to the GameObject. This assumes the mass of the object is evenly spreaded out in a solid sphere of radius 1.

\param x
The magnitude of the torque on the x-axis.
\param y
The magnitude of the torque on the y-axis.
\param z
The magnitude of the torque on the z-axis.
\param deltaTime
The time taken since for the previous frame.
*/
/*******************************************************************************/
void RigidBody::AddTorque(float x, float y, float z, const double& deltaTime) {

	AddTorque(Vector3(x, y, z), deltaTime);

}

/*******************************************************************************/
/*!
\brief
Adds the specificed torque to the GameObject. This assumes the mass of the object is evenly spreaded out in a solid sphere of radius 1.

\param torqueVector
The direction and magnitude of the torque applied.
\param deltaTime
The time since taken for the previous frame.
*/
/*******************************************************************************/
void RigidBody::AddTorque(Vector3 torqueVector, const double& deltaTime) {

	//Do stuff here.

}

void RigidBody::ApplyFriction(const double& deltaTime) {

	if (useFriction == true) {
		if (velocity.LengthSquared() > Math::EPSILON) {
			Vector3 velocityChange = this->velocity.Normalized() * (this->gravity.Length() * this->frictionCoefficient) * deltaTime;
			if (velocityChange.LengthSquared() < velocity.LengthSquared()) {
				velocity -= velocityChange;
			} else {
				velocity.SetZero();
			}
		} else {
			velocity.SetZero();
		}
	}

}

void RigidBody::ApplyGravity(const double& deltaTime) {

	if (useGravity == true) {
		AddForce(this->gravity * this->mass, deltaTime);
	}

}