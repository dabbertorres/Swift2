#include "Noisy.hpp"

namespace swift
{
	Noisy::Noisy(unsigned int id, const Physical& p)
	:	Component(id),
		physical(p)
	{}
	
	const Physical& Noisy::getPhysical() const
	{
		return physical;
	}
	
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
