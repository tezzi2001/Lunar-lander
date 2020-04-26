#pragma once
#include "Lander.h"
#include "RenderText.h"
#include "Terrain.h"

extern vector<Text*> textGarbage;
extern vector<Font*> fontGarbage;

class Game : public Renderable {
private:
	bool landed;
	float score;
	Terrain* terrain;
	RenderText* levelCompleteMsg;
	RenderText* gameOverMsg;
	RenderText* landerInfo;
public:
	Lander* lander;

	Game(RenderWindow*, Configuration*, float);
	~Game();
	void render();
	bool isOver();
	bool isComplete();
	float getScore();
	RenderText* getLevelCompleteMsg();
	RenderText* getGameOverMsg();
};

