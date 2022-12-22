#include "game.hpp"
#include <utility>
#include "event/gameEvent.hpp"
#include "../startEvent/startEvent.hpp"
#include "../../lib/modules/appendix/HSVtoRGB/HsVtoRgb.hpp"

namespace cg {
	Game::Game(uint scale, uint hue, ui::PSbool pause, ui::PSuint points, PSTime time, ui::IUninteractive *background, ui::Key key) :
		ui::Interactive_Simple(new ui::OneKeyInteraction{new GameEvent{*this}, key}),
		cells(scale, new ui::FullColor(ui::HSVtoRGB(hue)), new ui::FullColor(ui::HSVtoRGB((hue + 180) % 360)), background),
		hue(hue), points(std::move(points)), time(std::move(time)), timer(), pause(pause) {
		this->points->setValue(0);
		this->time->setValue(sf::microseconds(0));
		this->pause->setValue(false);
	}
	
	void Game::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::IPanelManager &panelManager) {
		Interactive_Simple::init(renderTarget, drawManager, updateManager, panelManager);
		cells.init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
		dynamic_cast<cg::StartEvent *>(dynamic_cast<ui::OneKeyInteraction *>(interactionStack->at(0))->getEvent())->setGame(*this);
	}
	
	void Game::setPause(bool pause) {
		this->pause->setValue(pause);
	}
	
	void Game::setScale(uint scale) {
		cells.setScale(scale);
	}
	
	void Game::setColor() {
		dynamic_cast<ui::FullColor*>(cells.getFirst())->setColor(ui::HSVtoRGB(hue));
		dynamic_cast<ui::FullColor*>(cells.getSecond())->setColor(ui::HSVtoRGB((hue + 180) % 360));
	}
	
	void Game::setHue(uint hue) {
		this->hue = hue % 360;
		setColor();
	}
	
	void Game::moveHue(int offset) {
		this->hue = ((hue + static_cast<uint>(offset % 360 + 360)) % 360);
		setColor();
	}
	
	void Game::addPoint() {
		points->setValue(points->getValue() + 1);
	}
	
	void Game::resetPoints() {
		points->setValue(0);
	}
	
	void Game::resetTimer() {
		time->setValue(sf::microseconds(0));
	}
	
	void Game::restart() {
		resetTimer();
		resetPoints();
		setPause(false);
	}
	
	ui::Key Game::getKey() {
		return dynamic_cast<ui::OneKeyInteraction*>(interaction)->getKey();
	}
	
	sf::Time Game::getTime() {
		return time->getValue();
	}
	
	ui::IUninteractive *Game::getBackground() {
		return cells.getBackground();
	}
	
	void Game::resetCurrentCell() {
		cells.resetCurrentCell();
	}
	
	bool Game::onCurrentCell(sf::Vector2f currentPosition) {
		return cells.onCurrentCell(currentPosition);
	}
	
	void Game::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		cells.resize(size, position);
	}
	
	void Game::update() {
		Interactive_Simple::update();
		if(!(pause->getValue())) {
			time->setValue(time->getValue() + timer.restart());
		} else {
			timer.restart();
		}
	}
	
	bool Game::updateInteractions(sf::Vector2f mousePosition) {
		return pause->getValue() || Interactive_Simple::updateInteractions(mousePosition);
	}
	
	sf::Vector2f Game::getMinSize() {
		return cells.getMinSize();
	}
	
	sf::Vector2f Game::getNormalSize() {
		return cells.getNormalSize();
	}
	
	Game *Game::copy() {
		Game* game{new Game{cells.getScale(), hue, pause, points, time, cells.getBackground()->copy(), getKey()}};
		Interactive_Simple::copy(game);
		Layout::copy(game);
		return game;
	}
	
	void Game::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, Game *&game) {
		game = new Game{
			node["scale"].as<uint>(),
			node["hue"].as<uint>(),
			ui::Buffer::get<ui::Sbool>(node["pause"]),
			ui::Buffer::get<ui::Suint>(node["points"]),
			ui::Buffer::get<STime>(node["time"]),
			node["background"].as<ui::IUninteractive *>(),
			ui::convDef(node["key"], ui::Key::mouseLeft)
		};
		return true;
	}
}