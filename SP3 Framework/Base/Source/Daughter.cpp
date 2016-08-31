#include "Daughter.h"
#include "Application.h"

Daughter::Daughter()
{

}

Daughter::~Daughter()
{
}

void Daughter::Init()
{
	setProtein(averageStat);
	setCarbohydrates(aboveAverageStat);
	setFats(aboveAverageStat);
	setHydration(averageStat);
	setVitamins(averageStat);
}

void Daughter::Update(const double& dt)
{
	multiplier = 1.f + (Application::clock->getDay() / 10);

	minusProtein(dropRateSlow * multiplier, dt);

	minusCarbohydrates(dropRateFast * multiplier, dt);

	minusFats(dropRateFast * multiplier, dt);

	minusHydration(dropRateSlow * multiplier, dt);

	minusVitamins(dropRateSlow * multiplier, dt);

	calculateHealth();
}