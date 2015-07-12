#ifndef SWIFT_SCRIPTABLE_SYSTEM_HPP
#define SWIFT_SCRIPTABLE_SYSTEM_HPP

#include "../System.hpp"

#include "../Components/Scriptable.hpp"

namespace swift
{
	class ScriptableSystem : public System<Scriptable>
	{
		public:
			virtual void update(float dt);
			
		private:
			virtual void addImpl(const Scriptable& s);
			virtual void removeImpl(const Scriptable&);
	};
}

#endif // SWIFT_SCRIPTABLE_SYSTEM_HPP
