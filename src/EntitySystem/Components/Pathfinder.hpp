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
			Pathfinder(unsigned int id, const Physical& p, Movable& m);
			
			const Physical& getPhysical() const;
			Movable& getMovable() const;

			static std::string getType();

			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			Path::PathNodes nodes;
			sf::Vector2f destination;
			bool needsPath;
			
		private:
			const Physical& physical;
			Movable& movable;
	};
}

#endif // PATHFINDER_HPP
