#pragma once
#include "../../lib/ui/UI.hpp"

namespace cg {
	class Game;
	
	class StartEvent : public ui::KeyEvent_Simple {
	private:
		Game* game;
		
	public:
		StartEvent();
		
		void setGame(Game& game);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		StartEvent* copy() override;
	};
}