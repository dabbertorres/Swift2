#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "../Component.hpp"

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Physical : public Component
	{
		public:
			static std::string getType();
			
			sf::Vector2f position;
			sf::Vector2u size;
	};
}

#endif // PHYSICAL_HPP
