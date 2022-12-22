#pragma once
#include "../../../../layout/layout.hpp"
#include "../onlyDrawable/onlyDrawable.hpp"
#include "../../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"
#include "../../../../../sizingAndPositioning/positioning2/internal/internalPositioning2.hpp"

namespace ui {
	class Caption : public OnlyDrawable, public Layout {
	protected:
		static sf::Color defaultColor;
		static int defaultSize;

        bool cutBack;
		
		sf::Text text;
		sf::String str;
		IUninteractive* background;
		sf::Vector2f minimumSize;
		DrawManager drawManager;
        InternalPositioning2 internalPositioning2;
		
		void setText(sf::FloatRect& bounds);
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
		
		static void setDefaultColor(sf::Color color = sf::Color::White);
		
		static void setDefaultSize(int size);
		
		static sf::Color getDefaultColor();
		
		static int getDefaultSize();
		
		Caption(sf::String text, IUninteractive *background, sf::Font &font, sf::Vector2f minSize, int fontSize = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0,
                InternalPositioning2 internalPositioning2 = {{0, 0}}, bool cutBack = true);
		
		Caption(sf::String text, IUninteractive *background, sf::Font &font, int fontSize = defaultSize, sf::Color color = defaultColor, sf::Text::Style style = {}, float rotation = 0,
                InternalPositioning2 internalPositioning2 = {{0, 0}}, bool cutBack = true);
		
		void setText(sf::String newStr);
		
		void draw() override;

    protected:
        sf::FloatRect getBounds();
		
    public:
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
	protected:
		Caption(sf::Text text, IUninteractive *background, sf::String str, sf::Vector2f minimumSize, InternalPositioning2 internalPositioning2, bool cutBack);
		
	public:
		Caption* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, Caption *&caption);
}