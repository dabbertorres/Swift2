#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "Widget.hpp" // Base class: sgui::Widget

#include <string>

namespace sgui
{
	class TextBox : public sgui::Widget
	{
		public:
			TextBox(int x, int y, int width, int height);
			virtual ~TextBox();
			
			virtual void parse(const sf::Event& e);
			
			virtual void run(int k);

			virtual sf::FloatRect getGlobalBounds() const;
			
			virtual void setFont(const sf::Font& f);
			
			virtual void setString(const std::string& s);
			
			const std::string& getString() const;

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
			
			sf::RectangleShape box;
			std::string str;
			sf::Text text;
			
			bool receiveText;
	};
}

#endif // TEXTBOX_HPP
