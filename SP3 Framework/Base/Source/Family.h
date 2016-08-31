#ifndef FAMILY_H_
#define FAMILY_H_

#include "Attributes.h"

class Family :public Attributes
{
public:
	//Virtual Function(s)
	virtual void Init() = 0;
	virtual void Update(const double& dt) = 0;
	//virtual void Render() = 0;
	//virtual void Exit() = 0;

	//Constructor(s) & Destructor
	Family() {}
	virtual ~Family() {}
protected:
	float multiplier;
};


#endif