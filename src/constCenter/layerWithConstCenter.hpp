#pragma once

#include "../../lib/ui/UI.hpp"

namespace cg {
	class LayerWithConstCenter : public ui::Layer, public ui::LayoutWithObject {
	protected:
		sf::Vector2f objectSize;
	
	public:
		void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) override;

		LayerWithConstCenter(IScalable *object, sf::Vector2f objectSize, sf::Vector2f minSize = {});

		void setAspectRatio(sf::Vector2f objectSize);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstCenter* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithConstCenter *&layerWithConstCenter);
	
	typedef LayerWithConstCenter LayerWCCenter;
	typedef LayerWithConstCenter LWCC;
}
