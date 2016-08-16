#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Maths.h"
#include "GameObject.h"

struct AspectRatio {

public:
	//Variable(s)
	unsigned int x, y;

	//Constructor(s) & Destructor
	AspectRatio(const unsigned int& x = 16, const unsigned int& y = 9) {
		Set(x, y);
	}
	~AspectRatio() {}

	//Setter(s)
	void Set(const unsigned int& x, const unsigned int& y) {
		if (x < 1) {
			this->x = 1;
		} else {
			this->x = x;
		}
		if (y < 1) {
			this->y = 1;
		} else {
			this->y = y;
		}
		unsigned int hcf = HCF(this->x, this->y);
		this->x /= hcf;
		this->y /= hcf;
	}

};

class Camera : public GameObject {

private:
	//Perspective
	float FOV;
	float nearClippingPlane;
	float farClippingPlane;

	//Orthographic
	bool isOrtho;

public:
	Transform transform;
	float orthoSize;

	AspectRatio aspectRatio;

	//Constructor(s) & Destructor
	Camera();
	virtual ~Camera();

	void SetFOV(const float& FOV);
	float GetFOV();

	void SetOrthoSize(const float& orthoSize);
	float GetOrthoSize() const;

	void SetOrtho();
	void SetPerspective();
	bool IsOrtho() const;

	void SetNearClippingPlane(const float& nearClippingPlane);
	void SetFarClippingPlane(const float& nearClippingPlane);
	float GetNearClippingPlane() const;
	float GetFarClippingPlane() const;

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);

};

#endif