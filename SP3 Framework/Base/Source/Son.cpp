#include "Son.h"


Son::Son()
{
}

Son::~Son()
{
}

void Son::Init()
{
	setProtein(statAboveAverage);
	setCarbohydrates(statAverage);
	setFats(statBelowAverage);
	setHydration(statAverage);
	setVitamins(statAverage);
}

void Son::Update(const double& dt)
{
	if (Protein > maxStat * 0.5f)
		minusProtein(statDropRateSlow, dt);
	else
		minusProtein(statDropRateFast, dt);

	if (Carbohydrates > maxStat * 0.5f)
		minusCarbohydrates(statDropRateSlow, dt);
	else
		minusCarbohydrates(statDropRateFast, dt);

	if (Fats > maxStat * 0.5f)
		minusFats(statDropRateSlow, dt);
	else
		minusFats(statDropRateFast, dt);

	if (Hydration > maxStat * 0.5f)
		minusHydration(statDropRateSlow, dt);
	else
		minusHydration(statDropRateFast, dt);

	if (Vitamins > maxStat * 0.5f)
		minusVitamins(statDropRateSlow, dt);
	else
		minusVitamins(statDropRateFast, dt);

	calculateHealth();
}