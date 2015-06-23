#ifndef NAME_HPP
#define NAME_HPP

#include "../Component.hpp"

#include <string>

namespace swift
{
	class Name : public Component
	{
		public:
			Name(unsigned int id = 0);
			
			static constexpr Component::Type type();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);
			
			std::string name;
	};
	
	constexpr Component::Type Name::type()
	{
		return Component::Type::Name;
	}
}

#endif // NAME_HPP
