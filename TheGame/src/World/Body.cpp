#include "Body.hpp"

namespace tg
{
	Body::Body(Body::Type t, Body::LifeLevel l, Body::Atmosphere a)
	:	type(t),
		life(l),
		atmosphere(a)
	{
	}

	Body::~Body()
	{
	}
}
