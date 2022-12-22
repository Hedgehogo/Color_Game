#include "cells.hpp"

namespace cg {
	Cells::Cells(uint scale, ui::OnlyDrawable *first, ui::OnlyDrawable *second, ui::IUninteractive *background) :
		LayoutWithBackground(background), cellsImpl({2, 2}, first, second, new ui::Empty{}), scale(scale) {}
	
	void Cells::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
		LayoutWithBackground::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		cellsImpl.init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	void Cells::resetCurrentCell() {
		cellsImpl.resetCurrentCell();
	}
	
	void Cells::setScale(uint scale) {
		this->scale = scale;
		resize(size, position);
	}
	
	uint Cells::getScale() {
		return scale;
	}
	
	sf::Vector2u Cells::getCount() {
		return cellsImpl.getCount();
	}
	
	ui::OnlyDrawable *Cells::getFirst() {
		return cellsImpl.getFirst();
	}
	
	ui::OnlyDrawable *Cells::getSecond() {
		return cellsImpl.getSecond();
	}
	
	ui::IUninteractive *Cells::getBackground() {
		return background;
	}
	
	bool Cells::onCurrentCell(sf::Vector2f currentPosition) {
		return cellsImpl.onCurrentCell(currentPosition);
	}
	
	void Cells::resize(sf::Vector2f size, sf::Vector2f position) {
		float ratio{size.x / size.y};
		uint area{scale * scale};
		float xf{sqrtf(static_cast<float>(area) * ratio)};
		sf::Vector2u count{static_cast<uint>(std::roundf(xf)), static_cast<uint>(std::roundf(xf / ratio))};
		float cellsRatio{static_cast<float>(count.x) / static_cast<float>(count.y)};
		
		sf::Vector2f cellsSize{size};
		sf::Vector2f cellsPosition{position};
		if(ratio > cellsRatio) {
			cellsSize.x = size.y * cellsRatio;
			cellsPosition.x = position.x + (size.x - cellsSize.x) / 2.f;
		} else {
			cellsSize.y = size.x / cellsRatio;
			cellsPosition.y = position.y + (size.y - cellsSize.y) / 2.f;
		}
		
		cellsImpl.setCount(count);
		cellsImpl.resize(cellsSize, cellsPosition);
		LayoutWithBackground::resize(size, position);
	}
	
	sf::Vector2f Cells::getMinSize() {
		return ui::max(background->getMinSize(), cellsImpl.getMinSize());
	}
	
	sf::Vector2f Cells::getNormalSize() {
		return ui::max(background->getNormalSize(), cellsImpl.getNormalSize());
	}
	
	Cells *Cells::copy() {
		Cells *cells{new Cells{scale, getFirst()->copy(), getSecond()->copy(), background->copy()}};
		Layout::copy(cells);
		return cells;
	}
	
	void Cells::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue, hueOffset);
		cellsImpl.drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, Cells *&cells) {
		cells = new Cells{
			node["scale"].as<uint>(),
			node["first"].as<ui::OnlyDrawable *>(),
			node["second"].as<ui::OnlyDrawable *>(),
			node["background"].as<ui::IUninteractive *>()
		};
		return true;
	}
}