#include "About.h"
#include <iostream>
#include <fstream>

About::About(RenderWindow* window, Configuration* cfg) : WindowItem(cfg->getAboutTexturePath(), window) {
	Font* font = new Font();
	font->loadFromFile(cfg->getFontPath());

	Text* descriptionText = new Text();
	descriptionText->setFont(*font);
	descriptionText->setString("Term paper \n sbj.: object oriented programming \n by student Bondarenko Bohdan \n 225 - SP form");
	descriptionText->setCharacterSize(50);
	descriptionText->setPosition(100, 100);

	Text* controlsText = new Text();
	controlsText->setFont(*font);
	controlsText->setString(getControls(cfg->getControlsPathForAbout()));
	controlsText->setCharacterSize(50);
	controlsText->setPosition(1100, 100);

	this->description = new RenderText(font, descriptionText, window);
	this->controls = new RenderText(font, controlsText, window);
	this->buttonBack = new Button(window, cfg->getButtonTexturePath(), cfg->getFontPath(), 2, "      Back ");

	fontGarbage.push_back(font);
	textGarbage.push_back(descriptionText);
	textGarbage.push_back(controlsText);
}

About::~About() {
	if (buttonBack) delete buttonBack;
	if (description) delete description;
	if (controls) delete controls;
}

string About::getControls(string path) {
	ifstream descriptionFile(path);
	string temp;
	string result;
	while (getline(descriptionFile, temp)) {
		result.append(temp).append("\n");
	}
	descriptionFile.close();
	return result;
}

bool About::isBackButtonPressed(Vector2i mousePos) {
	return buttonBack->contains(mousePos);
}

void About::render() {
	WindowItem::render();
	buttonBack->render();
	description->render();
	controls->render();
}
