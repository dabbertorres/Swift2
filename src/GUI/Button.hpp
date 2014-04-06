#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Widget.hpp" // Base class: sgui::Widget

#include <string>
#include <functional>

namespace sgui
{
	class Button : public Widget
	{
		public:
			Button(int x, int y, int width, int height);
			virtual ~Button();
			
			virtual void run(int k);
			
			virtual sf::FloatRect getGlobalBounds() const;
			
			virtual void setFont(const sf::Font& f);
			
			virtual void setTextSize(unsigned ts);
			
			virtual void setString(const std::string& s);
			
			virtual void setColor(const sf::Color& c);
			
			virtual void setCall(const std::function<void(bool)>& f);
			
		private:
			// implemented on per-Widget type basis
			// This triggers when the widget is clicked. It should
			// implement any mouse click feedback, and then return
			virtual void clickPressFeedback();
			
			// implemented on per-Widget type basis
			// This triggers when the widget is clicked. It should
			// implement any mouse click feedback, and then return
			virtual void clickReleaseFeedback();
			
			// implemented on per-Widget type basis
			// This triggers when the widget is moused over, this function should
			// implement any mouse over feedback, and then return
			virtual void mousedOverFeedback();
			
			// implemented on per-Widget type basis
			// This triggers when the widget is moused off. It should
			// implement any mouse off feedback, and then return
			virtual void mousedOffFeedback();
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			std::string str;
			sf::Text text;
			
			sf::RectangleShape rect;
			sf::Color color;
			
			std::function<void(bool)> func;
	};
}

#endif // BUTTON_HPP
