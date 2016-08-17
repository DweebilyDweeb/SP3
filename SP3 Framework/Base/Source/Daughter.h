#ifndef DAUGHTER_H_
#define DAUGHTER_H_

#include "Family.h"

class Daughter :public Family
{
public:
	//Virtual Function(s)
	virtual void Init();

	virtual void Update(const double& dt);

	//Constructor(s) & Destructor
	Daughter();
	virtual ~Daughter();
};


#endif