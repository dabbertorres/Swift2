#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Widget.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/Label.hpp"
#include "Widgets/Toggle.hpp"
#include "Widgets/TextBox.hpp"

namespace cstr
{
	class Window : public sf::Drawable
	{
		public:
			Window();
			~Window();
			
			void update(sf::Event& event);
			
			void setFont(sf::Font& font);
			
			Label& addLabel(const sf::Vector2i& pos, const std::string& str);
			Button& addButton(sf::IntRect rect, const sf::Texture& tex, const std::function<void()>& f);
			Toggle& addToggle(sf::IntRect rect, const sf::Texture& off, const sf::Texture& on, bool s);
			TextBox& addTextBox(sf::IntRect rect, const sf::Color& in, const sf::Color& out);
			
			Widget& getWidget(unsigned i);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			std::vector<Widget*> widgets;
			Widget* activeWidget;
			
			sf::Font* font;
	};
}

#endif // WINDOW_HPP
