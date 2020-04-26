#include "Lander.h"
#define _USE_MATH_DEFINES
#include <math.h>

Lander::Lander(RenderWindow* window, Configuration* cfg) : WindowItem(cfg->getLanderTexturePath(), window) {
	this->G = cfg->getG();
	this->FUEL_COSUMPTION = cfg->getFuelConsumption();
	this->fuel = cfg->getStartAmountOfFuel();
	this->angleToNormal = M_PI_2;
	this->sprite.setPosition(cfg->getWidth() / 2, cfg->getHeight() / 4);
	this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);
	this->sprite.setRotation(radiansToDegrees(-angleToNormal));
	this->speed = new Vector(1.0, 0);
	this->thrust = new  Vector(0, 0);
	this->flames = new WindowItem(cfg->getFlamesTexturePath(), window);
	this->flames->sprite.setOrigin(this->flames->sprite.getGlobalBounds().width / 2, this->flames->sprite.getGlobalBounds().height);
	this->flames->sprite.rotate(90);
	this->flames->sprite.setPosition(this->sprite.getPosition());
	this->flames->sprite.setScale(0.1, 0.1);
	this->flames->sprite.setColor(Color::White);

	if (!engineSoundBuffer.loadFromFile(cfg->getEngineSoundPath())) cout << "Error loading engine sound" << endl;
	engineSound.setBuffer(engineSoundBuffer);
	engineSound.setVolume(cfg->getSoundsVolume());
	engineSound.setLoop(true);
	engineSoundEnable = false;
}

Lander::~Lander() {
	if (speed) delete speed;
	if (thrust) delete thrust;
	if (flames) delete flames;
}

void Lander::rotatePositive() {
	angleToNormal += UNIT_ANGLE;
	thrust->rotate(UNIT_ANGLE);
	sprite.rotate(radiansToDegrees(-UNIT_ANGLE));
	flames->sprite.rotate(radiansToDegrees(-UNIT_ANGLE));
}

void Lander::rotateNegative() {
	angleToNormal -= UNIT_ANGLE;
	thrust->rotate(-UNIT_ANGLE);
	sprite.rotate(radiansToDegrees(UNIT_ANGLE));
	flames->sprite.rotate(radiansToDegrees(UNIT_ANGLE));
}

void Lander::update() {
	Vector speed = *this->speed;

	speed += *thrust;
	this->speed->x = speed.x;
	this->speed->y = speed.y;
	this->speed->y -= G;
	this->fuel -= FUEL_COSUMPTION * thrust->getModule();
	if (fuel < 0) fuel = 0;

	thrust->getModule() == 0 ? flames->sprite.setScale(0, 0) : flames->sprite.setScale(0.04 + thrust->getModule() * 0.17f, 0.04 + thrust->getModule() * 0.17f);

	if (!engineSoundEnable) {
		if (thrust->getModule() > 0) {
			engineSound.play();
			engineSoundEnable = true;
		}
	}
	if (engineSoundEnable) {
		if (thrust->getModule() == 0) {
			engineSound.pause();
			engineSoundEnable = false;
		}
	}
}

void Lander::increaseThrust() {
	if (fuel == 0) return;
	Vector resultThrust = *thrust;
	Vector rotatedUnit = UNIT; //vector that encapsulates speed shift in this moment
	rotatedUnit *= 0.25f;
	rotatedUnit.rotate(angleToNormal);
	resultThrust += rotatedUnit;

	thrust->x = resultThrust.x;
	thrust->y = resultThrust.y;
	
}

void Lander::decreaseThrust() {
	Vector resultThrust = *thrust;
	Vector rotatedUnit = UNIT; //vector that encapsulates speed shift in this moment
	rotatedUnit *= 0.25f;
	rotatedUnit.rotate(angleToNormal);
	resultThrust -= rotatedUnit;

	//prevent the thrust vector being negative
	if ((resultThrust.x > 0 && thrust->x < 0) || (resultThrust.x < 0 && thrust->x > 0) || (resultThrust.y > 0 && thrust->y < 0) || (resultThrust.y < 0 && thrust->y > 0) || (thrust->x == 0 && thrust->y == 0)) {
		offThrust();
	}
	else {
		thrust->x = resultThrust.x;
		thrust->y = resultThrust.y;
	}
}

void Lander::offThrust() {
	thrust->x = 0;
	thrust->y = 0;
}

float Lander::radiansToDegrees(float radian) {
	return 180 * radian / M_PI;
}

void Lander::render() {
	flames->render();
	WindowItem::render();
}

Vector Lander::getSpeed() {
	return *speed;
}

Vector2f Lander::getPosition() {
	return sprite.getPosition();
}

Vector Lander::getThrust() {
	return *thrust;
}

float Lander::getFuel() {
	return fuel;
}

void Lander::notifyOnEnd() {
	engineSoundEnable = false;
	engineSound.stop();
}