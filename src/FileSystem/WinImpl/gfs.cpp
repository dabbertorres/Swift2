#ifdef _WIN32

#include "../gfs.hpp"

#include <limits>
#include <windows.h>

namespace gfs
{
	Path cwd()
	{
		char buffer[PATH_MAX];
		
		GetModuleFileName(NULL, buffer, PATH_MAX);
		
		return Path(buffer);
	}
}

#endif
