#ifndef ROW_HPP
#define ROW_HPP

#include "../Container.hpp"

namespace cstr
{
	class Row : public Container
	{
		public:
			Row(sf::IntRect r, bool s);
			Row(sf::Vector2i size, bool s);
			~Row();

			virtual void update(sf::Event& event);
			virtual void setPosition(sf::Vector2i pos);

		private:
			virtual void reposition();
			virtual void scroll(float amount);

	};
}

#endif // ROW_HPP
