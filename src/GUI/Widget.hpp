#ifndef WIDGET_HPP
#define WIDGET_HPP

/* SFML headers */
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace sgui
{
	class Widget : public sf::Drawable
	{
		public:
			Widget(int x, int y, int width, int height);
			virtual ~Widget();
			
			void mousedOver(bool m);	// true = mouse is on
										// false = mouse is off
			
			void clickedOn(bool c);		// true = press
										// false = release
			
			void setActive(bool a);		// true = active
										// false = not active
										// "active" meaning it is available to be interacted with and drawn
			
			bool isMouseOn() const;
			
			bool isClicked() const;
			
			bool isActive() const;
			
			virtual void setFont(const sf::Font& f);
			
			virtual void setTextSize(unsigned ts);
			
			virtual void setString(const std::string& s);
			
			virtual void setColor(const sf::Color& c);
			
			virtual void setCall(const std::function<void(bool)>& f);
			
			virtual void run(int k = -1) = 0;
			
			virtual sf::FloatRect getGlobalBounds() const = 0;
			
		private:
			// implemented on per-Widget type basis
			// This triggers when the widget is clicked. It should
			// implement any mouse click feedback, and then return
			virtual void clickPressFeedback();
			
			// implemented on per-Widget type basis
			// This triggers when the widget is released. It should
			// implement any mouse release feedback, and then return
			virtual void clickReleaseFeedback();
			
			// implemented on per-Widget type basis
			// This triggers when the widget is moused over. It should
			// implement any mouse over feedback, and then return
			virtual void mousedOverFeedback();
			
			// implemented on per-Widget type basis
			// This triggers when the widget is moused off. It should
			// implement any mouse off feedback, and then return
			virtual void mousedOffFeedback();

			bool mouseOn;
			bool clicked;
			bool active;
	};
}

#endif // WIDGET_HPP
