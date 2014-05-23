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

namespace cstr
{
	class Window : public sf::Drawable
	{
		public:
			Window();
			~Window();
			
			void update(sf::Event& event);
			
			Button& addButton(sf::IntRect rect, const sf::Texture& tex, const std::function<void()>& f);
			Label& addLabel(const sf::Vector2f& pos, const std::string& str, const sf::Font& font);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			std::vector<Widget*> widgets;
			Widget* activeWidget;
	};
}

#endif // WINDOW_HPP
