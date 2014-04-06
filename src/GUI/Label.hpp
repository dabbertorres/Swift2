#ifndef LABEL_HPP
#define LABEL_HPP

#include "Widget.hpp" // Base class: sgui::Widget

#include <string>

namespace sgui
{
	class Label : public sgui::Widget
	{
		public:
			Label(int x, int y, int width, int height);
			virtual ~Label();

			virtual void run(int k);

			virtual sf::FloatRect getGlobalBounds() const;
			
			virtual void setFont(const sf::Font& f);
			
			virtual void setTextSize(unsigned ts);
			
			virtual void setString(const std::string& s);
			
			virtual void setColor(const sf::Color& c);

		private:			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			std::string str;
			sf::Text text;
	};
}

#endif // LABEL_HPP
