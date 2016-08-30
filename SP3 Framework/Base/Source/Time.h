#ifndef TIME_H
#define TIME_H

#include <ostream>
#include "Scene3D.h"

class Time
{
	int hour;
	double minute;

	int day;
	bool active;
	bool fastForward;
	float rotation;
public:
	Time();
	Time(int h, double m);
	Time(int h, double m, int d, bool a);
	~Time();

	void setTime(int h, double m);
	void setTime(int h, double m, int day);
	void setDay();
	void setActive(bool activity);
	void setFastForward(bool FF);
	void addDays(int d);

	int getHour();
	double getMinute();
	int getDay();
	bool getActive();
	Time getTime();
	float getRotation();
	bool dayChanged();

	void Init(){};
	void RenderTime(){};
	void UpdateTime(const double& deltaTime);

	friend std::ostream & operator<< (std::ostream&, Time&);
};

#endif