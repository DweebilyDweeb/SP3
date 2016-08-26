#include "Mother.h"


Mother::Mother()
{
	
}

Mother::~Mother()
{
}

void Mother::Init()
{
	setProtein(statAverage);
	setCarbohydrates(statBelowAverage);
	setFats(statAverage);
	setHydration(statAverage);
	setVitamins(stoi(LoadCSV("CSV//data.csv", "statAboveAverage")));
}

void Mother::Update(const double& dt)
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