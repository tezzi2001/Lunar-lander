#include "RenderText.h"
#include <iostream>

RenderText::RenderText(Font* font, Text* text, RenderWindow* window) {
	this->font = font;
	this->text = text;
	this->window = window;
}

void RenderText::render() {
	window->draw(*text);
}

void RenderText::setString(string s) {
	text->setString(s);
}

void RenderText::center() {
	text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);
	text->setPosition(window->getSize().x / 2, window->getSize().y / 2);
}
