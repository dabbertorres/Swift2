#include "Animated.hpp"

namespace swift
{
	Animated::Animated()
	:	animTex(nullptr),
		currentAnim(""),
		previousAnim("")
	{}
	
	void Animated::setAnimation(const std::string& anim)
	{
		if(anims.find(anim) == anims.end())
			return;
		
		previousAnim = currentAnim;
		currentAnim = anim;
	}
	
	void Animated::revertAnimation()
	{
		std::string temp = currentAnim;
		currentAnim = previousAnim;
		previousAnim = temp;
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
