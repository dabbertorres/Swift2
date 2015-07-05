#include "Node.hpp"

namespace swift
{
	Node::Node(const sf::Vector2u& pos)
	:	position(pos)
	{
	}

	const sf::Vector2u& Node::getPosition() const
	{
		return position;
	}
}
