#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <map>
#include <array>
#include <utility>
#include <string>

#include <dirent.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include "../EntitySystem/Components/Collidable.hpp"	// for bitmasks
#include "../Scripting/Script.hpp"

#include "../Logger/Logger.hpp"

#include "Mod.hpp"

namespace swift
{
	class AssetManager
	{
		public:
			AssetManager();
			~AssetManager();

			// Accepts a resource folder. This folder should contain folders containing a common group of resources.
			// This function will recursively roll through the top resource folder, grabbing all resources.
			// The function returns false if it cannot find the given folder, and returns true if otherwise.
			bool loadResourceFolder(const std::string& folder);
			
			bool loadMod(const Mod& mod);
			
			// destroys all resources the AssetManager contains
			void clean();
			
			// sets the AssetManager to load textures with smoothing (antialiasing)
			void setSmooth(bool s);
			
			sf::Texture& getTexture(const std::string& n);
			//Bitmask& getBitmask(const std::string& n);
			//Skeleton& getSkeleton(const std::string& n);
			sf::SoundBuffer& getSoundBuffer(const std::string& n);
			sf::Music& getSong(const std::string& n);
			sf::Font& getFont(const std::string& n);
			Script& getScript(const std::string& n);
			
			// following 6 const iterators are for the programmer/scripter checking if something was found or not
			const std::map<std::string, sf::Texture*>::iterator		TEXTURE_NOT_FOUND = textures.end();
			//const std::map<std::string, Bitmask*>::iterator			BITMASK_NOT_FOUND = bitmasks.end();
			//const std::map<std::string, Skeleton>::iterator	SKELETON_NOT_FOUND = skeletons.end();
			const std::map<std::string, sf::SoundBuffer*>::iterator SOUNDBUFFER_NOT_FOUND = soundBuffers.end();
			const std::map<std::string, sf::Music*>::iterator 		MUSIC_NOT_FOUND = music.end();
			const std::map<std::string, sf::Font*>::iterator 		FONT_NOT_FOUND = fonts.end();
			const std::map<std::string, Script*>::iterator 			SCRIPT_NOT_FOUND = scripts.end();

		private:
			bool loadResource(const std::string& file);
			
			std::map<std::string, sf::Texture*> textures;
			//std::map<std::string, Bitmask*> bitmasks;
			//std::map<std::string, Skeleton> skeletons;
			std::map<std::string, sf::SoundBuffer*> soundBuffers;
			std::map<std::string, sf::Music*> music;
			std::map<std::string, sf::Font*> fonts;
			std::map<std::string, Script*> scripts;
			
			bool smooth;
	};
}

#endif // ASSETMANAGER_HPP
