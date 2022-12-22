#include "startEvent.hpp"
#include "../game/game.hpp"

namespace cg {
	StartEvent::StartEvent() : game(nullptr) {}
	
	void StartEvent::setGame(Game &game) {
		this->game = &game;
	}
	
	void StartEvent::startPressed() {}
	
	void StartEvent::stopPressed() {
		game->restart();
	}
	
	void StartEvent::whilePressed() {}
	
	void StartEvent::whileNotPressed() {}
	
	StartEvent *StartEvent::copy() {
		return new StartEvent{};
	}
}