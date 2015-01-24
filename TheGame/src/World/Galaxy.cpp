#include "Galaxy.hpp"

namespace tg
{
	Galaxy::Galaxy(Galaxy::Shape s, unsigned int size)
	:	shape(s)
	{
		systems.reserve(size);
	}

	Galaxy::~Galaxy()
	{
	}
	
	Galaxy::Shape Galaxy::getShape() const
	{
		return shape;
	}
	
	const SolarSystem* Galaxy::getSystem(unsigned int s) const
	{
		if(s < systems.size())
			return &systems[s];
		else
			return nullptr;
	}
}
