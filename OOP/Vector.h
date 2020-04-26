#pragma once
#include "SFML/System/Vector2.hpp"

class Vector : public sf::Vector2f {
public:
	Vector(float, float);
	Vector(sf::Vector2f);
	void rotate(float);
	float getAngleToVector(Vector);
	float getScalarProduct(Vector);
	float getModule();
};

