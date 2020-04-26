#pragma once
#include "WindowItem.h"
#include <string>
#include "RenderText.h"

using namespace std;
using namespace sf;

extern vector<Text*> textGarbage;
extern vector<Font*> fontGarbage;

class Button : public RenderText, public WindowItem {
public:
	Button(RenderWindow*, string, string, int, string);
	string getName();
	void render();
	bool contains(Vector2i);
};

