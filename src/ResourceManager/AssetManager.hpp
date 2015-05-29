#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <unordered_map>
#include <string>

#include "FileSystem/gfs.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include "BatchDrawing/SpriteBatch.hpp"
#include "Animation/AnimTexture.hpp"
#include "Scripting/Script.hpp"

#include "Logger/Logger.hpp"
#include "Settings/Settings.hpp"

#include "Mod.hpp"

namespace swift
{
	class AssetManager
	{
		template<typename T>
		using ResourceMap = std::unordered_map<std::string, T>;
		
		public:
			AssetManager();
			~AssetManager();
			
			// Accepts a resource folder. This folder should contain folders containing a common group of resources.
			// This function will recursively roll through the top resource folder, grabbing all resources.
			// The function returns false if it cannot find the given folder, and returns true if otherwise.
			bool loadResourceFolder(const gfs::Path& folder);
			
			bool loadMods(const gfs::Path& modsFolder);
			
			// destroys all resources the AssetManager contains
			void clean();
			
			// sets the AssetManager to load textures with smoothing (antialiasing)
			void setSmooth(bool s);
			
			// make a SpriteBatch out of a texture, given a size
			bool newSpriteBatch(const std::string& t);

			AnimTexture* getAnimTexture(const std::string& n);
			SpriteBatch* getBatch(const std::string& n);
			sf::Texture* getTexture(const std::string& n);
			sf::SoundBuffer* getSoundBuffer(const std::string& n);
			sf::Music* getSong(const std::string& n);
			sf::Font* getFont(const std::string& n);
			Script* getScript(const std::string& n);

		protected:
			virtual bool loadResource(const gfs::Path& file);
			
			virtual bool loadAnimTexture(const gfs::Path& file);
			virtual bool loadTexture(const gfs::Path& file);
			virtual bool loadSound(const gfs::Path& file);
			virtual bool loadSong(const gfs::Path& file);
			virtual bool loadFont(const gfs::Path& file);
			virtual bool loadScript(const gfs::Path& file);

			ResourceMap<AnimTexture*> animTextures;
			ResourceMap<SpriteBatch*> batches;
			ResourceMap<sf::Texture*> textures;
			ResourceMap<sf::SoundBuffer*> soundBuffers;
			ResourceMap<sf::Music*> music;
			ResourceMap<sf::Font*> fonts;
			ResourceMap<Script*> scripts;
			ResourceMap<Mod> mods;

			bool smooth;
	};
}

#endif // ASSET_MANAGER_HPP
