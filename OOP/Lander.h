#pragma once
#include "SFML/Audio.hpp"
#include "Vector.h"
#include "WindowItem.h"
#include "Configuration.h"

using namespace sf;

class Lander : public WindowItem {
private:
	float G; 
	const float UNIT_ANGLE = 0.1;
	const float MAX_THRUST = 10;
	const Vector UNIT = Vector(0, 0.01);
	float FUEL_COSUMPTION;

	float angleToNormal; //in radians [-pi/2; pi/2]
	float fuel;
	Vector* speed;
	Vector* thrust;
	WindowItem* flames;
	SoundBuffer engineSoundBuffer;
	Sound engineSound;
	bool engineSoundEnable;

	float radiansToDegrees(float);
public:
	Lander(RenderWindow*, Configuration*);
	~Lander();
	void rotatePositive(); //rotate counter-clockwise
	void rotateNegative(); //rotate clockwise
	void increaseThrust();
	void decreaseThrust();
	void offThrust();
	void update(); //invoke to recalculate variables of lander. Should be always invoken before method render()
	void render();
	Vector getSpeed();
	Vector2f getPosition();
	Vector getThrust();
	float getFuel();
	void notifyOnEnd();
};