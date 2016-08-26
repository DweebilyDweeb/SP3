#ifndef COW_OBJECT_H
#define COW_OBJECT_H

#include "Vector3.h"

class Cow_state {

public:
	virtual void Update(const double& deltaTime) = 0;

protected:
	Cow_state();
};

class Idle_State : public Cow_state {

public:
	Idle_State();
	virtual void Update(const double& deltaTime);
};

class Cow {

public:
	Cow(Cow_state *);
	void re_State();
	void change_state(Cow_state *);

private:
	Vector3 pos;
	Vector3 scale;
	Cow_state* state;
};



#endif //COW_OBJECT_H