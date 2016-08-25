#ifndef PLAYER_SS_H
#define PLAYER_SS_H

#include "Player.h"
#include "Vector2.h"

//Side scrolling Player
class PlayerSS : public Player {

protected:
	float mass;
	float maxSpeed;
	float walkAcceleration;
	float jumpAcceleration;
	float gravity;
	bool onGround;
    bool rotateClock;
    bool counterClock;
    
    float spin;
	void MoveLeft(const double& deltaTime);
	void MoveRight(const double& deltaTime);
private:
	bool invert;
	float accumTime;
public:
	PlayerSS();
	virtual ~PlayerSS();
    int Level;
	virtual void Update(const double& deltaTime);

	bool getOnGround();
	bool getInvert();
};

#endif