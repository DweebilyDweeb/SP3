#include "Mother.h"
#include "Application.h"

Mother::Mother()
{
	
}

Mother::~Mother()
{
}

void Mother::Init()
{
	setProtein(averageStat);
	setCarbohydrates(aboveAverageStat);
	setFats(averageStat);
	setHydration(averageStat);
	setVitamins(aboveAverageStat);
}

void Mother::Update(const double& dt)
{
	multiplier = 1.f + (Application::clock->getDay() / 10);

	minusProtein(dropRateSlow * multiplier, dt);

	minusCarbohydrates(dropRateFast * multiplier, dt);

	minusFats(dropRateSlow * multiplier, dt);
	
	minusHydration(dropRateSlow * multiplier, dt);

	minusVitamins(dropRateFast * multiplier, dt);

	calculateHealth();
}