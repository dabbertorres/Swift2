#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../MessageSystem/Observable.hpp"

#include <string>
#include <map>

namespace swift
{
	class Component : public Observable<Component*>
	{
		public:
			virtual ~Component() = default;
			
			static std::string getType();
			
			virtual std::map<std::string, std::string> serialize() const = 0;
			virtual void unserialize(const std::map<std::string, std::string>& variables) = 0;
		
		protected:
			template<typename T>
			static void initMember(const std::string& name, const std::map<std::string, std::string>& variables, T& var, T def);
	};
	
	template<>
	inline void Component::initMember<int>(const std::string& name, const std::map<std::string, std::string>& variables, int& var, int def)
	{
		if(variables.find(name) != variables.end())
		{
			var = std::stoi(variables.at(name));
		}
		else
		{
			var = def;
		}
	}
	
	template<>
	inline void Component::initMember<unsigned int>(const std::string& name, const std::map<std::string, std::string>& variables, unsigned int& var, unsigned int def)
	{
		if(variables.find(name) != variables.end())
		{
			var = std::stoi(variables.at(name));
		}
		else
		{
			var = def;
		}
	}
	
	template<>
	inline void Component::initMember<float>(const std::string& name, const std::map<std::string, std::string>& variables, float& var, float def)
	{
		if(variables.find(name) != variables.end())
		{
			var = std::stof(variables.at(name));
		}
		else
		{
			var = def;
		}
	}
	
	template<>
	inline void Component::initMember<bool>(const std::string& name, const std::map<std::string, std::string>& variables, bool& var, bool def)
	{
		if(variables.find(name) != variables.end())
		{
			var = variables.at(name) == "true";
		}
		else
		{
			var = def;
		}
	}
	
	template<>
	inline void Component::initMember<std::string>(const std::string& name, const std::map<std::string, std::string>& variables, std::string& var, std::string def)
	{
		if(variables.find(name) != variables.end())
		{
			var = variables.at(name);
		}
		else
		{
			var = def;
		}
	}
}

#endif // COMPONENT_HPP
