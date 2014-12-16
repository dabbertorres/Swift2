#include "Noisy.hpp"

namespace swift
{
	std::string Noisy::getType()
	{
		return "Noisy";
	}
	
	std::map<std::string,std::string> Noisy::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("sound", soundFile);
		
		return std::move(variables);
	}
	
	void Noisy::unserialize(const std::map<std::string, std::string>& variables)
	{
		initMember("sound", variables, soundFile, std::string("./data/sounds/nothing.wav"));
	}
}
