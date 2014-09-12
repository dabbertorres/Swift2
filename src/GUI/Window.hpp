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
#include "Container.hpp"

namespace cstr
{
	class Window : public sf::Drawable
	{
		public:
			Window();
			~Window();
			
			void update(sf::Event& event);
			
			template<typename C>
			C& addContainer(C* c);
			
			void setFont(sf::Font& font);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			std::vector<Container*> containers;
			
			sf::Font* font;
	};
	
	template<typename C>
	C& Window::addContainer(C* c)
	{
		static_assert(std::is_base_of<Container, C>::value, "C must be a child of cstr::Container");
		
		containers.push_back(c);
		
		return *c;
	}
}

#endif // WINDOW_HPP
