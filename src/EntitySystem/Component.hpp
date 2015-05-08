#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <map>

namespace swift
{
	class Component
	{
		public:
			enum class Type : unsigned long int
			{
				Animated = 1 << 0,
				BatchDrawable = 1 << 1,
				Controllable = 1 << 2,
				Drawable = 1 << 3,
				Movable = 1 << 4,
				Name = 1 << 5,
				Noisy = 1 << 6,
				Pathfinder = 1 << 7,
				Physical = 1 << 8,
				
				MAX = 1 << 9,
			};
			
			Component(unsigned int i);
			virtual ~Component() = default;
			
			unsigned int ID() const;

			static Type type();

			virtual std::map<std::string, std::string> serialize() const = 0;
			virtual void unserialize(const std::map<std::string, std::string>& variables) = 0;

		protected:
			template<typename T>
			static void initMember(const std::string& name, const std::map<std::string, std::string>& variables, T& var, T def);
			
		private:
			unsigned int id;
	};
	
	Component::Component(unsigned int i)
	:	id(i)
	{}
	
	unsigned int Component::ID() const
	{
		return id;
	}

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
