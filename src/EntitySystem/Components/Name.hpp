#ifndef NAME_HPP
#define NAME_HPP

#include "../Component.hpp"

#include <string>

namespace swift
{
	class Name : public Component
	{
		public:
			Name(unsigned int id);
			
			static Component::Type type();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);
			
			std::string name;
	};
}

#endif // NAME_HPP
