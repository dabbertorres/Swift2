#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <map>
#include <array>
#include <utility>
#include <string>

#include <dirent.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include "../BatchDrawing/SpriteBatch.hpp"
#include "../Animation/AnimTexture.hpp"
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

			// make a SpriteBatch out of a texture, given a size
			bool newSpriteBatch(const std::string& t, unsigned int s);

			AnimTexture* getAnimTexture(const std::string& n);
			SpriteBatch* getBatch(const std::string& n);
			sf::Texture* getTexture(const std::string& n);
			sf::SoundBuffer* getSoundBuffer(const std::string& n);
			sf::Music* getSong(const std::string& n);
			sf::Font* getFont(const std::string& n);
			Script* getScript(const std::string& n);

		protected:
			virtual bool loadAnimTexture(const std::string& file);
			virtual bool loadTexture(const std::string& file);
			virtual bool loadSound(const std::string& file);
			virtual bool loadSong(const std::string& file);
			virtual bool loadFont(const std::string& file);
			virtual bool loadScript(const std::string& file);

			bool loadResource(const std::string& file);

			std::map<std::string, AnimTexture*> animTextures;
			std::map<std::string, SpriteBatch*> batches;
			std::map<std::string, sf::Texture*> textures;
			std::map<std::string, sf::SoundBuffer*> soundBuffers;
			std::map<std::string, sf::Music*> music;
			std::map<std::string, sf::Font*> fonts;
			std::map<std::string, Script*> scripts;

			bool smooth;
	};
}

#endif // ASSET_MANAGER_HPP
