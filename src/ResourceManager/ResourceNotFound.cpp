#include "ResourceNotFound.hpp"

namespace swift
{
	ResourceNotFound::ResourceNotFound(const std::string& wa)
	:	std::runtime_error(wa)
	{}

	ResourceNotFound::ResourceNotFound(const char* wa)
	:	std::runtime_error(wa)
	{}
}
