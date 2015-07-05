#ifndef COLUMN_HPP
#define COLUMN_HPP

#include "../Container.hpp"

namespace cstr
{
	class Column : public Container
	{
		public:
			Column(const sf::IntRect& r, bool s);
			Column(const sf::Vector2i& size, bool s);
			~Column() = default;
			
			virtual void update(const sf::Event& event);
			virtual void setPosition(const sf::Vector2i& pos);

		private:
			virtual void reposition();
			virtual void scroll(float amount);
	};
}

#endif // COLUMN_HPP
