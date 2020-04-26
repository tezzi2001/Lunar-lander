#include "Dispatcher.h"
#include <Windows.h>

Dispatcher::Dispatcher(Configuration* cfg, RenderWindow& window) {
	this->cfg = cfg;
	this->menu = new Menu(&window, cfg);
	this->about = new About(&window, cfg);
	this->game = new Game(&window, cfg, 0);
	this->window = &window;
	this->theme = new Music();
	if(!this->theme->openFromFile(cfg->getSpaceMusicPath())) cout << "Error loading space music" << endl;
	if (!this->explosionBuffer.loadFromFile(cfg->getExplosionSoundPath())) cout << "Error loading explosion sound" << endl;
	this->theme->setLoop(true);
	this->theme->setVolume(cfg->getMusicVolume());
	this->explosion.setBuffer(explosionBuffer);
	this->explosion.setVolume(cfg->getSoundsVolume());
	this->theme->play();
	context = MENU;
}

Dispatcher::~Dispatcher() {
	if (theme) delete theme;
	if (menu) delete menu;
	if (about) delete about;
	if (game) delete game;
}

void Dispatcher::changeContext(int context) {
	this->context = context >= 0 && context <= 3 ? context : this->context;
}

/*
	It`s neccessary to provide RenderWindow instance to this method.
	It`s imposible to store an instance of RenderWindow(operator = is not defined in RenderWindow).
	Also methods can`t be invoke form pointer to RenderWindow via '->' operator.
	Otherwise there will be thrown an exeption when methods from RenderWindow invoke.
	Can`t be fixed under any circumstances
*/
void Dispatcher::start(RenderWindow& window) { 
	Vector2i mousePos = Mouse::getPosition();

	while (window.isOpen()) {
		Event event;

		window.clear();
		while (window.pollEvent(event)) {
			switch (event.type) {
				case Event::MouseButtonPressed: {
					onMouseClick();
					break;
				}
				case Event::KeyPressed: {
					onKeyPressed();
					break;
				}
				case Event::Closed: {
					window.close();
				}
			}
		}
		render();
		window.display();
	}
}

void Dispatcher::onMouseClick() {
	switch (context) {
		case MENU: {
			context = menu->getContextByButtonPressed(Mouse::getPosition());
			break;
		}
		case ABOUT: {
			if (about->isBackButtonPressed(Mouse::getPosition())) context = MENU;
			break;
		}
	}
}

void Dispatcher::onKeyPressed() {
	switch (context) {
		case GAME: {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) context = MENU;
			if (Keyboard::isKeyPressed(Keyboard::LShift)) game->lander->increaseThrust();
			if (Keyboard::isKeyPressed(Keyboard::LControl)) game->lander->decreaseThrust();
			if (Keyboard::isKeyPressed(Keyboard::Up)) game->lander->rotatePositive();
			if (Keyboard::isKeyPressed(Keyboard::Down)) game->lander->rotateNegative();
			if (Keyboard::isKeyPressed(Keyboard::X)) game->lander->offThrust();
			break;
		}
		case ABOUT: {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) context = MENU;
		}
	}
}

void Dispatcher::render() {
	switch (context) {
		case MENU: {
			game->lander->notifyOnEnd();
			menu->render();
			break;
		}
		case GAME: {
			if (game->isComplete()) {
				game->lander->notifyOnEnd();
				float score = game->getScore();

				game->getLevelCompleteMsg()->render();
				window->display();
				Sleep(4000);

				delete game;
				game = new Game(window, cfg, score);
			} else if (game->isOver()) {
				explosion.play();
				theme->setVolume(theme->getVolume()-30); 

				game->lander->notifyOnEnd();
				context = MENU;

				game->getGameOverMsg()->render();
				window->display();
				while (explosion.getStatus() == explosion.Playing) {} //wait till crash sound has played

				delete game;
				game = new Game(window, cfg, 0);
				explosion.stop();
				theme->setVolume(theme->getVolume() + 30);
			}
			game->render();
			break;
		}
		case ABOUT: {
			about->render();
			break;
		}
		case EXIT: {
			cout << "exit" << endl;
			exit(0);
		}
	}
}