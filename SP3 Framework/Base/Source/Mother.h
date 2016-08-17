#ifndef MOTHER_H_
#define MOTHER_H_

#include "Family.h"

class Mother :public Family
{
public:
	//Virtual Function(s)
	virtual void Init();

	virtual void Update(const double& dt);

	//Constructor(s) & Destructor
	Mother();
	virtual ~Mother();
};


#endif