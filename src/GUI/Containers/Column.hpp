#ifndef COLUMN_HPP
#define COLUMN_HPP

#include "../Container.hpp"

namespace cstr
{
	class Column : public Container
	{
		public:
			Column(sf::IntRect r, bool s);
			Column(sf::Vector2i size, bool s);
			~Column();
			
			virtual void update(sf::Event& event);
			virtual void setPosition(sf::Vector2i pos);

		private:
			virtual void reposition();
			virtual void scroll(float amount);
	};
}

#endif // COLUMN_HPP
