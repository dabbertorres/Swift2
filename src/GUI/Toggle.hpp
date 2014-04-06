#ifndef TOGGLE_HPP
#define TOGGLE_HPP

#include "Widget.hpp" // Base class: sgui::Widget

namespace sgui
{
	class Toggle : public sgui::Widget
	{
		public:
			Toggle(int x, int y, int width, int height);
			virtual ~Toggle();
			
			virtual void setState(bool s);

			virtual void run(int k);

			virtual sf::FloatRect getGlobalBounds() const;
			
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
			// This triggers when the widget is moused over. It should
			// implement any mouse over feedback, and then return
			virtual void mousedOverFeedback();
			
			// implemented on per-Widget type basis
			// This triggers when the widget is moused off. It should
			// implement any mouse off feedback, and then return
			virtual void mousedOffFeedback();

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::RectangleShape outline;
			sf::RectangleShape checked;
			sf::Color color;
			
			bool state;
			
			std::function<void(bool)> func;
	};
}

#endif // TOGGLE_HPP
