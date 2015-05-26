#ifndef BATCHDRAWSYSTEM_HPP
#define BATCHDRAWSYSTEM_HPP

#include "../System.hpp"

#include "../Components/BatchDrawable.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <unordered_set>

namespace swift
{
	class AssetManager;
	
	class BatchDrawSystem : public System<BatchDrawable>
	{
		public:
			BatchDrawSystem() = default;
			BatchDrawSystem(unsigned int res);
			
			virtual void update(float dt);
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states, AssetManager& assets) const;
		
		private:
			virtual void addImpl(const BatchDrawable& c);
			std::unordered_set<std::string> batches;
	};
}

#endif // BATCHDRAWSYSTEM_HPP
