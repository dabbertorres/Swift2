#include "Node.hpp"

namespace swift
{
	Node::Node(const sf::Vector2f& pos)
	:	position(pos)
	{
	}

	const sf::Vector2f& Node::getPosition() const
	{
		return position;
	}
}
