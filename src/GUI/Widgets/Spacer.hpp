#ifndef SPACER_HPP
#define SPACER_HPP

#include "../Widget.hpp"

namespace cstr
{
	class Spacer : public Widget
	{
		public:
			Spacer(const sf::Vector2i& size);
			~Spacer() = default;

			virtual void update(const sf::Event& event);
			
			virtual sf::FloatRect getGlobalBounds() const;

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // SPACER_HPP
