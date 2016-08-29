#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "LoadCSV.h"

using std::stof;

#define statDropRateSlow stof(getDataFromCSV("CSV//data.csv", "statDropRateSlow"))
#define statDropRateFast stof(getDataFromCSV("CSV//data.csv", "statDropRateFast"))
#define maxStat stof(getDataFromCSV("CSV//data.csv", "maxStat"))
#define statAboveAverage stof(getDataFromCSV("CSV//data.csv", "statAboveAverage"))
#define statBelowAverage stof(getDataFromCSV("CSV//data.csv", "statBelowAverage"))
#define statAverage stof(getDataFromCSV("CSV//data.csv", "statAverage"))


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
    Attributes getAttributes();

    void setProtein(float value);
    void setCarbohydrates(float value);
    void setFats(float value);
    void setVitamins(float value);
    void setHydration(float value);
    void setAttributes(float p, float c, float f, float v, float h);
	
	void addAttributes(const Attributes& other);

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
    void boundStats();

    friend Attributes operator+ (const Attributes&, const Attributes&);
	friend Attributes operator- (const Attributes&, const Attributes&);
	friend Attributes operator* (const Attributes&, const int& val);
	Attributes operator+= (const Attributes& other);
    Attributes operator-= (const Attributes& other);

protected:
    float Protein;
    float Carbohydrates;
    float Fats;
    float Vitamins;
    float Hydration;

    float Health;

};

#endif