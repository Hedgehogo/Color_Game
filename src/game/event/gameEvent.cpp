#include "gameEvent.hpp"
#include "../game.hpp"

namespace cg {
	GameEvent::GameEvent(Game &game) : game(&game) {}
	
	void GameEvent::startPressed() {}
	
	void GameEvent::stopPressed() {
		if(game->onCurrentCell(sf::Vector2f(mousePosition))) {
			game->resetCurrentCell();
			game->addPoint();
		}
	}
	
	void GameEvent::whilePressed() {}
	
	void GameEvent::whileNotPressed() {}
	
	void GameEvent::setGame(Game &game) {
		this->game = &game;
	}
	
	GameEvent *GameEvent::copy() {
		return new GameEvent{*game};
	}
}