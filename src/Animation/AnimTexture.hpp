#ifndef ANIMTEXTURE_HPP
#define ANIMTEXTURE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <map>

#include "FrameAnimation.hpp"

namespace swift
{
	class AnimTexture
	{
		public:
			AnimTexture();
			
			bool loadFromFile(const std::string& f);
			
			const std::string& getFile() const;
			const std::string& getTextureFile() const;
			std::vector<std::string> getAnimNames() const;
			const FrameAnimation& getAnimFrames(const std::string& n) const;

		private:
			std::string textureFile;
			std::string file;
			
			std::map<std::string, FrameAnimation> animations;
	};
}

#endif // ANIMTEXTURE_HPP
