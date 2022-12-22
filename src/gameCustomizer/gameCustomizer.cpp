#include "gameCustomizer.hpp"

#include <utility>

namespace cg {
	GameCustomizer::GameCustomizer(ui::PSRfloat scale, ui::PSRfloat hue, ui::PSbool pause, ui::PSuint points, PSTime time, ui::IUninteractive *background, ui::Key key) :
		game(static_cast<uint>(scale->getValue() * 90) + 10, static_cast<uint>(hue->getValue() * 360), std::move(pause), std::move(points),  std::move(time), background, key), hue(hue), scale(scale) {
		scale->setBounds(0, 1);
		scale->addSetter([this](float value) { setScale(value); });
		hue->setBounds(0, 1);
		hue->addSetter([this](float value){ setHue(value); });
	}
	
	void GameCustomizer::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
		dynamic_cast<ui::IScalable*>(&game)->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	void GameCustomizer::setScale(float value) {
		game.setScale(static_cast<uint>(value * 90) + 10);
	}
	
	void GameCustomizer::setHue(float value) {
		game.setHue(static_cast<uint>(value * 360));
	}
	
	void GameCustomizer::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		game.resize(size, position);
	}
	
	bool GameCustomizer::updateInteractions(sf::Vector2f mousePosition) {
		return game.updateInteractions(mousePosition);
	}
	
	sf::Vector2f GameCustomizer::getMinSize() {
		return game.getMinSize();
	}
	
	sf::Vector2f GameCustomizer::getNormalSize() {
		return game.getNormalSize();
	}
	
	GameCustomizer *GameCustomizer::copy() {
		GameCustomizer* gameCustomizer{new GameCustomizer{scale, hue, ui::PSbool{}, ui::PSuint{}, cg::PSTime{}, game.getBackground(), game.getKey()}};
		Layout::copy(gameCustomizer);
		return gameCustomizer;
	}
	
	void GameCustomizer::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		game.drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, GameCustomizer *&gameCustomizer) {
		gameCustomizer = new GameCustomizer{
			ui::Buffer::get<ui::SRfloat>(node["scale"]),
			ui::Buffer::get<ui::SRfloat>(node["hue"]),
			ui::Buffer::get<ui::Sbool>(node["pause"]),
			ui::Buffer::get<ui::Suint>(node["points"]),
			ui::Buffer::get<STime>(node["time"]),
			node["background"].as<ui::IUninteractive *>(),
			ui::convDef(node["key"],
			ui::Key::mouseLeft)
		};
		return true;
	}
}