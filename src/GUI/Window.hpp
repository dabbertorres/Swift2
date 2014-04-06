#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <memory>

/* SFML headers */
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/* sgui headers */
#include "Widget.hpp"
#include "Widgets.hpp"

namespace sgui
{
	// automated widget organization
	enum Organization
	{
		Horizontal,		// automated
		Vertical,		// automated
		Custom			// if full control of widget placement is desired
	};
	
	class Window : public sf::Drawable
	{
		public:
			Window(const sf::Window& w, const sf::Font& f, unsigned ts, bool a = true);
			~Window();
			
			void update(sf::Event event);
			
			void addChild(Widget* c);
			
			Widget& getChild(unsigned c) const;
			
			bool toggle();
			
			bool isActive() const;
			
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			void organize();
			
			std::vector< std::unique_ptr<Widget> > children;
			
			TextBox* activeTextBox;
			
			Organization org;
			int rows_cols;
			
			const sf::Window& window;
			
			const sf::Font& font;
			unsigned textSize;
			
			bool active;	// controls whether the Window is updated and drawn or not
	};
}

#endif // WINDOW_HPP
