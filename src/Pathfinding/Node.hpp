#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Node
	{
		public:
			Node(const sf::Vector2u& pos);
			
			const sf::Vector2u& getPosition() const;

		private:
			sf::Vector2u position;

	};
}

#endif // NODE_HPP
