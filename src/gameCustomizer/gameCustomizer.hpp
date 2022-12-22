#pragma once
#include "../game/game.hpp"

namespace cg {
	class GameCustomizer : public ui::IScalable, public ui::Layout {
	public:
		Game game;
		
	private:
		ui::PSRfloat scale;
		ui::PSRfloat hue;
		
		void setScale(float scale);
		
		void setHue(float hue);
		
	public:
		GameCustomizer(ui::PSRfloat scale, ui::PSRfloat hue, ui::PSbool pause, ui::PSuint points, PSTime time, ui::IUninteractive *background, ui::Key key = ui::Key::mouseLeft);
		
		void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		GameCustomizer *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, GameCustomizer *&gameCustomizer);
}
