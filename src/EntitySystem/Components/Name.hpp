#ifndef NAME_HPP
#define NAME_HPP

#include "../Component.hpp"

#include <string>

namespace swift
{
	class Name : public Component
	{
		public:
			Name();
			
			static std::string getType();
			
			std::string name;
	};
}

#endif // NAME_HPP
