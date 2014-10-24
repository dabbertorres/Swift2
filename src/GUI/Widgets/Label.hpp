#ifndef LABEL_HPP
#define LABEL_HPP

#include "../Widget.hpp"

#include <SFML/Graphics/Text.hpp>
#include <string>

namespace cstr
{
	class Label : public Widget
	{
		public:
			Label(const std::string& str, const sf::Font& f, unsigned ts = 0);
			~Label();
			
			virtual void update(sf::Event& event);

			virtual sf::FloatRect getGlobalBounds() const;
			
			void setString(const std::string& str, unsigned ts = 0);
			const std::string& getString() const;
			
			virtual void setPosition(sf::Vector2i pos);
			
			virtual void setSize(sf::Vector2u size);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Text text;
			std::string string;
			unsigned textSize;
	};
}

#endif // LABEL_HPP
