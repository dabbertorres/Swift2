#ifndef BATCHDRAWSYSTEM_HPP
#define BATCHDRAWSYSTEM_HPP

#include "../System.hpp"

#include "../Components/BatchDrawable.hpp"
#include "../Components/Physical.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <unordered_set>

namespace swift
{
	class AssetManager;
	
	class BatchDrawSystem : public System<BatchDrawable>
	{
		public:
			BatchDrawSystem(AssetManager* am);
			
			virtual void update(float dt);
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			void setPhysSystem(System<Physical>* ps);
		
		private:
			virtual void addImpl(const BatchDrawable& c);
			std::unordered_set<SpriteBatch*> batches;
			
			System<Physical>* physSystem;
			
			AssetManager* assets;
	};
}

#endif // BATCHDRAWSYSTEM_HPP
