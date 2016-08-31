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
	setCarbohydrates(belowAverageStat);
	setFats(aboveAverageStat);
	setHydration(averageStat);
	setVitamins(averageStat);
}

void Daughter::Update(const double& dt)
{
	multiplier = 1.f + (Application::clock->getDay() / 10);
	if (Protein > maximumStat * 0.5f)
		minusProtein(dropRateSlow * multiplier, dt);
	else
		minusProtein(dropRateFast * multiplier, dt);

	if (Carbohydrates > maximumStat * 0.5f)
		minusCarbohydrates(dropRateSlow * multiplier, dt);
	else
		minusCarbohydrates(dropRateFast * multiplier, dt);

	if (Fats > maximumStat * 0.5f)
		minusFats(dropRateSlow * multiplier, dt);
	else
		minusFats(dropRateFast * multiplier, dt);

	if (Hydration > maximumStat * 0.5f)
		minusHydration(dropRateSlow * multiplier, dt);
	else
		minusHydration(dropRateFast * multiplier, dt);

	if (Vitamins > maximumStat * 0.5f)
		minusVitamins(dropRateSlow * multiplier, dt);
	else
		minusVitamins(dropRateFast * multiplier, dt);

	calculateHealth();

	calculateHealth();
}