#include "SoundsLimit.hpp"

namespace swift
{
	SoundsLimit::SoundsLimit()
	{}
	
	unsigned SoundsLimit::total = 0;
	const unsigned SoundsLimit::limit = 256;
}