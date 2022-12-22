#include "victoryCatcher.hpp"
#include <utility>

namespace cg {
	VictoryCatcher::VictoryCatcher(ui::PSbool pause, ui::PSbool timeLimit, ui::PSRfloat limit, ui::PSuint points, PSTime time, ui::IScalable *game, ui::IScalable *victoryMenu) :
		timeLimit(std::move(timeLimit)), limit(std::move(limit)), points(std::move(points)), time(time), game(game), victoryMenu(victoryMenu), victory(false), pause(pause) {}
	
	void VictoryCatcher::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
		game->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		victoryMenu->init(renderTarget, this->drawManager, updateManager, interactionManager, interactionStack, panelManager);
		drawManager.add(*this);
		updateManager.add(*this);
	}
	
	void VictoryCatcher::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		game->resize(size, position);
		victoryMenu->resize(size, position);
	}
	
	void VictoryCatcher::draw() {
		if(pause->getValue()) {
			drawManager.draw();
		}
	}
	
	void VictoryCatcher::update() {
		if(timeLimit->getValue()) {
			sf::Time end{sf::seconds(limit->getValue() * 110.f + 10.f)};
			victory = time->getValue() > end;
		} else {
			uint maximum{static_cast<uint>(limit->getValue() * 90.f) + 10};
			victory = points->getValue() >= maximum;
		}
		if(victory) {
			pause->setValue(true);
		}
	}
	
	bool VictoryCatcher::updateInteractions(sf::Vector2f mousePosition) {
		if(pause->getValue()) {
			return victoryMenu->updateInteractions(mousePosition);
		} else {
			return game->updateInteractions(mousePosition);
		}
	}
	
	sf::Vector2f VictoryCatcher::getMinSize() {
		return ui::max(game->getMinSize(), victoryMenu->getMinSize());
	}
	
	sf::Vector2f VictoryCatcher::getNormalSize() {
		return ui::max(game->getNormalSize(), victoryMenu->getNormalSize());
	}
	
	VictoryCatcher *VictoryCatcher::copy() {
		VictoryCatcher* victoryCatcher{new VictoryCatcher{pause, timeLimit, limit, points, time, game->copy(), victoryMenu->copy()}};
		Layout::copy(victoryCatcher);
		return victoryCatcher;
	}
	
	void VictoryCatcher::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		game->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		victoryMenu->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, VictoryCatcher *&victoryCatcher) {
		victoryCatcher = new VictoryCatcher{
			ui::Buffer::get<ui::Sbool>(node["pause"]),
			ui::Buffer::get<ui::Sbool>(node["limit-type"]),
			ui::Buffer::get<ui::SRfloat>(node["limit"]),
			ui::Buffer::get<ui::Suint>(node["points"]),
			ui::Buffer::get<STime>(node["time"]),
			node["game"].as<ui::IScalable *>(),
			node["victory-menu"].as<ui::IScalable *>()
		};
		return true;
	}
}