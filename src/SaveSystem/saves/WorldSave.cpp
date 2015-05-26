#include "WorldSave.hpp"

namespace swift
{
	WorldSave::WorldSave(const World& w)
	:	name(w.getName()),
		tilemap(w.tilemap.getFile())
	{
		save(w);
	}
	
	void WorldSave::load(World& w)
	{
		auto& systems = w.getSystems();
		
		// doing Physical first since it's what other Components depend on most
		System<Physical>* physSys = systems.get<Physical>();
		for(auto& c : components[Component::Type::Physical])
		{
			physSys->add(c.first)->unserialize(c.second);
		}
		
		// Movable is the next with most dependencies
		System<Movable>* movSys = systems.get<Movable>();
		for(auto& c : components[Component::Type::Movable])
		{
			movSys->add(c.first, physSys->get(c.first))->unserialize(c.second);
		}
		
		// now can do the rest
		System<Animated>* animSys = systems.get<Animated>();
		for(auto& c : components[Component::Type::Animated])
		{
			animSys->add(c.first, physSys->get(c.first))->unserialize(c.second);
		}
		
		System<BatchDrawable>* bdrawSys = systems.get<BatchDrawable>();
		for(auto& c : components[Component::Type::BatchDrawable])
		{
			bdrawSys->add(c.first, physSys->get(c.first))->unserialize(c.second);
		}
		
		System<Controllable>* ctrlSys = systems.get<Controllable>();
		for(auto& c : components[Component::Type::Controllable])
		{
			ctrlSys->add(c.first, movSys->get(c.first))->unserialize(c.second);
		}
		
		System<Drawable>* drawSys = systems.get<Drawable>();
		for(auto& c : components[Component::Type::Drawable])
		{
			drawSys->add(c.first, physSys->get(c.first))->unserialize(c.second);
		}
		
		System<Name>* nameSys = systems.get<Name>();
		for(auto& c : components[Component::Type::Name])
		{
			nameSys->add(c.first)->unserialize(c.second);
		}
		
		System<Noisy>* noiseSys = systems.get<Noisy>();
		for(auto& c : components[Component::Type::Noisy])
		{
			noiseSys->add(c.first, physSys->get(c.first))->unserialize(c.second);
		}
		
		System<Pathfinder>* pfSys = systems.get<Pathfinder>();
		for(auto& c : components[Component::Type::Pathfinder])
		{
			pfSys->add(c.first, movSys->get(c.first))->unserialize(c.second);
		}
	}
	
	void WorldSave::save(const World& w)
	{
		name = w.getName();
		tilemap = w.tilemap.getFile();
		
		components.clear();
		
		auto& systems = w.getSystems();
		for(auto* s : systems)
		{
			auto comps = s->getAll();
			for(auto* c : comps)
			{
				components[s->typeEnum()][c->ID()] = c->serialize();
			}
		}
	}
	
	const std::string& WorldSave::getName() const
	{
		return name;
	}
	
	const std::string& WorldSave::getTilemap() const
	{
		return tilemap;
	}
	
	WorldSave::WorldSave(const std::string& n, const std::string& tm, const Data& wd)
	:	name(n),
		tilemap(tm),
		components(wd)
	{}
}
