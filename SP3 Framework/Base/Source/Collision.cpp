#include "Collision.h"

bool LineSphereCollide(Vector3 lineSource, Vector3 lineDirection, float lineLength, Vector3 spherePosition, float sphereRadius) {

	if ((lineSource - spherePosition).LengthSquared() <= sphereRadius * sphereRadius) {
		return true;
	}

	Vector3 closestPoint = (spherePosition - lineSource).Projection(lineDirection * lineLength) + lineSource;
	if ((spherePosition - closestPoint).LengthSquared() <= sphereRadius * sphereRadius) {
		return true;
	}

	return false;

}