#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Physical
	{
		public:
			Physical();
			~Physical();

			void addForce(sf::Vector2f n);
			
			void update(float dt);
			
			static float getGravity();
			static void setGravity(float g);

		private:
			float mass;
			sf::Vector2f acceleration;
			
			sf::Vector2f velocity;
			
			sf::Vector2f position;
			
			static float gravity;
	};
}

#endif // PHYSICAL_HPP
