#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <vector>

#include "Body.hpp"

namespace tg
{
	class SolarSystem
	{
		public:
			SolarSystem(unsigned int size);
			~SolarSystem();

		private:
			std::vector<Body> bodies;
	};
}

#endif // SOLARSYSTEM_HPP
