#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_


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

	void addProtein(float value);
	void addCarbohydrates(float value);
	void addFats(float value);
	void addVitamins(float value);
	void addHydration(float value);

	void minusProtein(float value);
	void minusCarbohydrates(float value);
	void minusFats(float value);
	void minusVitamins(float value);
	void minusHydration(float value);
private:
	float Protein;
	float Carbohydrates;
	float Fats;
	float Vitamins;
	float Hydration;

};

#endif