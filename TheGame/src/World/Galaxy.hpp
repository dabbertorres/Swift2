#ifndef GALAXY_HPP
#define GALAXY_HPP

#include <vector>

#include "SolarSystem.hpp"

namespace tg
{
	class Galaxy
	{
		public:
			enum class Shape
			{
				Elliptical,
				Spiral,
				BarredSpiral,
				Ring,
			};
			
			Galaxy(Shape s, unsigned int size);
			~Galaxy();
			
			Shape getShape() const;
			const SolarSystem* getSystem(unsigned int s) const;

		private:
			std::vector<SolarSystem> systems;
			
			Shape shape;
	};
}

#endif // GALAXY_HPP
