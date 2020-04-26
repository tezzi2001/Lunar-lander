#include "Configuration.h"

Configuration::Configuration(string path) {
	ifstream config(path);

	appName = extractData(&config);
	aboutTexturePath = extractData(&config);
	controlsPathForAbout = extractData(&config);
	buttonTexturePath = extractData(&config);
	menuTexturePath = extractData(&config);
	flamesTexturePath = extractData(&config);
	landerTexturePath = extractData(&config);
	fontPath = extractData(&config);
	iconPath = extractData(&config);
	engineSoundPath = extractData(&config);
	spaceMusicPath = extractData(&config);
	explosionSoundPath = extractData(&config);

	antialiasingLevel = stoi(extractData(&config));
	soundsVolume = stoi(extractData(&config));
	musicVolume = stoi(extractData(&config));
	width = stoi(extractData(&config));
	height = stoi(extractData(&config));
	startAmountOfFuel = stof(extractData(&config));
	fuelConsumption = stof(extractData(&config));
	g = stof(extractData(&config));
	maxLandingSpeedX = stof(extractData(&config));
	maxLandingSpeedY = stof(extractData(&config));

	config.close();
}

string Configuration::getAppName() {
	return appName;
}

string Configuration::getAboutTexturePath() {
	return aboutTexturePath;
}

string Configuration::getControlsPathForAbout() {
	return controlsPathForAbout;
}

string Configuration::getButtonTexturePath() {
	return buttonTexturePath;
}

string Configuration::getMenuTexturePath() {
	return menuTexturePath;
}

string Configuration::getFlamesTexturePath() {
	return flamesTexturePath;
}

string Configuration::getLanderTexturePath() {
	return landerTexturePath;
}

string Configuration::getFontPath() {
	return fontPath;
}

string Configuration::getIconPath() {
	return iconPath;
}

string Configuration::getEngineSoundPath() {
	return engineSoundPath;
}

string Configuration::getSpaceMusicPath() {
	return spaceMusicPath;
}

string Configuration::getExplosionSoundPath() {
	return explosionSoundPath;
}

int Configuration::getAntialiasingLevel() {
	return antialiasingLevel;
}

int Configuration::getSoundsVolume() {
	return soundsVolume;
}

int Configuration::getMusicVolume() {
	return musicVolume;
}

int Configuration::getWidth() {
	return width;
}
int Configuration::getHeight() {
	return height;
}

int Configuration::getStartAmountOfFuel() {
	return startAmountOfFuel;
}

float Configuration::getFuelConsumption() {
	return fuelConsumption;
}

float Configuration::getG() {
	return g;
}

float Configuration::getMaxLandingSpeedX() {
	return maxLandingSpeedX;
}

float Configuration::getMaxLandingSpeedY() {
	return maxLandingSpeedY;
}

string Configuration::extractData(ifstream *config) {
	string line;
	int index;
	getline(*config, line);
	if (line.find_first_of('#') == 0 || line.empty()) return extractData(config); //if line is commented
	index = line.find_first_of(':');
	if (index == -1) { //if it`s an empty line
		printf("An error occured during reading the configuration file!");
		exit(-1);
	} else {
		return line.substr(index + 1);
	}
}
