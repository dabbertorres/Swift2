#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "../Component.hpp"
#include "../../Pathfinding/Path.hpp"

#include <queue>

namespace swift
{
	class Physical;
	class Movable;
	
	class Pathfinder : public Component
	{
		public:
			Pathfinder(unsigned int id = 0);

			static constexpr Component::Type type();

			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			Path::PathNodes nodes;
			sf::Vector2f destination;
			bool needsPath;
	};
	
	constexpr Component::Type Pathfinder::type()
	{
		return Component::Type::Pathfinder;
	}
}

#endif // PATHFINDER_HPP
