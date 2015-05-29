#ifdef _WIN32

#include "../Path.hpp"

#include <windows.h>

namespace gfs
{
	std::chrono::system_clock::time_point Path::lastAccess() const
	{
		return {};
	}
	
	std::chrono::system_clock::time_point Path::lastModify() const
	{
		return {};
	}
	
	unsigned long int Path::fileSize() const
	{
		return 0;
	}
	
	void Path::checkPath(Path& path)
	{
		
	}
}

#endif
