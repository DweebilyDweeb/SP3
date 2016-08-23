#include "Time.h"

Time::Time()
    :
    hour(0),
    minute(0.f),
    day(1),
    active(false),
    rotation(0)
{}

Time::Time(int h, double m)
    :
    hour(h),
    minute(m),
    day(1),
    active(false),
    rotation(0)
{}

Time::Time(int h, double m, int d, bool a)
    :
    hour(h),
    minute(m),
    day(d),
    active(a),
    rotation(0)
{}

Time::~Time()
{}

void Time::UpdateTime(const double& deltaTime)
{
<<<<<<< HEAD
    if (active)
    {
        minute += 1.8 * deltaTime;
        rotation = float(-hour * 30);
        if (minute > 60)
        {
            hour++;
            minute = 0;
        }

        if (hour >= 9)
        {
            hour = minute = 0;
            day++;
        }
    }
=======
	if (active)
	{
		minute += 1.8 * deltaTime;
		rotation = float(-hour * 30);
		if (minute > 60)
		{
			hour++;
			minute = 0;
		}

		if (hour >= 9)
		{
			hour = minute = 0;
			day++;
		}
	}
>>>>>>> e6672cdb6cba78f9c86d717302693dbda0d6f869
}

float Time::getRotation()
{
    return rotation;
}

int Time::getHour()
{
    return hour;
}

double Time::getMinute()
{
    return minute;
}

int Time::getDay()
{
    return day;
}

bool Time::getActive()
{
    return active;
}

Time Time::getTime()
{
    return Time(hour, minute, day, active);
}

void Time::setTime(int h, double min)
{
    hour = h;
    minute = min;
}

void Time::setTime(int h, double min)
{
	hour = h;
	minute = min;
}

std::ostream & operator<<(std::ostream& os, Time& time)
{
    os.precision(3);
    os << time.getHour() << "hr, " << time.getMinute() << "mins, " << time.getDay() << "days, " << time.getActive() << std::endl;
    return os;
}