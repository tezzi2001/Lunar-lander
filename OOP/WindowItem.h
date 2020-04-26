#pragma once
#include <string>
#include "Renderable.h"

using namespace std;
using namespace sf;

class WindowItem : public Renderable {
protected:
    RenderWindow* window;
public:
    Texture texture;
    Sprite sprite;
 
    WindowItem(string, RenderWindow*);
    virtual void render();
};

