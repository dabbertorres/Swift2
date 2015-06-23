#include "Animated.hpp"

#include "Physical.hpp"

namespace swift
{
	Animated::Animated(unsigned int id)
	:	Component(id),
		animTex(nullptr),
	    currentAnim(""),
	    previousAnim("")
	{}
	
	void Animated::setAnimation(const std::string& anim)
	{
		if(anims.find(anim) == anims.end())
			return;
		
		anims[currentAnim].stop();
		anims[anim].play();
		
		std::string temp = anim;
		previousAnim = currentAnim;
		currentAnim = temp;
	}

	void Animated::revertAnimation()
	{
		setAnimation(previousAnim);
	}

	bool Animated::createAnimations()
	{
		if(animTex)
		{
			for(auto& a : animTex->getAnimNames())
			{
				anims[a] = animTex->getAnimFrames(a);
			}
			
			return true;
		}
		else
		{
			return false;
		}
	}

	std::map<std::string, std::string> Animated::serialize() const
	{
		std::map<std::string, std::string> variables;

		variables.emplace("scaleX", std::to_string(sprite.getScale().x));
		variables.emplace("scaleY", std::to_string(sprite.getScale().y));
		variables.emplace("animation", animationFile);

		return variables;
	}

	void Animated::unserialize(const std::map<std::string, std::string>& variables)
	{
		sprite.setScale(std::stof(variables.at("scaleX")), std::stof(variables.at("scaleY")));
		
		animationFile = variables.at("animation");
	}
}
