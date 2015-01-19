#include "AnimTexture.hpp"

#include <tinyxml2.h>

#include "../Logger/Logger.hpp"

namespace swift
{
	AnimTexture::AnimTexture()
	:	textureFile(""),
		file("")
	{}

	bool AnimTexture::loadFromFile(const std::string& f)
	{
		file = f;
		
		tinyxml2::XMLDocument loadFile;
		loadFile.LoadFile(f.c_str());
		
		if(loadFile.Error())
		{
			log << "[ERROR] Loading animation file \"" << file << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* animRoot = loadFile.FirstChildElement("animated");
		if(animRoot == nullptr)
		{
			log << "[WARNING] Animation file \"" << file << "\" does not have a \"animated\" root element.\n";
			return false;
		}
		
		textureFile = animRoot->Attribute("texture");
		
		tinyxml2::XMLElement* animation = animRoot->FirstChildElement("animation");
		while(animation != nullptr)
		{
			std::string animName = animation->Attribute("name");
			animations[animName].setTime(std::stof(animation->Attribute("time")));
			animations[animName].setLooping(std::string(animation->Attribute("looping")) == "true" ? true : false);
			
			tinyxml2::XMLElement* frame = animation->FirstChildElement("frame");
			while(frame != nullptr)
			{
				sf::IntRect frameRect;
				
				tinyxml2::XMLElement* param = frame->FirstChildElement();
				while(param != nullptr)
				{
					std::string name = param->Name();
					if(name == "x")
						frameRect.left = std::stoi(param->GetText());
					else if(name == "y")
						frameRect.top = std::stoi(param->GetText());
					else if(name == "w")
						frameRect.width = std::stoi(param->GetText());
					else if(name == "h")
						frameRect.height = std::stoi(param->GetText());
					else
						log << "[INFO]: Unknown paramater: \"" << name << "\" in anim file: " << file << '\n';
					
					param = param->NextSiblingElement();
				}
				
				animations[animName].addFrame(frameRect);
				
				frame = frame->NextSiblingElement("frame");
			}
			
			animation = animation->NextSiblingElement("animation");
		}
		
		return true;
	}
	
	const std::string& AnimTexture::getFile() const
	{
		return file;
	}
	
	const std::string& AnimTexture::getTextureFile() const
	{
		return textureFile;
	}
	
	std::vector<std::string> AnimTexture::getAnimNames() const
	{
		std::vector<std::string> anims;
		
		for(auto& it : animations)
		{
			anims.push_back(it.first);
		}
		
		return anims;
	}
	
	const FrameAnimation& AnimTexture::getAnimFrames(const std::string& n) const
	{
		return animations.at(n);
	}
}
