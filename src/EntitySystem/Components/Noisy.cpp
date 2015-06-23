#include "Noisy.hpp"

#include "Physical.hpp"

namespace swift
{
	Noisy::Noisy(unsigned int id)
	:	Component(id)
	{}
	
	std::map<std::string,std::string> Noisy::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("sound", soundFile);
		
		return variables;
	}
	
	void Noisy::unserialize(const std::map<std::string, std::string>& variables)
	{
		soundFile = variables.at("sound");
	}
}
