#include "Platform.h"

Platform::Platform(Font* font, Text* text, RenderWindow* window, int multiplier, Vector2f position) : RenderText(font, text, window) {
	this->multiplier = multiplier;
	this->square = VertexArray(LinesStrip, 5);
	this->square[0].position.x = position.x - 40;
	this->square[0].position.y = position.y + 20;
	this->square[1].position.x = position.x + 40;
	this->square[1].position.y = position.y + 20;
	this->square[2].position.x = position.x + 40;
	this->square[2].position.y = position.y - 20;
	this->square[3].position.x = position.x - 40;
	this->square[3].position.y = position.y - 20;
	this->square[4].position.x = this->square[0].position.x;
	this->square[4].position.y = this->square[0].position.y;
	square[0].color = Color::White; 
	square[1].color = Color::White;
	square[2].color = Color::White;
	square[3].color = Color::White;
	square[4].color = Color::White;
	this->text->setPosition(this->square[3].position.x + 15, this->square[3].position.y - 25);
}

void Platform::render() {
	RenderText::render(); 
	window->draw(square);
}

bool Platform::isLanded(Vector2f landerPos) {
	if (square[3].position.x < landerPos.x && square[2].position.x > landerPos.x) {
		float k = (square[3].position.y - square[2].position.y) / (square[3].position.x - square[2].position.x);
		float b = square[3].position.y - k * square[3].position.x;
		float p = landerPos.y / (landerPos.x * k + b);
		if (p > 0.999) return true;
	}
	return false;
}

void Platform::move(Vector speed) {
	square[0].position.x -= speed.x;
	square[0].position.y += speed.y;
	square[1].position.x -= speed.x;
	square[1].position.y += speed.y;
	square[2].position.x -= speed.x;
	square[2].position.y += speed.y;
	square[3].position.x -= speed.x;
	square[3].position.y += speed.y;
	square[4].position.x -= speed.x;
	square[4].position.y += speed.y;
	text->setPosition(text->getPosition().x - speed.x, text->getPosition().y + speed.y);
}

int Platform::getMultiplier() {
	return multiplier;
}
