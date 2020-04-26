#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Renderable {
public:
	virtual void render() = 0;
};

