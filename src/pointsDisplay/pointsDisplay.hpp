#pragma once
#include "../time/time.hpp"
#include "../../lib/ui/UI.hpp"

namespace cg {
	class PointsDisplay : public ui::IScalable, public ui::Layout {
	private:
		ui::IUninteractive* background;
		ui::Caption pointsText;
		ui::Caption timeText;
		ui::PSuint points;
		PSTime time;
		
		void setTime(sf::Time value);
		
		void setPoints(uint value);
	
	public:
		PointsDisplay(ui::PSuint points, PSTime time, ui::IUninteractive *background, sf::Font &font, int fontSize = ui::Caption::getDefaultSize(), sf::Color color = ui::Caption::getDefaultColor(),
					  sf::Text::Style style = {}, ui::InternalPositioning2 internalPositioning2 = {{0, 0}});
		
		void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
	private:
		PointsDisplay(ui::PSuint points, PSTime time, ui::Caption pointsText, ui::Caption timeText, ui::IUninteractive* background);
		
	public:
		PointsDisplay *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, PointsDisplay *&pointsDisplay);
}
