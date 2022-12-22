#pragma once
#include "../../lib/ui/UI.hpp"

namespace cg {
	class CellsImpl : public ui::IUninteractive, public ui::LayoutWithBackground, public ui::IDrawable {
	private:
		sf::Vector2u count;
		ui::OnlyDrawable *first;
		ui::OnlyDrawable *second;
		ui::DrawManager drawManager;
		sf::Vector2u currentCell;
		
	public:
		CellsImpl(sf::Vector2u count, ui::OnlyDrawable *first, ui::OnlyDrawable *second, ui::IUninteractive *background);
		
		void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) override;
		
		void setCount(sf::Vector2u count);
		
		void resetCurrentCell();
	
		sf::Vector2u getCount();
		
		ui::OnlyDrawable *getFirst();
	
		ui::OnlyDrawable *getSecond();
	
		ui::IUninteractive *getBackground();
		
		sf::Vector2u getCurrentCell();
		
		sf::Vector2i getCurrentCell(sf::Vector2f currentPosition);
		
		bool onCurrentCell(sf::Vector2f currentPosition);
		
		void draw() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		CellsImpl *copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
		~CellsImpl() override;
	};
	
	bool convertPointer(const YAML::Node &node, CellsImpl *&cellsImpl);
}
