#ifndef BATCHDRAWSYSTEM_HPP
#define BATCHDRAWSYSTEM_HPP

#include "../System.hpp"

#include "../Entity.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class AssetManager;
	
	class BatchDrawSystem : public System
	{
		public:
			virtual void update(std::vector<Entity*>& entities, float dt);
			
			virtual void draw(std::vector<Entity*>& entities, float e, sf::RenderTarget& target, sf::RenderStates states, AssetManager& assets) const;
	};
}

#endif // BATCHDRAWSYSTEM_HPP
