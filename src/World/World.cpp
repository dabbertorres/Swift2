#include "World.hpp"

#include <cmath>
#include "../Math/Math.hpp"

/* serialization headers */
#include <tinyxml2.h>

namespace swift
{
	World::World(const std::string& n, const sf::Vector2i& s, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp)
		:	assets(am),
			soundPlayer(sp),
			musicPlayer(mp),
			noisySystem(soundPlayer, assets),
			size(s),
			name(n)
	{
		tilemap.setSize(static_cast<sf::Vector2u>(s));
	}
	
	World::~World()
	{
		save();
		
		for(auto& e : entities)
		{
			delete e;
		}
	}
	
	void World::update(float dt)
	{
		controlSystem.update(entities, dt);
		moveSystem.update(entities, dt);
		pathSystem.update(entities, dt);
		physicalSystem.update(entities, dt);
		drawSystem.update(entities, dt);
		noisySystem.update(entities, dt);
		
		for(auto& e : entities)
		{
			if(e->has<Physical>() && e->has<Movable>())
			{
				Physical* phys = e->get<Physical>();
				Movable* mov = e->get<Movable>();
				
				const Tile* tile = tilemap.getTile(phys->position, phys->zIndex);
				
				// if is nullptr, bad layer or bad position
				// need to decide if engine should do something in this case. delete the entity?
				if(tile != nullptr)
				{
					if(!tile->isPassable())
					{
						// if entity moved onto an impassable tile, move it back
						phys->position -= mov->velocity * dt;
					}
				}
			}
		}
		
		
	}
	
	/* save file format */
	/* It is an xml file
	 * <world>
	 * 	<entity>
	 * 		<component type = "">
	 * 			<variable>component data</variable>
	 * 		</component>
	 * 	</entity>
	 * .
	 * .
	 * .
	 * </world>
	 */
	bool World::load()
	{
		std::string file = "./data/saves/" + name + ".world";
		
		tinyxml2::XMLDocument loadFile;
		loadFile.LoadFile(file.c_str());
		
		if(loadFile.Error())
		{
			log << "[ERROR] Loading world save file \"" << file << "\" failed.\n";
			return false;
		}
		
		tinyxml2::XMLElement* worldRoot = loadFile.FirstChildElement("world");
		if(worldRoot == nullptr)
		{
			log << "[WARNING] World save file \"" << file << "\" does not have a \"world\" root element.\n";
			return false;
		}
		
		tinyxml2::XMLElement* entityElement = worldRoot->FirstChildElement("entity");
		while(entityElement != nullptr)
		{
			Entity* entity = addEntity();
			
			tinyxml2::XMLElement* component = entityElement->FirstChildElement();
			while(component != nullptr)
			{
				std::string componentName = component->Value();
				entity->add(componentName);
				
				std::map<std::string, std::string> variables;
				tinyxml2::XMLElement* variableElement = component->FirstChildElement();
				while(variableElement != nullptr)
				{
					// make sure the strings aren't empty...
					if(std::string(variableElement->Value()).size() > 0 && std::string(variableElement->GetText()).size() > 0)
						variables.emplace(variableElement->Value(), variableElement->GetText());
					variableElement = variableElement->NextSiblingElement();
				}
				
				// get component and add to it
				entity->get(componentName)->unserialize(variables);
				
				if(componentName == "Drawable")
				{
					entity->get<Drawable>()->sprite.setTexture(assets.getTexture(entity->get<Drawable>()->texture));
				}
				
				component = component->NextSiblingElement();
			}
			
			entityElement = entityElement->NextSiblingElement("entity");
		}
		
		return true;
	}
	
