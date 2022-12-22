#pragma once
#include "../../../lib/ui/UI.hpp"

namespace cg {
	class Game;
	class GameEvent : public ui::KeyEvent_Simple {
	private:
		Game* game;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
	public:
		GameEvent(Game& game);
		
		void setGame(Game& game);
		
		GameEvent* copy() override;
	};
}
