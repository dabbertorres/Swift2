#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

#include "../Component.hpp" // Base class: swift::Component

namespace swift
{
	class Movable;
	
	class Controllable : public swift::Component
	{
		public:
			Controllable(unsigned int id = 0);
			
			static constexpr Component::Type type();
			
			virtual std::map<std::string,std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);
			
			// bools of things a player entity should do when a key is pressed
			bool moveLeft;
			bool moveRight;
			bool moveUp;
			bool moveDown;
	};
	
	constexpr Component::Type Controllable::type()
	{
		return Component::Type::Controllable;
	}
}

#endif // CONTROLLABLE_HPP
