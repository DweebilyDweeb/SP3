#ifndef COW_OBJECT_H
#define COW_OBJECT_H

#include "Vector3.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "TileMap.h"
#include "Player.h"

enum COW_DIRECTION {
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Cow {

private:

	Vector3 scale;
	Vector3 pos;

	TileMap *tileMap;
	Player *player;
	COW_DIRECTION cowFaces;
	class Cow_state* state;

	float hotspotOffset;
	bool invert;
	bool isMoving;
	bool isRunning;
	bool isTriggered;
	bool isDead;

	double c_timer;
	double c_time_limit;

	int c_health;
public:
	Cow(SpriteAnimation*);
	~Cow();

	void setPosition(const Vector3& pos);
	Vector3 getPosition() const;

	void setScale(const Vector3& scale);
	Vector3 getScale() const;

	void setInvert(const bool& invert);
	bool getInvert() const;

	void setMoving(const bool& move);
	bool getMoving() const;

	void setRunning(const bool& run);
	bool getRunning() const;

	void setHealth(const int& health);
	int getHealth() const;

	void setTriggered(const bool& trigger);
	bool getTriggered() const;

	void setDead(const bool& kek);
	bool getDead() const;

	void setTileMap(TileMap &tileMap);
	void setPlayer(Player &player);
	void setState(Cow_state* state);

	bool CheckCollisionLeft();
	bool CheckCollisionRight();
	bool CheckCollisionUp();
	bool CheckCollisionDown();
	bool CheckPlayer();

	void Update(const double& deltaTime);
	
	// states
	void ChangeStateIdle(const double& deltaTime);
	void ChangeStateRun(const double& deltaTime);
	void ChangeStateDead(const double& deltaTime);
	void ChangeStateWalk(const double& deltaTime);
	void ChangeStateTriggered(const double& deltaTime);

	int getDirectionFace() const;

};


class Cow_state {

public:
	virtual void Idle(Cow* c, const double& deltaTime) = 0;
	virtual void Run(Cow* c, const double& deltaTime) = 0;
	virtual void Dead(Cow* c, const double& deltaTime) = 0;
	virtual void Walk(Cow* c, const double& deltaTime) = 0;
	virtual void Triggered(Cow* c, const double& deltaTime) = 0;
};

class State_Idle : public Cow_state {

public:
	State_Idle() {}
	~State_Idle() {}
	
	void Idle(Cow* c, const double& deltaTime);
	void Walk(Cow* c, const double& deltaTime);
	void Run(Cow* c, const double& deltaTime);
	void Dead(Cow* c, const double& deltaTime);
	void Triggered(Cow* c, const double& deltaTime);
};

class State_Walk : public Cow_state {

public:
	State_Walk() {}
	~State_Walk() {}

	void Idle(Cow* c, const double& deltaTime);
	void Walk(Cow* c, const double& deltaTime);
	void Run(Cow* c, const double& deltaTime);
	void Dead(Cow* c, const double& deltaTime);
	void Triggered(Cow* c, const double& deltaTime);
};

class State_Triggered : public Cow_state {

public:
	State_Triggered() {}
	~State_Triggered() {}

	void Idle(Cow* c, const double& deltaTime);
	void Walk(Cow* c, const double& deltaTime);
	void Run(Cow* c, const double& deltaTime);
	void Dead(Cow* c, const double& deltaTime);
	void Triggered(Cow* c, const double& deltaTime);
};

class State_Run : public Cow_state {

public:
	State_Run() {}
	~State_Run() {}

	void Idle(Cow* c, const double& deltaTime);
	void Walk(Cow* c, const double& deltaTime);
	void Run(Cow* c, const double& deltaTime);
	void Dead(Cow* c, const double& deltaTime);
	void Triggered(Cow* c, const double& deltaTime);
};

class State_Dead : public Cow_state {

public:
	State_Dead() {}
	~State_Dead() {}

	void Idle(Cow* c, const double& deltaTime){};
	void Walk(Cow* c, const double& deltaTime){};
	void Run(Cow* c, const double& deltaTime){};
	void Dead(Cow* c, const double& deltaTime){};
	void Triggered(Cow* c, const double& deltaTime){};
};


#endif //COW_OBJECT_H