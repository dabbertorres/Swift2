#include "TestWorld.hpp"

#include <pugixml.hpp>

namespace swift
{

	TestWorld::TestWorld(const sf::Vector2i s, AssetManager& a)
		:	World(s, a)
	{
		Script& playLogic = assets.getScript("./data/scripts/play.lua");
		playLogic.setWorld(*this);
		
		scripts["./data/scripts/quest.lua"] = &assets.getScript("./data/scripts/quest.lua");
	}

	TestWorld::~TestWorld()
	{
		save("./data/saves/default/maze.world");
	}
	
	/* save file format */
	/* It is an xml file
	 * <worldName>
	 * 	<entity>
	 * 		<component type = "">
	 * 			<variable>component data</variable>
	 * 		</component>
	 * 	</entity>
	 * .
	 * .
	 * .
	 * <script file = "">
	 * 	<variable name = "">value</variable>
	 * 	.
	 * 	.
	 * 	.
	 * </script>
	 */
	bool TestWorld::load(const std::string& file)
	{
		pugi::xml_document saveFile;
		
		pugi::xml_parse_result result = saveFile.load_file(file.c_str());
		
		if(!result)
		{
			log << "Loading save file \"" << file << "\" failed.\n";
			//return false;
		}
		/*
		// load entities
		for(pugi::xml_node entity : saveFile.children("entity"))
		{
			Entity* newEntity = addEntity();
			
			for(pugi::xml_node component : entity.children("component"))
			{
				newEntity->add(component.attribute("type").value());
				
				for(pugi::xml_node var : component.children())
				{
					
				}
			}
		}*/
		
		Script& playLogic = assets.getScript("./data/scripts/play.lua");
		playLogic.start();
		
		for(auto& s : scripts)
		{
			s.second->setWorld(*this);
			s.second->start();
		}
		
		return true;
	}
	
	bool TestWorld::save(const std::string& file)
	{
		pugi::xml_document saveFile;
		
		pugi::xml_parse_result result = saveFile.load_file(file.c_str());
		
		if(!result)
		{
			log << "Loading save file \"" << file << "\" failed.\n";
			//return false;
		}
		
		for(auto& s : scripts)
		{
			std::vector<std::string> variables = s.second->save();
			
			for(auto& v : variables)
			{
				
			}
		}
		
		return true;
	}
	
	void TestWorld::update(float dt)
	{
		Script& playLogic = assets.getScript("./data/scripts/play.lua");
		
		for(auto& e : entities)
		{
			moveSystem.update(*e, dt);
			physicalSystem.update(*e, dt);
			drawSystem.update(*e, dt);
		}
		
		playLogic.update();
		
		std::vector<std::map<std::string, Script*>::iterator> doneScripts;
		
		for(auto it = scripts.begin(); it != scripts.end(); it++)
		{
			it->second->update();
			
			// check if script is done, if so, push it for deletion
			if(it->second->toDelete())
				doneScripts.push_back(it);
		}
		
		// remove all done scripts
		for(auto& s : doneScripts)
		{
			scripts.erase(s);
		}
	}

}
