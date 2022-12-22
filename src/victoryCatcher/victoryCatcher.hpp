#pragma once
#include "../gameCustomizer/gameCustomizer.hpp"

namespace cg {
	class VictoryCatcher : public ui::IScalable, public ui::Layout, public ui::IUpdatable, public ui::DrawManager {
	private:
		ui::DrawManager drawManager;
		ui::IScalable* game;
		ui::IScalable* victoryMenu;
		ui::PSbool pause;
		ui::PSbool timeLimit;
		ui::PSRfloat limit;
		ui::PSuint points;
		PSTime time;
		bool victory;
		
	public:
		VictoryCatcher(ui::PSbool pause, ui::PSbool timeLimit, ui::PSRfloat limit, ui::PSuint points, PSTime time, ui::IScalable* game, ui::IScalable* victoryMenu);
		
		void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		VictoryCatcher *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, VictoryCatcher *&victoryCatcher);
}
