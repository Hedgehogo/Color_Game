#include "layerWithConstCenter.hpp"

namespace cg {
	void LayerWithConstCenter::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
		object->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	LayerWithConstCenter::LayerWithConstCenter(IScalable* object, sf::Vector2f objectSize, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObject(object), objectSize(objectSize) {}
	
	void LayerWithConstCenter::setAspectRatio(sf::Vector2f objectSize) {
		this->objectSize = objectSize;
		this->setPosition(position);
	}

	void LayerWithConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		
		object->resize(objectSize, position + (this->size - objectSize) / 2.0f);
	}
	
	bool LayerWithConstCenter::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		return true;
	}
	
	sf::Vector2f LayerWithConstCenter::getMinSize() {
		return ui::max(objectSize, minimumSize);
	}
	
	sf::Vector2f LayerWithConstCenter::getNormalSize() {
		return ui::max(objectSize, minimumSize);
	}
	
	LayerWithConstCenter *LayerWithConstCenter::copy() {
		LayerWithConstCenter* layerWithConstCenter{new LayerWithConstCenter{object->copy(), objectSize, minimumSize}};
		Layer::copy(layerWithConstCenter);
		return layerWithConstCenter;
	}
	
	bool convertPointer(const YAML::Node &node, LayerWithConstCenter *&layerWithConstCenter) {
		layerWithConstCenter = new LayerWithConstCenter{
			node["object"].as<ui::IScalable *>(),
			node["object-size"].as<sf::Vector2f>(),
			ui::convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
	
	void LayerWithConstCenter::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}
