#include "Attributes.h"
#include "SceneManager.h"

Attributes::Attributes()
	: Protein(0)
	, Carbohydrates(0)
	, Fats(0)
	, Vitamins(0)
	, Hydration(0)
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

Attributes Attributes::getAttributes()
{
	return *this;
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

void Attributes::setAttributes(float p, float c, float f, float v, float h)
{
	setProtein(p);
	setCarbohydrates(c);
	setFats(f);
	setVitamins(v);
	setHydration(h);
}

void Attributes::addAttributes(const Attributes& other)
{
	Protein += other.Protein;
	Carbohydrates += other.Carbohydrates;
	Fats += other.Fats;
	Vitamins += other.Vitamins;
	Hydration += other.Hydration;
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

Attributes operator* (const Attributes& lhs, const int& val)
{
	Attributes temp;
	temp.setCarbohydrates(lhs.Carbohydrates * val);
	temp.setFats(lhs.Fats * val);
	temp.setHydration(lhs.Hydration * val);
	temp.setProtein(lhs.Protein * val);
	temp.setVitamins(lhs.Vitamins * val);
	return temp;

}
Attributes Attributes::operator+= (const Attributes& other)
{
	this->Carbohydrates += other.Carbohydrates;
	this->Fats += other.Fats;
	this->Hydration += other.Hydration;
	this->Protein += other.Protein;
	this->Vitamins += other.Vitamins;

	return *this;
}

Attributes Attributes::operator-= (const Attributes& other)
{
	this->Carbohydrates -= other.Carbohydrates;
	this->Fats -= other.Fats;
	this->Hydration -= other.Hydration;
	this->Protein -= other.Protein;   
	this->Vitamins -= other.Vitamins;

	return *this;
}

void Attributes::boundStats()
{
    if (Carbohydrates > maxStat)
        Carbohydrates = maxStat;
    if (Fats > maxStat)
        Fats = maxStat;
    if (Hydration > maxStat)
        Hydration = maxStat;
    if (Protein > maxStat)
        Protein = maxStat;
    if (Vitamins > maxStat)
        Vitamins = maxStat;

    if (Carbohydrates < 0
        || Fats < 0
        || Hydration < 0
        || Protein < 0
        || Vitamins < 0)
    {

        SceneManager::GetInstance().chgCurrEnumScene(LOSE);

        //player.setVelocity(Vector3(0, 0, 0));
    }
}