#include "Terrain.h"
#include <stdlib.h>
#include <time.h>

Terrain::Terrain(RenderWindow* window, Configuration* cfg) {
	this->MAX_LANDING_SPEED_X = cfg->getMaxLandingSpeedX();
	this->MAX_LANDING_SPEED_Y = cfg->getMaxLandingSpeedY();
	this->window = window;
	this->cfg = cfg;
	srand(time(NULL));
	int currentWidth = 0;
	int currentHeight = rand() % MAX_LINE_HEIGHT;
	int windowWidth = cfg->getWidth();
	int windowHeight = cfg->getHeight();
	int totalWidth = 0;
	Vector2f previousPosition(0, windowHeight - currentHeight - MIN_LINE_HEIGHT);

	while (totalWidth < windowWidth) {
		currentWidth = rand() % MAX_LINE_WIDTH;
		currentHeight = rand() % MAX_LINE_HEIGHT;
		totalWidth += currentWidth;
		VertexArray line(Lines, 2);

		line[0].position = previousPosition;
		line[1].position = Vector2f(totalWidth, windowHeight - currentHeight - MIN_LINE_HEIGHT);
		previousPosition = line[1].position;

		lines.push_back(line);
	}
}

Terrain::~Terrain() {
	for (Platform* platform : platforms) {
		if (platform) delete platform;
	}
}

void Terrain::update(Vector speed, Vector2f landerPos) {
	for (int i = 0; i < lines.size(); i++) {
		lines[i][0].position.x -= speed.x;
		lines[i][0].position.y += speed.y;
		lines[i][1].position.x -= speed.x;
		lines[i][1].position.y += speed.y;
	}

	for (int i = 0; i < platforms.size(); i++) {
		platforms[i]->move(speed);
	}

	Vertex lastPoint = lines.back()[1];
	Vector2f newPoint;

	if (lastPoint.position.x < cfg->getWidth()) {
		int probability = rand() % 100;
		VertexArray line(Lines, 2);

		line[0].position = lastPoint.position;
		line[1].position = lastPoint.position;
		line[1].position.x += rand() % MAX_LINE_WIDTH;
		line[1].position.y = cfg->getHeight() - rand() % MAX_LINE_HEIGHT - MIN_LINE_HEIGHT;

		newPoint = Vector2f(line[1].position.x, line[1].position.y);
		Font *font = new Font();
		font->loadFromFile(cfg->getFontPath());
		Text *text = new Text();
		text->setFont(*font);
		text->setFillColor(Color::White);
		text->setCharacterSize(60);
		text->setPosition(newPoint);
		if (probability >= 0 && probability < 5) {
			text->setString("x2");
			platforms.push_back(new Platform(font, text, this->window, 2, newPoint));
		}
		if (probability >= 5 && probability < 13) {
			text->setString("x3");
			platforms.push_back(new Platform(font, text, this->window, 3, newPoint));
		}
		if (probability >= 13 && probability < 25) {
			text->setString("x4");
			platforms.push_back(new Platform(font, text, this->window, 4, newPoint));
		}

		lines.push_back(line);
	}
}

void Terrain::render() {
	for (int i = 0; i < lines.size(); i++) window->draw(lines[i]);
	for (int i = 0; i < platforms.size(); i++) platforms[i]->render();

}
/*
	this method is using simple line equality (y = k*x + b)
	and variable p to introduce precision as float variables can`t be checked for equality
*/
bool Terrain::isCrushed(Vector2f landerPos) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i][0].position.x < landerPos.x && lines[i][1].position.x > landerPos.x) {
			float k = (lines[i][0].position.y - lines[i][1].position.y) / (lines[i][0].position.x - lines[i][1].position.x);
			float b = lines[i][0].position.y - k * lines[i][0].position.x;
			float p = landerPos.y / (landerPos.x * k + b);
			if (p > 0.999) return true;
		}
	}
	return false;
}

bool Terrain::isLanded(Vector2f landerPos) {
	for (int i = 0; i < platforms.size(); i++) {
		if (platforms[i]->isLanded(landerPos)) {
			lastMultiplier = platforms[i]->getMultiplier();
			return true;
		}
	}
	return false;
}

bool Terrain::isLandedSuccessfully(Vector speed) {
	return fabsf(speed.x) < MAX_LANDING_SPEED_X && fabsf(speed.y) < MAX_LANDING_SPEED_Y;
}

int Terrain::getLastMultiplier() {
	return lastMultiplier;
}
