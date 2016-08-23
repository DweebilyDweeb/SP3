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

};