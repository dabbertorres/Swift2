#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "../Component.hpp"
#include "../../Pathfinding/Path.hpp"

#include <queue>

namespace swift
{
	class Pathfinder : public Component
	{
		public:
			static std::string getType();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);
			
			Path::PathNodes nodes;
	};
}

#endif // PATHFINDER_HPP
