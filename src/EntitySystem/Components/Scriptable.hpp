#ifndef SCRIPTABLE_HPP
#define SCRIPTABLE_HPP

#include "../Component.hpp"

#include "Scripting/Script.hpp"

namespace swift
{
	class Scriptable : public Component
	{
		public:
			Scriptable(unsigned int id = 0);
			Scriptable(const Scriptable& other);
			
			Scriptable& operator=(const Scriptable& other);

			static constexpr Component::Type type();
			
			ScriptHandle script;
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);
	};

	constexpr Component::Type Scriptable::type()
	{
		return Component::Type::Scriptable;
	}
}

#endif // SCRIPTABLE_HPP
