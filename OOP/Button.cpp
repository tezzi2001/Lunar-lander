#include "Button.h"

Button::Button(RenderWindow* window, string texturePath, string fontPath, int index, string name) : RenderText(NULL, NULL, window), WindowItem(texturePath, window) {
	Font* font = new Font();
	Text* text = new Text();
	Vector2u windowSize = window->getSize();

	this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	this->sprite.setPosition(windowSize.x / 2, (index + 2) * windowSize.y / 5);
	if(!font->loadFromFile(fontPath)) printf("font loading error!\n");
	text->setFont(*font);
	text->setString(name);
	text->setPosition(windowSize.x / 2.5, (index + 1.65) * windowSize.y / 5);
	text->setCharacterSize(100);

	this->font = font;
	this->text = text;

	fontGarbage.push_back(font);
	textGarbage.push_back(text);
};

string Button::getName() {
	return text->getString();
}

bool Button::contains(Vector2i mousePos) {
	return sprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void Button::render() {
	WindowItem::render();
	RenderText::render();
}