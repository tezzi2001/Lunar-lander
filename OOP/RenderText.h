#pragma once
#include "Renderable.h"
#include <string>

using namespace std;

class RenderText : public Renderable {
protected:
	RenderWindow* window;
	Font* font;
	Text* text;
public:
	RenderText(Font*, Text*, RenderWindow*);
	virtual void render();
	void setString(string);
	void center();
};

