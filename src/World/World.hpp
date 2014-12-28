#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>
#include <map>

/* SFML */
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Drawable.hpp>

/* Resources */
#include "../ResourceManager/AssetManager.hpp"

/* Entity */
#include "../EntitySystem/Entity.hpp"

#include "../EntitySystem/Systems/DrawableSystem.hpp"
#include "../EntitySystem/Systems/MovableSystem.hpp"
#include "../EntitySystem/Systems/PathfinderSystem.hpp"
#include "../EntitySystem/Systems/PhysicalSystem.hpp"
#include "../EntitySystem/Systems/NoisySystem.hpp"

#include "../Mapping/TileMap.hpp"

#include "../SoundSystem/MusicPlayer.hpp"
#include "../SoundSystem/SoundPlayer.hpp"

namespace swift
{
	class World
	{
		public:
			World(const std::string& n, const sf::Vector2i& s, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp);
			virtual ~World();

			virtual void update(float dt);

			virtual bool load();
			virtual bool save();

			void drawWorld(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
			void drawEntities(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

			sf::Vector2i getSize() const;
			
			std::string getName() const;

			Entity* addEntity();
			bool removeEntity(int e);
			
			Entity* getEntity(int e) const;
			const std::vector<Entity*>& getEntities() const;

			const std::vector<Entity*> getEntitiesAround(const sf::Vector2f& pos, float radius);
			const std::vector<unsigned> getEntitiesAroundIDs(const sf::Vector2f& pos, float radius);
			
			const std::vector<Collision*> getCollisions() const;

			TileMap tilemap;

		protected:
			AssetManager& assets;
			SoundPlayer& soundPlayer;
			MusicPlayer& musicPlayer;
			
			DrawableSystem drawSystem;
			MovableSystem moveSystem;
			PathfinderSystem pathSystem;
			PhysicalSystem physicalSystem;
			NoisySystem noisySystem;

			sf::Vector2i size;

			std::vector<Entity*> entities;

		private:
			std::string name;
	};
}

#endif // WORLD_HPP
