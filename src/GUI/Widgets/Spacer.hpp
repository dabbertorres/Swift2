#ifndef SPACER_HPP
#define SPACER_HPP

#include "../Widget.hpp"

namespace cstr
{
	class Spacer : public Widget
	{
		public:
			Spacer(sf::Vector2i size);
			~Spacer();

			virtual void update(sf::Event& event);
			
			virtual sf::FloatRect getGlobalBounds() const;

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // SPACER_HPP
