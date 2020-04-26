#include "Game.h"

Game::Game(RenderWindow* window, Configuration* cfg, float score) {
	this->lander = new Lander(window, cfg);
	this->terrain = new Terrain(window, cfg);
	this->landed = false;
	this->score = score;

	Font* font = new Font();
	font->loadFromFile(cfg->getFontPath());
	Text* levelCompleteText = new Text();
	levelCompleteText->setCharacterSize(200);
	levelCompleteText->setFont(*font);
	levelCompleteText->setString("LEVEL COMPLETE");
	levelCompleteText->setFillColor(Color::Green);
	this->levelCompleteMsg = new RenderText(font, levelCompleteText, window);
	Text* gameOverText = new Text();
	gameOverText->setCharacterSize(200);
	gameOverText->setFont(*font);
	gameOverText->setFillColor(Color::Red);
	this->gameOverMsg = new RenderText(font, gameOverText, window);
	Text* landerInfoText = new Text();
	landerInfoText->setCharacterSize(30);
	landerInfoText->setLineSpacing(1.2);
	landerInfoText->setFont(*font);
	this->landerInfo = new RenderText(font, landerInfoText, window);

	fontGarbage.push_back(font);
	textGarbage.push_back(levelCompleteText);
	textGarbage.push_back(gameOverText);
	textGarbage.push_back(landerInfoText);
}

Game::~Game() {
	if (lander) delete lander;
	if (terrain) delete terrain;
	if (gameOverMsg) delete gameOverMsg;
	if (levelCompleteMsg) delete levelCompleteMsg;
	if (landerInfo) delete landerInfo;
}

void Game::render() {
	lander->update();
	lander->render();
	terrain->update(lander->getSpeed(), lander->getPosition());
	landed = terrain->isLanded(lander->getPosition());
	terrain->render();

	string s = "";
	s.append("speed: ").append(to_string(lander->getSpeed().getModule())).append("\n");
	s.append("horzontal speed: ").append(to_string(lander->getSpeed().x)).append("\n");
	s.append("vertical speed: ").append(to_string(lander->getSpeed().y)).append("\n");
	s.append("thrust: ").append(to_string(lander->getThrust().getModule())).append("\n");
	s.append("fuel: ").append(to_string(lander->getFuel())).append("\n");
	landerInfo->setString(s);
	landerInfo->render();
}

bool Game::isOver() {
	if (landed) {
		if (!terrain->isLandedSuccessfully(lander->getSpeed())) {
			string s;
			s.append("GAME OVER\n").append("SCORE: ").append(to_string(score));
			gameOverMsg->setString(s);
			return true;
		}
		return false;
	}
	if (terrain->isCrushed(lander->getPosition())) {
		string s;
		s.append("GAME OVER\n").append("SCORE: ").append(to_string(score));
		gameOverMsg->setString(s);
		return true;
	}
	return false;
}

bool Game::isComplete() {
	if (landed) {
		if (terrain->isLandedSuccessfully(lander->getSpeed())) {
			score += lander->getFuel() * terrain->getLastMultiplier();
			return true;
		}
	}
	return false;
}

float Game::getScore() {
	return score;
}

RenderText* Game::getLevelCompleteMsg() {
	levelCompleteMsg->center();
	return levelCompleteMsg;
}

RenderText* Game::getGameOverMsg() {
	gameOverMsg->center();
	return gameOverMsg;
}