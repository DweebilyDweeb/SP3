#ifndef SON_H_
#define SON_H_

#include "Family.h"

class Son :public Family
{
public:
	//Virtual Function(s)
	virtual void Init();

	virtual void Update(const double& dt);

	//Constructor(s) & Destructor
	Son();
	virtual ~Son();
};


#endif