	bool World::save()
	{
		std::string file = "./data/saves/" + name + ".world";
		
		tinyxml2::XMLDocument saveFile;
		
		if(saveFile.LoadFile(file.c_str()))
		{
			log << "[ERROR] Saving world save file \"" << file << "\" failed.\n";
			return false;
		}
		
		tinyxml2::XMLElement* root = saveFile.FirstChildElement("world");
		if(root == nullptr)
		{
			log << "[WARNING] World save file \"" << file << "\" does not have a \"world\" root element.\n";
			//return false;
			root = saveFile.NewElement("world");
			saveFile.InsertFirstChild(root);
		}
		else
			root->DeleteChildren();
		
		for(auto& e : entities)
		{
			tinyxml2::XMLElement* entity = saveFile.NewElement("entity");
			
			for(auto& c : e->getComponents())
			{
				tinyxml2::XMLElement* component = saveFile.NewElement(c.first.c_str());
				
				for(auto& v : c.second->serialize())
				{
					tinyxml2::XMLElement* variable = saveFile.NewElement(v.first.c_str());
					variable->SetText(v.second.c_str());
					component->InsertEndChild(variable);
				}
				
				entity->InsertEndChild(component);
			}
			
			root->InsertEndChild(entity);
		}
		
		saveFile.SaveFile(file.c_str());
		
		return true;
	}
	
	void World::drawWorld(sf::RenderTarget& target, sf::RenderStates states)
	{
		target.draw(tilemap, states);
	}
	
	void World::drawEntities(sf::RenderTarget& target, sf::RenderStates states)
	{
		drawSystem.draw(entities, target, states);
	}
	
	sf::Vector2i World::getSize() const
	{
		return size;
	}
	
	std::string World::getName() const
	{
		return name;
	}
	
	Entity* World::addEntity()
	{
		unsigned oldSize = entities.size();
		
		entities.emplace_back(new Entity);
		
		return entities.size() > oldSize ? entities[entities.size() - 1] : nullptr;
	}
	
	bool World::removeEntity(int e)
	{
		// if e is positive, check if is greater than last entity
		// if e is negative, check if it refers to entity less than 0
		if(e > static_cast<int>(entities.size()) || static_cast<int>(entities.size()) + e < 0)
			return false;
		
		entities.erase((e >= 0 ? entities.begin() : entities.end()) + e);
		
		return true;
	}
	
	Entity* World::getEntity(int e) const
	{
		// if e is positive, check if is greater than last entity
		// if e is negative, check if it refers to entity less than 0
		if(e > static_cast<int>(entities.size()) || static_cast<int>(entities.size()) + e < 0)
			return nullptr;
			
		return entities[(e >= 0 ? 0 : entities.size()) + e];
	}
	
	const std::vector<Entity*>& World::getEntities() const
	{
		return entities;
	}
	
	const std::vector<Entity*> World::getEntitiesAround(const sf::Vector2f& pos, float radius)
	{
		std::vector<Entity*> around;
		
		// if pos is outside of the world, or the radius is 0 or less, just return an empty vector
		if(!(0 <= pos.x && pos.x < size.x && 0 <= pos.y && pos.y < size.y) || radius <= 0)
			return around;
		
		for(auto& e : entities)
		{
			if(e->has<Physical>())
			{
				Physical* p = e->get<Physical>();
				if(math::distance(p->position, pos) <= radius)
					around.push_back(e);
			}
		}
		
		return around;
	}
	
	const std::vector<unsigned> World::getEntitiesAroundIDs(const sf::Vector2f& pos, float radius)
	{
		std::vector<unsigned> around;
		
		if(!(0 <= pos.x && pos.x < size.x && 0 <= pos.y && pos.y < size.y) || radius <= 0)
			return around;
		
		for(unsigned i = 0; i < entities.size(); i++)
		{
			if(entities[i]->has<Physical>())
			{
				Physical* p = entities[i]->get<Physical>();
				
				if(math::distance(p->position, pos) <= radius)
					around.push_back(i);
			}
		}
		
		return around;
	}
	
	const std::vector<Collision*> World::getCollisions() const
	{
		return physicalSystem.getCollisions();
	}
}
