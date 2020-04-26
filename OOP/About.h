#pragma once
#include "WindowItem.h"
#include <string>
#include "WindowItem.h"
#include "RenderText.h"
#include "Configuration.h"
#include "Button.h"

using namespace std;

extern vector<Text*> textGarbage;
extern vector<Font*> fontGarbage;

class About : public WindowItem {
private:
	RenderText* description;
	RenderText* controls;
	Button* buttonBack;
	string getControls(string);
public:
	About(RenderWindow*, Configuration*);
	~About();
	bool isBackButtonPressed(Vector2i);
	void render();
};

