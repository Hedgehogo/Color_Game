#pragma once
#include "../gameCustomizer/gameCustomizer.hpp"
#include "../pointsDisplay/pointsDisplay.hpp"
#include "../victoryCatcher/victoryCatcher.hpp"
#include "../constCenter/layerWithConstCenter.hpp"
#include "../startEvent/startEvent.hpp"

namespace cg {
	class Program {
	private:
		sf::RenderWindow window;
		sf::View view;
		ui::Interface interface;
		bool debug;
		
	public:
		Program(sf::VideoMode mode, const sf::String& title, const std::string &filePath, bool debug = false);
		
		void run();
	};
}
