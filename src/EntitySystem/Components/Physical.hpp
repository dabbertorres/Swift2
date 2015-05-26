#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "../Component.hpp"

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Physical : public Component
	{
		public:
			Physical(unsigned int id);
			
			Physical(const Physical& other);

			static Component::Type type();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			sf::Vector2f position;
			unsigned int zIndex;
			sf::Vector2u size;
			bool collides;
			float angle;	// degrees
	};
}

#endif // PHYSICAL_HPP
