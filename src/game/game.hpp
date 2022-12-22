#pragma once
#include "../time/time.hpp"
#include "../cells/cells.hpp"

namespace cg {
	class Game : public ui::Interactive_Simple, public ui::Layout {
	private:
		Cells cells;
		sf::Vector2u currentCell;
		sf::Clock timer;
		PSTime time;
		ui::PSuint points;
		ui::PSbool pause;
		uint hue;
		
		void setColor();
		
	public:
		Game(uint scale, uint hue, ui::PSbool pause, ui::PSuint points, PSTime time, ui::IUninteractive *background, ui::Key key = ui::Key::mouseLeft);
		
		void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::IPanelManager &panelManager) override;
		
		void setPause(bool pause);
		
		void setScale(uint scale);
		
		void setHue(uint hue);
	
		void moveHue(int offset);
	
		void addPoint();
		
		void resetPoints();
		
		void resetTimer();
		
		void resetCurrentCell();
		
		void restart();
		
		ui::Key getKey();
		
		sf::Time getTime();
		
		ui::IUninteractive *getBackground();
		
		bool onCurrentCell(sf::Vector2f currentPosition);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	
		Game *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, Game *&game);
}
