#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {

	float x, y;
	Vector2(float x = 0.0f, float y = 0.0f); //default constructor
	Vector2(const Vector2 &rhs); //copy constructor
	void Set(float x, float y); //Set all data
	Vector2 operator+(const Vector2& rhs) const; //Vector addition
	Vector2& operator+=(const Vector2& rhs); //Vector addition
	Vector2 operator-(const Vector2& rhs) const; //Vector subtraction
	Vector2& operator-=(const Vector2& rhs); //Vector subtraction
	Vector2 operator-(void) const; //Unary negation
	Vector2 operator*(const float& scalar) const; //Scalar multiplication
	Vector2& operator*=(const float& scalar); //Scalar multiplication
	float Length(void) const; //Get magnitude
	float LengthSquared(void) const; //Get magnitude
	float Dot(const Vector2& rhs) const; //Dot product
	Vector2 Normalized(void); //Return a copy of this vector, normalized
	Vector2& Normalize();

};

#endif