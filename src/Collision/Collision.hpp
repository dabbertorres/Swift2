#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "../MessageSystem/Observable.hpp"

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Entity;
	
	class Collision : public Observable<Collision&>
	{
		public:
			Collision(Entity& f, Entity& s);
			virtual ~Collision();
			
			Entity& getFirstEntity() const;
			Entity& getSecondEntity() const;
			
			const sf::Vector2f& getPosition() const;
			
		private:
			bool handle();
			
			static sf::Vector2f scaledDiffVector(const sf::Vector2f& one, const sf::Vector2f& two, float scale);
			
			Entity& one;
			Entity& two;
			sf::Vector2f position;
	};
}

#endif // COLLISION_HPP
