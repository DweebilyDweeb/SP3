#include "Mother.h"


Mother::Mother()
{
	
}

Mother::~Mother()
{
}

void Mother::Init()
{
	setProtein(averageStat);
	setCarbohydrates(belowAverageStat);
	setFats(averageStat);
	setHydration(averageStat);
	setVitamins(aboveAverageStat);
}

void Mother::Update(const double& dt)
{
	if (Protein > maximumStat * 0.5f)
		minusProtein(dropRateSlow, dt);
	else
		minusProtein(dropRateFast, dt);

	if (Carbohydrates > maximumStat * 0.5f)
		minusCarbohydrates(dropRateSlow, dt);
	else
		minusCarbohydrates(dropRateFast, dt);

	if (Fats > maximumStat * 0.5f)
		minusFats(dropRateSlow, dt);
	else
		minusFats(dropRateFast, dt);

	if (Hydration > maximumStat * 0.5f)
		minusHydration(dropRateSlow, dt);
	else
		minusHydration(dropRateFast, dt);

	if (Vitamins > maximumStat * 0.5f)
		minusVitamins(dropRateSlow, dt);
	else
		minusVitamins(dropRateFast, dt);

	calculateHealth();
}