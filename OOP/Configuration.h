#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Configuration {
private:
	string appName;
	string aboutTexturePath;
	string controlsPathForAbout;
	string buttonTexturePath;
	string menuTexturePath;
	string flamesTexturePath;
	string landerTexturePath;
	string fontPath;
	string iconPath;
	string engineSoundPath;
	string spaceMusicPath;
	string explosionSoundPath;
	int antialiasingLevel;
	int soundsVolume;
	int musicVolume;
	int width;
	int height;
	int startAmountOfFuel;
	float fuelConsumption;
	float g;
	float maxLandingSpeedX;
	float maxLandingSpeedY;

	Configuration(string);
	string extractData(ifstream*);
public:
	static Configuration& getInstance(string path) {
		static Configuration instance(path);
		return instance;
	}

	string getAppName();
	string getAboutTexturePath();
	string getControlsPathForAbout();
	string getButtonTexturePath();
	string getMenuTexturePath();
	string getFlamesTexturePath();
	string getLanderTexturePath();
	string getFontPath();
	string getIconPath();
	string getEngineSoundPath();
	string getSpaceMusicPath();
	string getExplosionSoundPath();
	int getAntialiasingLevel();
	int getSoundsVolume();
	int getMusicVolume();
	int getWidth();
	int getHeight();
	int getStartAmountOfFuel();
	float getFuelConsumption();
	float getG();
	float getMaxLandingSpeedX();
	float getMaxLandingSpeedY();
};