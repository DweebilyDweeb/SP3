#include "Vector3.h"
#include "GameObject.h"

struct ChickenObject : public GameObject
{
	enum CHICKEN_STATES
	{
		IDLE,
		WALKING,
		RUNNING,
		TOTAL_STATES,
	};

	CHICKEN_STATES CS;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 dir;
	bool active;
	float rotation;
	float mass;
	float timeAlive;

	ChickenObject();
	~ChickenObject();

	void setChickenStates(CHICKEN_STATES state);
	void setPos(Vector3 position);
	void setVel(Vector3 velocity);
	void setScale(Vector3 scale);
	void setDir(Vector3 dir);
	void setActive(bool activity);
	void setRotation(float rotate);
	void setMass(float heavy);
	void setTimeAlive(float time);

	CHICKEN_STATES getChickenStates();
	Vector3 getPos();
	Vector3 getVel();
	Vector3 getScale();
	Vector3 getDir();
	bool getActive();
	float getRotation();
	float getMass();
	float getTimeAlive();
};