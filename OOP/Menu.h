#pragma once
#include <string>
#include "WindowItem.h"
#include "Button.h"
#include "Configuration.h"

using namespace std;
using namespace sf;

class Menu : public WindowItem {
private:
    Configuration* cfg;
    vector<Button*> buttons;
public:
    Menu(RenderWindow*, Configuration*);
    ~Menu();
    void render();
    int getContextByButtonPressed(Vector2i);
};

