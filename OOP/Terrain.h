#pragma once
#include "Renderable.h"
#include "Configuration.h"
#include "Vector.h"
#include "Platform.h"

using namespace sf;
using namespace std;

class Terrain : public Renderable {
private:
	const int MAX_LINE_WIDTH = 130; 
	const int MAX_LINE_HEIGHT = 300;
	const int MIN_LINE_HEIGHT = 100;
	float MAX_LANDING_SPEED_X;
	float MAX_LANDING_SPEED_Y;

	int lastMultiplier;

	RenderWindow* window;
	Configuration* cfg;
	vector<VertexArray> lines;
	vector<Platform*> platforms;
public:
	Terrain(RenderWindow*, Configuration*);
	~Terrain();
	void update(Vector, Vector2f);
	void render();
	bool isCrushed(Vector2f);
	bool isLanded(Vector2f);
	bool isLandedSuccessfully(Vector);
	int getLastMultiplier();
};

