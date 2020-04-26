#include "Menu.h"
#include "Dispatcher.h"

Menu::Menu(RenderWindow* window, Configuration *cfg) : WindowItem(cfg->getMenuTexturePath(), window) {
	Vector2u windowSize = window->getSize();
	Button* button;
	string buttonTexturePath = cfg->getButtonTexturePath();
	string fontPath = cfg->getFontPath();
	button = new Button(window, buttonTexturePath, fontPath, 0, "Start game");
	buttons.push_back(button);
	button = new Button(window, buttonTexturePath, fontPath, 1, "    About  ");
	buttons.push_back(button);
	button = new Button(window, buttonTexturePath, fontPath, 2, "      Exit ");
	buttons.push_back(button);
	this->cfg = cfg;
}

Menu::~Menu() {
	for (Button* button : buttons) {
		if (button) delete button;
	}
}

void Menu::render() {
	Font font;
	font.loadFromFile(cfg->getFontPath());
	Text title;
	title.setCharacterSize(200);
	title.setFont(font);
	title.setString(cfg->getAppName());
	title.setPosition(cfg->getWidth()/3.8, cfg->getHeight()/40);
	WindowItem::render();
	window->draw(title);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render();
	}
}

int Menu::getContextByButtonPressed(Vector2i mousePos) {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->contains(mousePos)) {
			string name = buttons[i]->getName();
			if (name == "Start game") {
				return Dispatcher::GAME;
			} else if (name == "    About  ") { 
				return Dispatcher::ABOUT;
			} else if (name == "      Exit ") {
				return Dispatcher::EXIT;
			}
		}
	}
	return Dispatcher::MENU;
}