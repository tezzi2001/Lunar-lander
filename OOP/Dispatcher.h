#pragma once
#include "SFML/Audio.hpp"
#include "Menu.h"
#include "About.h"
#include "Game.h"
#include "Configuration.h"

using namespace sf;

class Dispatcher : public Renderable {
private:
	int context;
	Configuration* cfg;
	Menu* menu;
	About* about;
	Game* game;
	RenderWindow* window;
	Music* theme;
	Sound explosion;
	SoundBuffer explosionBuffer;

	Dispatcher(Configuration*, RenderWindow&);
public:
	~Dispatcher();

	enum ContextTypes {
		MENU = 0,
		GAME = 1,
		ABOUT = 2,
		EXIT = 3
	};

	void onMouseClick();
	void onKeyPressed();
	void changeContext(int);
	void start(RenderWindow&);
	static Dispatcher& getInstance(Configuration* cfg, RenderWindow& window) {
		static Dispatcher instance(cfg, window);
		return instance;
	}

	void render();
};

