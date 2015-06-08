#include "Noisy.hpp"

#include "Physical.hpp"

namespace swift
{
	Noisy::Noisy(unsigned int id, const Physical& p)
	:	Component(id),
		physical(p)
	{}
	
	Noisy::Noisy(const Noisy& other)
	:	Component(other.ID()),
		soundFile(other.soundFile),
		shouldPlay(other.shouldPlay),
		physical(other.physical)
	{}
	
	Noisy& Noisy::operator=(Noisy&& other)
	{
		soundFile = other.soundFile;
		shouldPlay = other.shouldPlay;
		const_cast<Physical&>(physical) = other.physical;
		
		return *this;
	}
	
	const Physical& Noisy::getPhysical() const
	{
		return physical;
	}
	
	std::map<std::string,std::string> Noisy::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("sound", soundFile);
		
		return std::move(variables);
	}
	
	void Noisy::unserialize(const std::map<std::string, std::string>& variables)
	{
		soundFile = variables.at("sound");
	}
}
