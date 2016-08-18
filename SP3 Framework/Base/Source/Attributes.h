#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#define statDropRateSlow 0.1f
#define statDropRateFast 0.3f
#define maxStat 100.f
#define statAboveAverage 80.f
#define statBelowAverage 30.f
#define statAverage 60.f

class Attributes
{
public:
	Attributes();
	~Attributes();

	float getProtein();
	float getCarbohydrates();
	float getFats();
	float getVitamins();
	float getHydration();
	float getHealth();

	void setProtein(float value);
	void setCarbohydrates(float value);
	void setFats(float value);
	void setVitamins(float value);
	void setHydration(float value);

	void addProtein(float value);
	void addCarbohydrates(float value);
	void addFats(float value);
	void addVitamins(float value);
	void addHydration(float value);

	void minusProtein(const float& value, double dt);
	void minusCarbohydrates(const float& value, double dt);
	void minusFats(const float& value, double dt);
	void minusVitamins(const float&  value, double dt);
	void minusHydration(const float&  value, double dt);

	void calculateHealth();
protected:
	float Protein;
	float Carbohydrates;
	float Fats;
	float Vitamins;
	float Hydration;

	float Health;

};

#endif