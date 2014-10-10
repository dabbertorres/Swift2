#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../MessageSystem/Observable.hpp"

#include <string>
#include <map>

namespace swift
{
	class Component : public Observable
	{
		public:
			virtual ~Component() = default;
			
			static std::string getType();
			
			virtual std::map<std::string, std::string> serialize() const = 0;
			virtual void unserialize(const std::map<std::string, std::string>& variables) = 0;
	};
}

#endif // COMPONENT_HPP
