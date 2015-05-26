#ifndef SWIFT_NAME_SYSTEM_HPP
#define SWIFT_NAME_SYSTEM_HPP

#include "../System.hpp"

#include "../Components/Name.hpp"

namespace swift
{
	class NameSystem : public System<Name>
	{
		public:
			NameSystem() = default;
			NameSystem(unsigned int res);
			
			virtual void update(float dt);

	};
}

#endif // SWIFT_NAME_SYSTEM_HPP
