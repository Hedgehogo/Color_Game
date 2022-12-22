#include "fullColor.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
    FullColor::FullColor(sf::Color color, sf::Vector2f normalSize) : OnlyDrawable(), rectangle(), normalSize(normalSize) {
        rectangle.setFillColor(color);
    }
	
	void FullColor::setColor(sf::Color color) {
		rectangle.setFillColor(color);
	}
	
    void FullColor::draw() {
        renderTarget->draw(rectangle);
    }
	
    void FullColor::resize(sf::Vector2f size, sf::Vector2f position) {
        rectangle.setSize(size);
        rectangle.setPosition(position);
    }
	
	sf::Vector2f FullColor::getAreaPosition() {
		return rectangle.getPosition();
	}
	
	sf::Vector2f FullColor::getAreaSize() {
		return rectangle.getSize();
	}
	
    sf::Vector2f FullColor::getMinSize() {
        return sf::Vector2f();
    }
	
	sf::Vector2f FullColor::getNormalSize(){
		return normalSize;
	}
	
	FullColor *FullColor::copy() {
		FullColor* fullColor {new FullColor{rectangle.getFillColor(), normalSize}};
		OnlyDrawable::copy(fullColor);
		return fullColor;
	}
	
	bool convertPointer(const YAML::Node &node, FullColor *&fullColor) {
		if(node.IsScalar()) {
			fullColor = new FullColor{node.as<sf::Color>(), {}};
		} else {
			fullColor = new FullColor{node["color"].as<sf::Color>(), convDef(node["normal-size"], sf::Vector2f{})};
		}
		return true;
	}
	
	template<>
	bool determine<FullColor>(const YAML::Node &node) {
		if(node.IsScalar()) {
			return node.as<std::string>().size() <= 11;
		} else {
			return determine(node, {{"color", YAML::NodeType::Scalar}}, {{"normal-size"}});
		}
	}
}