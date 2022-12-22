#include "cellsImpl.hpp"

namespace cg {
	CellsImpl::CellsImpl(sf::Vector2u count, ui::OnlyDrawable *first, ui::OnlyDrawable *second, ui::IUninteractive *background) :
		ui::LayoutWithBackground(background), first(first), second(second), count(count), currentCell() {}
	
	void CellsImpl::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
		ui::LayoutWithBackground::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		first->init(renderTarget, this->drawManager, updateManager, interactionManager, interactionStack, panelManager);
		second->init(renderTarget, this->drawManager, updateManager, interactionManager, interactionStack, panelManager);
		drawManager.add(*this);
	}
	
	void CellsImpl::setCount(sf::Vector2u count) {
		if(this->count != count) {
			this->count = count;
			resetCurrentCell();
		}
	}
	
	void CellsImpl::resetCurrentCell() {
		currentCell = {static_cast<uint>(rand()) % count.x, static_cast<uint>(rand()) % count.y};
	}
	
	sf::Vector2u CellsImpl::getCount() {
		return count;
	}
	
	ui::OnlyDrawable *CellsImpl::getFirst() {
		return first;
	}
	
	ui::OnlyDrawable *CellsImpl::getSecond() {
		return second;
	}
	
	ui::IUninteractive *CellsImpl::getBackground() {
		return background;
	}
	
	sf::Vector2u CellsImpl::getCurrentCell() {
		return currentCell;
	}
	
	sf::Vector2i CellsImpl::getCurrentCell(sf::Vector2f currentPosition) {
		if(currentPosition.x > position.x && currentPosition.x < position.x + size.x &&
		   currentPosition.y > position.y && currentPosition.y < position.y + size.y) {
			return {static_cast<int>((currentPosition.x - position.x) * static_cast<float>(count.x) / size.x),
					static_cast<int>((currentPosition.y - position.y) * static_cast<float>(count.y) / size.y)};
		} else {
			return sf::Vector2i{-1, -1};
		}
	}
	
	bool CellsImpl::onCurrentCell(sf::Vector2f currentPosition) {
		sf::Vector2i cell{getCurrentCell(currentPosition)};
		if(cell != sf::Vector2i{-1, -1}) {
			return sf::Vector2u{cell} == getCurrentCell();
		}
		return false;
	}
	
	void CellsImpl::draw() {
		sf::Vector2f cellSize{size / sf::Vector2f{count}};
		first->setSize(cellSize);
		second->setSize(cellSize);
		
		sf::Vector2f currentPosition{position};
		for(uint y = 0; y < count.y; ++y) {
			for(uint x = 0; x < count.x; ++x) {
				if(((x + y) % 2 == 0) != (x == currentCell.x && y == currentCell.y)) {
					first->setPosition(currentPosition);
					first->draw();
				} else {
					second->setPosition(currentPosition);
					second->draw();
				}
				currentPosition.x += cellSize.x;
			}
			currentPosition.x = position.x;
			currentPosition.y += cellSize.y;
		}
	}
	
	sf::Vector2f CellsImpl::getMinSize() {
		return ui::LayoutWithBackground::getMinSize();
	}
	
	sf::Vector2f CellsImpl::getNormalSize() {
		return ui::LayoutWithBackground::getNormalSize();
	}
	
	CellsImpl *CellsImpl::copy() {
		CellsImpl *cellsImpl{new CellsImpl{count, first->copy(), second->copy(), background->copy()}};
		ui::Layout::copy(cellsImpl);
		return cellsImpl;
	}
	
	void CellsImpl::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		ui::LayoutWithBackground::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	CellsImpl::~CellsImpl() {
		delete first;
		delete second;
	}
	
	bool convertPointer(const YAML::Node &node, CellsImpl *&cellsImpl) {
		cellsImpl = new CellsImpl{
			node["count"].as<sf::Vector2u>(),
			node["first"].as<ui::OnlyDrawable *>(),
			node["second"].as<ui::OnlyDrawable *>(),
			node["background"].as<ui::IUninteractive *>()
		};
		return true;
	}
}