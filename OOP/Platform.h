#pragma once
#include "RenderText.h"
#include "Vector.h"

class Platform : public RenderText {
private:
	VertexArray square;
	Vector2f position;
	int multiplier;
public:
	Platform(Font*, Text*, RenderWindow*, int, Vector2f);
	void render();
	bool isLanded(Vector2f);
	void move(Vector);
	int getMultiplier();
};

