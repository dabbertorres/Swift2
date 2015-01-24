#ifndef COMPONENTREGISTRY_HPP
#define COMPONENTREGISTRY_HPP

#include "Component.hpp"
#include "Components/Animated.hpp"
#include "Components/BatchDrawable.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Movable.hpp"
#include "Components/Pathfinder.hpp"
#include "Components/Physical.hpp"
#include "Components/Name.hpp"
#include "Components/Noisy.hpp"

namespace swift
{
	class ComponentRegistry
	{
		public:
			static Component* get(const std::string& c)
			{
				if(c == "Animated")
					return new Animated;
				else if(c == "BatchDrawable")
					return new BatchDrawable;
				else if(c == "Controllable")
					return new Controllable;
				else if(c == "Drawable")
					return new Drawable;
				else if(c == "Movable")
					return new Movable;
				else if(c == "Pathfinder")
					return new Pathfinder;
				else if(c == "Physical")
					return new Physical;
				else if(c == "Name")
					return new Name;
				else if(c == "Noisy")
					return new Noisy;
				else
					return nullptr;
			}
	};
}

#endif // COMPONENTREGISTRY_HPP
