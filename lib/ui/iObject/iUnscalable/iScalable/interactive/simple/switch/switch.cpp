#include "switch.hpp"
#include "../../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"
#include "event/switchEvent.hpp"

namespace ui {
    Switch::Switch(ui::PSbool active, IUninteractive *inactiveBackground, IUninteractive *activeBackground, Key key) :
		Interactive_Simple(new OneKeyInteraction{new SwitchEvent{*this}, key}), activeBackground(activeBackground), inactiveBackground(inactiveBackground), active(active){}

    void Switch::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) {
		Interactive_Simple::init(renderTarget, drawManager, updateManager, panelManager);
        drawManager.add(*this);
		activeBackground->init(renderTarget, activeDrawManager, updateManager, *interactionManager, *interactionStack, panelManager);
		inactiveBackground->init(renderTarget, inactiveDrawManager, updateManager, *interactionManager, *interactionStack, panelManager);
    }

    void Switch::switchValue() {
        active->setValue(!active->getValue());
    }

    void Switch::setPosition(sf::Vector2f position) {
        Layout::setPosition(position);
        activeBackground->setPosition(position);
        inactiveBackground->setPosition(position);
    }

    void Switch::move(sf::Vector2f position) {
        Layout::move(position);
        activeBackground->move(position);
        inactiveBackground->move(position);
    }

    void Switch::setSize(sf::Vector2f size) {
        Layout::setSize(size);
        activeBackground->setSize(size);
        inactiveBackground->setSize(size);
    }

    sf::Vector2f Switch::getMinSize() {
        return max(activeBackground->getMinSize(), inactiveBackground->getMinSize());
    }

    sf::Vector2f Switch::getNormalSize() {
        return max(activeBackground->getNormalSize(), inactiveBackground->getNormalSize());
    }
    void Switch::draw() {
        if(active->getValue())
            activeDrawManager.draw();
        else
            inactiveDrawManager.draw();
    }

    void Switch::resize(sf::Vector2f size, sf::Vector2f position) {
        Layout::resize(size, position);
        activeBackground->resize(size, position);
        inactiveBackground->resize(size, position);
    }

    Switch *Switch::copy() {
        Switch* switcher{new Switch(active, inactiveBackground->copy(), activeBackground->copy(), dynamic_cast<OneKeyInteraction*>(interaction)->getKey())};
        Layout::copy(switcher);
        return switcher;
    }
	
	bool convertPointer(const YAML::Node &node, Switch *&switcher) {
		IUninteractive *inactiveBackground;
		IUninteractive *activeBackground;
		Key key{Key::mouseLeft};
		
		node["inactive-background"] >> inactiveBackground;
		node["active-background"] >> activeBackground;
		if(node["key"]) node["key"] >> key;
		
		switcher = new Switch{
			ui::Buffer::get<ui::Sbool>(node["value"]),
			inactiveBackground,
			activeBackground,
			key
		};
		return true;
	}

    void Switch::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        if(active->getValue()) {
			activeBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		} else {
			inactiveBackground->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		}
    }

    Switch::~Switch() {
        delete activeBackground;
        delete inactiveBackground;
    }
}