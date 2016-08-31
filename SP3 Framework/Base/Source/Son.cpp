#include "Son.h"
#include "Application.h"

Son::Son()
{
}

Son::~Son()
{
}

void Son::Init()
{
	setProtein(aboveAverageStat);
	setCarbohydrates(averageStat);
	setFats(aboveAverageStat);
	setHydration(averageStat);
	setVitamins(averageStat);
}

void Son::Update(const double& dt)
{
	multiplier = 1.f + (Application::clock->getDay() / 10);
	minusProtein(dropRateFast * multiplier, dt);

	minusCarbohydrates(dropRateSlow * multiplier, dt);

	minusFats(dropRateFast * multiplier, dt);

	minusHydration(dropRateSlow * multiplier, dt);

	minusVitamins(dropRateSlow * multiplier, dt);

	calculateHealth();
}