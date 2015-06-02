#ifdef _WIN32

#include "../Path.hpp"

#include <ctime>
#include <windows.h>

std::time_t winFileTimeToTimeT(const FILETIME& ft)
{
	static const unsigned long long WINDOWS_TICK = 10000000LL;
	static const unsigned long long SEC_TO_UNIX_EPOCH = 11644473600LL;

	ULARGE_INTEGER ull;
	ull.LowPart = ft.dwLowDateTime;
	ull.HighPart = ft.dwHighDateTime;

	return ull.QuadPart / WINDOWS_TICK - SEC_TO_UNIX_EPOCH;
}

namespace gfs
{
	std::chrono::system_clock::time_point Path::lastAccess() const
	{
		WIN32_FILE_ATTRIBUTE_DATA data;

		if(existsVal && GetFileAttributesEx(pathStr.c_str(), GetFileExInfoStandard, &data))
		{
			std::time_t time = winFileTimeToTimeT(data.ftLastAccessTime);

			return std::chrono::system_clock::from_time_t(time);
		}

		return {};
	}
	
	std::chrono::system_clock::time_point Path::lastModify() const
	{
		WIN32_FILE_ATTRIBUTE_DATA data;

		if(existsVal && GetFileAttributesEx(pathStr.c_str(), GetFileExInfoStandard, &data))
		{
			std::time_t time = winFileTimeToTimeT(data.ftLastWriteTime);

			return std::chrono::system_clock::from_time_t(time);
		}

		return {};
	}
	
	unsigned long long int Path::fileSize() const
	{
		if(!existsVal)
			return 0;

		HANDLE file = CreateFile(*this, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		LARGE_INTEGER size;
		size.QuadPart = 0;
		GetFileSizeEx(file, &size);
		CloseHandle(file);

		return size.QuadPart;
	}
	
	void Path::checkPath(Path& path, bool resolveSymLink)
	{
		HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		DWORD attr = GetFileAttributes(path);
		DWORD type = GetFileType(file);

		if(file != INVALID_HANDLE_VALUE && attr != INVALID_FILE_ATTRIBUTES)
		{
			switch(type)
			{
				case FILE_TYPE_CHAR:
					path.typeVal = Type::Character;
					break;
				case FILE_TYPE_DISK:
					path.typeVal = Type::Block;
					break;
				case FILE_TYPE_PIPE:
					path.typeVal = Type::Pipe;
					break;
				default:
					path.typeVal = Type::Unknown;
					break;
			}

			if((attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
				path.typeVal = Type::Directory;
			else if((attr & FILE_ATTRIBUTE_REPARSE_POINT) != 0)
				path.typeVal = Type::SymLink;
			else
				path.typeVal = Type::File;

			// ignore permissions on Windows... it's... convoluted. for now at least

			if(path.typeVal != Type::SymLink || resolveSymLink)
			{
				// get absolute path
				char buf[MAX_PATH];

				std::size_t rSize = GetFinalPathNameByHandle(file, buf, MAX_PATH, FILE_NAME_OPENED);

				path.pathStr = {buf, rSize};
			}

			// get rid of the unicode stuff on the front of string
			std::size_t driveColon = path.pathStr.find(':');
			if(driveColon != std::string::npos)
				path.pathStr.erase(0, driveColon - 1);

			// add directory divider to end of directory Paths
			if(path.typeVal == Type::Directory)
				path.pathStr += '\\';

			path.existsVal = true;
		}
		else
		{
			path.typeVal = Type::Unknown;
			path.existsVal = false;
		}
	}
}

#endif
