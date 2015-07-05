#ifndef SWIFT_RESOURCE_NOT_FOUND_HPP
#define SWIFT_RESOURCE_NOT_FOUND_HPP

#include <stdexcept>

namespace swift
{
	class ResourceNotFound : public std::runtime_error
	{
		public:
			explicit ResourceNotFound(const std::string& wa);
			explicit ResourceNotFound(const char* wa);
	};
}

#endif
