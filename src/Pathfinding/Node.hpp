#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Node
	{
		public:
			Node(const sf::Vector2f& pos);
			
			const sf::Vector2f& getPosition() const;

		private:
			sf::Vector2f position;

	};
}

#endif // NODE_HPP
