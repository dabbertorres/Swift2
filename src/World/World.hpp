#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../EntitySystem/Entity.hpp"

namespace swift
{
	class World
	{
		public:
			World(const sf::Vector2u& s);
			~World();
			
			const std::vector<Entity>& getEntities() const;

			virtual void update(float dt) = 0;
			
			virtual void draw(sf::RenderTarget& target) const = 0;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
			
			virtual void load(const std::string& file) = 0;
			
			virtual void save(const std::string& file) = 0;

		private:
			sf::Vector2u size;
			
			std::vector<Entity> entities;
	};
}

#endif // WORLD_HPP
