#include "Vector.h"
#include <math.h>

Vector::Vector(float x, float y) : sf::Vector2f(x, y) {}

Vector::Vector(sf::Vector2f v) : sf::Vector2f(v) {}

void Vector::rotate(float angle) {
	float tempX = x, tempY = y;
	x = tempX * cos(angle) - tempY * sin(angle);
	y = tempY * cos(angle) + tempX * sin(angle);
}

float Vector::getAngleToVector(Vector vector) {
	return acosf(this->getScalarProduct(vector)/(this->getModule()*vector.getModule()));
}

float Vector::getScalarProduct(Vector vector) {
	return vector.x*x + vector.y*y;
}

float Vector::getModule() {
	return sqrtf(x * x + y * y);
}