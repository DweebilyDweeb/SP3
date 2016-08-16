
#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include "Component.h"
#include "Vector3.h"
#include "Physics.h"

/*******************************************************************************/
/*!
Class RigidBody
\brief
Defines RigidBody, a Component which allows objects to be affected by physics.

NOTES: Torque is incomplete.
*/
/*******************************************************************************/

class RigidBody : public Component {

private:
	//Variable(s)
	float mass;
	float drag;
	float angularDrag;
	float frictionCoefficient;

public:
	//The 3 axes of the game.
	enum AXIS {
	
		X = 0,
		Y,
		Z,
		NUM_AXIS,

	};

	//Variable(s)
	bool useGravity; //Determines if the RigidBody is affected by gravity.
	Vector3 gravity;
	
	bool useFriction; //Determines if the RigidBody is affected by friction.

	Vector3 velocity;
	Vector3 angularVelocity;

	bool freezePosition[NUM_AXIS]; //Determines if the position of the RigidBody on an axis is affected by physics.
	bool freezeRotation[NUM_AXIS]; //Determines if the rotation of the RigidBody on an axis is affected by physics.

	//Constructor(s) & Destructor
	RigidBody();
	virtual ~RigidBody();

	//Getter(s)
	float GetMass();
	float GetDrag();
	float GetAngularDrag();
	float GetFrictionCoefficient();
	
	Vector3 GetVelocity();
	Vector3 GetAngularVelocity();
	Vector3 GetGravity();

	//Setter(s)
	bool SetMass(float mass);
	bool SetDrag(float drag); //NOT USED. WIP
	bool SetAngularDrag(float angularDrag); //NOT USED. WIP
	bool SetFrictionCoefficient(float frictionCoefficient);

	void SetVelocity(Vector3 velocity);
	void SetVelocity(float x, float y, float z);
	void SetAcceleration(Vector3 acceleration, const double& deltaTime);
	void SetAcceleration(float x, float y, float z, const double& deltaTime);

	void SetAngularVelocity(Vector3 angularVelocity);
	void SetAngularVelocity(float x, float y, float z);
	void SetAngularAcceleration(Vector3 angularAcceleration, const double& deltaTime);
	void SetAngularAcceleration(float x, float y, float z, const double& deltaTime);

	void SetGravity(Vector3 gravity);
	void SetGravity(float x, float y, float z);

	//Function(s)
	void FreezePosition(bool x, bool y, bool z);
	void FreezePosition(bool freeze, AXIS axis);
	void FreezeRotation(bool x, bool y, bool z);
	void FreezeRotation(bool freeze, AXIS axis);

	void AddForce(float x, float y, float z, const double& deltaTime);
	void AddForce(Vector3 forceVector, const double& deltaTime);
	void AddTorque(float x, float y, float z, const double& deltaTime);
	void AddTorque(Vector3 torqueVector, const double& deltaTime);

	void ApplyFriction(const double& deltaTime);
	void ApplyGravity(const double& deltaTime);

};

#endif