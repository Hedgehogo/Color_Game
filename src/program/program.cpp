#include "program.hpp"

namespace cg {
	Program::Program(sf::VideoMode mode, const sf::String &title, const std::string &filePath, bool debug) :
		window(mode, title), view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize())),
		interface(window, filePath, new ui::InteractionStack{{new ui::OneKeyInteraction{new StartEvent{}, ui::Key::mouseLeft}}}), debug(debug) {
		window.setFramerateLimit(60);
		interface.setRenderWindowSize(window);
	}
	
	void Program::run() {
		while(window.isOpen()) {
			sf::Event event{};
			while(window.pollEvent(event)) {
				ui::handleEvent(event);
				
				if(event.type == sf::Event::Closed) {
					window.close();
				}
				
				if(event.type == sf::Event::Resized) {
					sf::Vector2f minSize = interface.getMinSize();
					sf::Vector2f windowSize{static_cast<float>(event.size.width), static_cast<float>(event.size.height)};
					if(windowSize.x < minSize.x || windowSize.y < minSize.y) {
						windowSize = ui::max(windowSize, minSize);
						window.setSize(sf::Vector2u{windowSize});
					}
					view.reset({{}, windowSize});
					window.setView(view);
					interface.setSize(windowSize);
				}
			}
			interface.setSize(sf::Vector2f{window.getSize()});
			window.clear();
			interface.update(sf::Vector2f{(sf::Mouse::getPosition(window))}, window.getSystemHandle());
			interface.draw();
			if(debug) interface.drawDebug(window, 0, 2, 90, 90);
			window.display();
			ui::clearEvent();
		}
	}
}