#include "Attributes.h"

Attributes::Attributes()
	: Protein(50)
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

float Attributes::getHealth()
{
	return Health;
}

void Attributes::setProtein(float value)
{
	Protein = value;
}
void Attributes::setCarbohydrates(float value)
{
	Carbohydrates = value;
}
void Attributes::setFats(float value)
{
	Fats = value;
}
void Attributes::setVitamins(float value)
{
	Vitamins = value;
}
void Attributes::setHydration(float value)
{
	Hydration = value;
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

void Attributes::minusProtein(const float& value, double dt)
{
	Protein -= value * (float)dt;
}
void Attributes::minusCarbohydrates(const float& value, double dt)
{
	Carbohydrates -= value * (float)dt;
}
void Attributes::minusFats(const float& value, double dt)
{
	Fats -= value * (float)dt;
}
void Attributes::minusVitamins(const float& value, double dt)
{
	Vitamins -= value * (float)dt;
}
void Attributes::minusHydration(const float& value, double dt)
{
	Hydration -= value * (float)dt;
}

void Attributes::calculateHealth()
{
	Health = (Protein * 0.1f) * (Carbohydrates * 0.1f) * (Fats * 0.1f) * (Vitamins * 0.1f) * (Hydration * 0.1f);
}

Attributes operator+ (const Attributes& lhs, const Attributes& rhs)
{
	Attributes temp;
	temp.setCarbohydrates(lhs.Carbohydrates + rhs.Carbohydrates);
	temp.setFats(lhs.Fats + rhs.Fats);
	temp.setHydration(lhs.Hydration + rhs.Hydration);
	temp.setProtein(lhs.Protein + rhs.Protein);
	temp.setVitamins(lhs.Vitamins + rhs.Vitamins);
	return temp;
}

Attributes operator- (const Attributes& lhs, const Attributes& rhs)
{
	Attributes temp;
	temp.setCarbohydrates(lhs.Carbohydrates - rhs.Carbohydrates);
	temp.setFats(lhs.Fats - rhs.Fats);
	temp.setHydration(lhs.Hydration - rhs.Hydration);
	temp.setProtein(lhs.Protein - rhs.Protein);
	temp.setVitamins(lhs.Vitamins - rhs.Vitamins);
	return temp;
}

Attributes Attributes::operator+= (const Attributes& other)
{
	this->Carbohydrates + other.Carbohydrates;
	this->Fats + other.Fats;
	this->Hydration + other.Hydration;
	this->Protein + other.Protein;
	this->Vitamins + other.Vitamins;

	return *this;
}

Attributes Attributes::operator-= (const Attributes& other)
{
	this->Carbohydrates - other.Carbohydrates;
	this->Fats - other.Fats;
	this->Hydration - other.Hydration;
	this->Protein - other.Protein;
	this->Vitamins - other.Vitamins;

	return *this;
}