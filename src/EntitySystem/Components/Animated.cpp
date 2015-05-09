#include "Animated.hpp"

#include "Physical.hpp"

namespace swift
{
	Animated::Animated(unsigned int id, const Physical& p)
	:	Component(id),
		animTex(nullptr),
	    currentAnim(""),
	    previousAnim(""),
		physical(p)
	{}

	Animated& Animated::operator=(Animated&& other)
	{
		sprite = other.sprite;
		animTex = other.animTex;
		anims = other.anims;
		currentAnim = other.currentAnim;
		previousAnim = other.previousAnim;
		animationFile = other.animationFile;
		const_cast<Physical&>(physical) = other.physical;
		
		return *this;
	}
			
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
			return false;
	}
	
	const Physical& Animated::getPhysical() const
	{
		return physical;
	}

	std::string Animated::getType()
	{
		return "Animated";
	}

	std::map<std::string, std::string> Animated::serialize() const
	{
		std::map<std::string, std::string> variables;

		variables.emplace("scaleX", std::to_string(sprite.getScale().x));
		variables.emplace("scaleY", std::to_string(sprite.getScale().y));
		variables.emplace("animation", animationFile);

		return std::move(variables);
	}

	void Animated::unserialize(const std::map<std::string, std::string>& variables)
	{
		sf::Vector2f scale;
		initMember("scaleX", variables, scale.x, 0.f);
		initMember("scaleY", variables, scale.y, 0.f);
		sprite.setScale(scale);

		initMember("animation", variables, animationFile, std::string("./data/anims/man.anim"));
	}
}
