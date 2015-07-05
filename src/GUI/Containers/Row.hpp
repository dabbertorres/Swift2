#ifndef ROW_HPP
#define ROW_HPP

#include "../Container.hpp"

namespace cstr
{
	class Row : public Container
	{
		public:
			Row(const sf::IntRect& r, bool s);
			Row(const sf::Vector2i& size, bool s);
			~Row() = default;

			virtual void update(const sf::Event& event);
			virtual void setPosition(const sf::Vector2i& pos);

		private:
			virtual void reposition();
			virtual void scroll(float amount);

	};
}

#endif // ROW_HPP
