#pragma once
#include "../cellsImpl/cellsImpl.hpp"

namespace cg {
	class Cells : public ui::IUninteractive, public ui::LayoutWithBackground {
	private:
		CellsImpl cellsImpl;
		uint scale;
		
	public:
		Cells(uint scale, ui::OnlyDrawable *first, ui::OnlyDrawable *second, ui::IUninteractive *background);
		
		void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) override;
		
		void resetCurrentCell();
		
		void setScale(uint scale);
		
		uint getScale();
		
		sf::Vector2u getCount();
		
		ui::OnlyDrawable *getFirst();
		
		ui::OnlyDrawable *getSecond();
		
		ui::IUninteractive *getBackground();
		
		bool onCurrentCell(sf::Vector2f currentPosition);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Cells *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, Cells *&cells);
}
