#include "pointsDisplay.hpp"
#include <utility>
#include <iostream>

namespace cg {
	PointsDisplay::PointsDisplay(ui::PSuint points, PSTime time, ui::IUninteractive *background, sf::Font &font, int fontSize, sf::Color color, sf::Text::Style style, ui::InternalPositioning2 internalPositioning2) :
		pointsText(sf::String("score: 0"), new ui::Empty{}, font, {10, 10}, fontSize, color, style, 0, internalPositioning2, false),
		timeText(sf::String("time: 0:0:0"), new ui::Empty{}, font, {10, 10}, fontSize, color, style, 0, internalPositioning2, false),
		points(std::move(points)), time(std::move(time)), background(background) {
		this->points->addSetter([this](uint value){ setPoints(value); });
		this->time->addSetter([this](sf::Time value){ setTime(value); });
	}
	
	void PointsDisplay::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
		background->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		pointsText.init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		timeText.init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	void PointsDisplay::setTime(sf::Time value) {
		uint milliseconds{static_cast<uint>(value.asMilliseconds()) % 1000};
		uint seconds{static_cast<uint>(value.asSeconds())};
		uint minutes{seconds / 60};
		seconds -= minutes * 60;
		
		std::string str{std::string("time: ") + std::to_string(minutes) + std::string(":") + std::to_string(seconds) + std::string(":") + std::to_string(milliseconds)};
		timeText.setText(sf::String(str));
	}
	
	void PointsDisplay::setPoints(uint value) {
		pointsText.setText(std::string("points: ") + std::to_string(value));
	}
	
	void PointsDisplay::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		sf::Vector2f textSize{size.x, size.y / 2};
		pointsText.resize(textSize, position);
		timeText.resize(textSize, {position.x, position.y + textSize.y});
		background->resize(size, position);
	}
	
	bool PointsDisplay::updateInteractions(sf::Vector2f mousePosition) {
		return false;
	}
	
	sf::Vector2f PointsDisplay::getMinSize() {
		return {0, 0};
	}
	
	sf::Vector2f PointsDisplay::getNormalSize() {
		return {0, 0};
	}
	
	PointsDisplay::PointsDisplay(ui::PSuint points, PSTime time, ui::Caption pointsText, ui::Caption timeText, ui::IUninteractive *background) :
		points(std::move(points)), time(std::move(time)), pointsText(pointsText), timeText(timeText), background(background) {}
	
	PointsDisplay *PointsDisplay::copy() {
		PointsDisplay* pointsDisplay{new PointsDisplay{points, time, pointsText, timeText, background->copy()}};
		Layout::copy(pointsDisplay);
		return pointsDisplay;
	}
	
	void PointsDisplay::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	bool convertPointer(const YAML::Node &node, PointsDisplay *&pointsDisplay) {
		pointsDisplay = new PointsDisplay{
			ui::Buffer::get<ui::Suint>(node["points"]),
			ui::Buffer::get<STime>(node["time"]),
			node["background"].as<ui::IUninteractive *>(),
			*node["font"].as<sf::Font *>(),
			ui::convDef(node["font-size"], ui::Caption::getDefaultSize()),
			ui::convDef(node["color"], ui::Caption::getDefaultColor()),
			ui::convDef(node["style"], sf::Text::Style::Regular),
			ui::InternalPositioning2{ui::convDef(node["coefficient"], sf::Vector2f{})}
		};
		return true;
	}
}