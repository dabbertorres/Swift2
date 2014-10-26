#ifndef COMPONENTREGISTRY_HPP
#define COMPONENTREGISTRY_HPP

#include "Component.hpp"
#include "Components/Drawable.hpp"
#include "Components/Movable.hpp"
#include "Components/Physical.hpp"
#include "Components/Name.hpp"

namespace swift
{
	class ComponentRegistry
	{
		public:
			static Component* get(const std::string& c)
			{
				if(c == "Drawable")
					return new Drawable;
				else if(c == "Movable")
					return new Movable;
				else if(c == "Physical")
					return new Physical;
				else if(c == "Name")
					return new Name;
				else
					return nullptr;
			}
	};
}

#endif // COMPONENTREGISTRY_HPP