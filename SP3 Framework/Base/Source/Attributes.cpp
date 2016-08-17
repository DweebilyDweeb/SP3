#include "Attributes.h"

Attributes::Attributes()
	:Protein(50)
	, Carbohydrates(50)
	, Fats(50)
	, Vitamins(50)
	, Hydration(50)
{

}
Attributes::~Attributes()
{

}

float Attributes::getProtein()
{
	return Protein;
}
float Attributes::getCarbohydrates()
{
	return Carbohydrates;
}
float Attributes::getFats()
{
	return Fats;
}
float Attributes::getVitamins()
{
	return Vitamins;
}
float Attributes::getHydration()
{
	return Hydration;
}

void Attributes::addProtein(float value)
{
	Protein += value;
}
void Attributes::addCarbohydrates(float value)
{
	Carbohydrates += value;
}
void Attributes::addFats(float value)
{
	Fats += value;
}
void Attributes::addVitamins(float value)
{
	Vitamins += value;
}
void Attributes::addHydration(float value)
{
	Hydration += value;
}

void Attributes::minusProtein(float value)
{
	Protein -= value;
}
void Attributes::minusCarbohydrates(float value)
{
	Carbohydrates -= value;
}
void Attributes::minusFats(float value)
{
	Fats -= value;
}
void Attributes::minusVitamins(float value)
{
	Vitamins -= value;
}
void Attributes::minusHydration(float value)
{
	Hydration -= value;
}