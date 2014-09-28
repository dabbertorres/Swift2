#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../MessageSystem/Observable.hpp"

#include <string>

namespace swift
{
	class Component : public Observable
	{
		public:
			virtual ~Component() = default;
			
			static std::string getType();
	};
}

#endif // COMPONENT_HPP
