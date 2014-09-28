#ifndef PHYSICALSYSTEM_HPP
#define PHYSICALSYSTEM_HPP

#include "../System.hpp"

namespace swift
{
	class PhysicalSystem : public System
	{
		public:
			virtual void update(Entity& entity, float dt);

		private:
			float distance(sf::Vector2f one, sf::Vector2f two) const;
	};
}

#endif // PHYSICALSYSTEM_HPP
