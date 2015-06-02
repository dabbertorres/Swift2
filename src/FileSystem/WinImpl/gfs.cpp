#ifdef _WIN32

#include "../gfs.hpp"

#include <windows.h>
#include <direct.h>
#include <Shlobj.h>

namespace gfs
{
	Path workingDir()
	{
		char buf[MAX_PATH];

		if(_getcwd(buf, MAX_PATH) != nullptr)
			return{buf};

		return {};
	}

	Path selfPath()
	{
		char buf[MAX_PATH];

		std::size_t rSize = GetModuleFileName(NULL, buf, MAX_PATH);

		if(!rSize)
			return {};

		std::string path{buf, rSize};

		// visual studio seems to interpret "{{buf, rSize}}" as passing two arguments
		// to Path's constructor, not, creating a string, and then passing that to Path
		// hence the string creation above

		return {path};
	}

	Path userHome()
	{
		wchar_t* wbuf = nullptr;

		if(SHGetKnownFolderPath(FOLDERID_Profile, KF_FLAG_NO_ALIAS, NULL, &wbuf) != S_OK)
			return {};

		char buf[MAX_PATH] {0};

		// comvert wide characters to multibyte characters
		std::size_t rSize;
		wcstombs_s(&rSize, buf, MAX_PATH, wbuf, MAX_PATH);

		CoTaskMemFree(wbuf);	// windows allocates wbuf for us, gotta free it

		if(buf != nullptr && rSize != 0)
		{
			std::string path{buf, rSize};
			return {path};
		}

		return {};
	}

	Path readSymlink(const Path& path)
	{
		if(!path)
			return 0;

		HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_REPARSE_POINT, NULL);

		char buf[MAX_PATH];

		std::size_t rSize = GetFinalPathNameByHandle(file, buf, MAX_PATH, FILE_NAME_OPENED);

		CloseHandle(file);

		if(rSize != 0)
		{
			std::string pathStr{buf, rSize};

			// get rid of the unicode stuff on the front of string
			std::size_t driveColon = pathStr.find(':');
			if(driveColon != std::string::npos)
				pathStr.erase(0, driveColon - 1);

			return {pathStr, false};
		}
		
		return {};
	}

	unsigned int hardLinkCount(const Path& path)
	{
		if(!path)
			return 0;

		HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		FILE_STANDARD_INFO info;

		unsigned int numLinks = 0;

		if(GetFileInformationByHandleEx(file, FileStandardInfo, &info, sizeof(FILE_STANDARD_INFO)) != 0)
			numLinks = info.NumberOfLinks;

		CloseHandle(file);

		return numLinks;
	}

	PathContents contents(const Path& path, bool hidden)
	{
		if(!path)
			return {};
		
		PathContents contents;

		WIN32_FIND_DATA pathData;

		std::string pathStr(path);

		// FindFirstFile and FindNextFile don't like directory dividers at the end of filenames
		if(pathStr.back() == '\\' || pathStr.back() == '/')
			pathStr = pathStr.substr(0, pathStr.size() - 1);

		HANDLE file = FindFirstFile(pathStr.c_str(), &pathData);

		if(file == INVALID_HANDLE_VALUE)
			return contents;
		
		do
		{
			if(pathData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// don't include the current dir and parent dirs
				if(pathData.cFileName == "." || pathData.cFileName == ".." || (!hidden && pathData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
					continue;
			}

			contents.emplace_back(path / pathData.cFileName);
		}
		while(FindNextFile(file, &pathData));

		FindClose(file);

		return contents;
	}

	bool makeDir(Path& path)
	{
		if(path)
			return false;

		if(CreateDirectory(path, NULL))
		{
			Path::checkPath(path, true);
			return true;
		}

		return false;
	}

	bool makeDir(const Path& path)
	{
		if(path)
			return false;

		return CreateDirectory(path, NULL) != 0;
	}

	bool makeFile(Path& path)
	{
		if(path)
			return false;

		HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

		bool result = file != INVALID_HANDLE_VALUE;
		Path::checkPath(path, true);
		CloseHandle(file);

		return result;
	}

	bool makeFile(const Path& path)
	{
		if(path)
			return false;

		HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		bool result = file != INVALID_HANDLE_VALUE;
		CloseHandle(file);

		return result;
	}

	bool remove(Path& path)
	{
		if(!path)
			return false;

		if(path.type() == Path::Type::File)
		{
			if(DeleteFile(path))
			{
				Path::checkPath(path, true);
				return true;
			}
		}
		else if(path.type() == Path::Type::Directory)
		{
			if(RemoveDirectory(path))
			{
				Path::checkPath(path, true);
				return true;
			}
		}

		return false;
	}

	bool remove(const Path& path)
	{
		if(!path)
			return false;

		if(path.type() == Path::Type::File)
			return DeleteFile(path) != 0;
		else if(path.type() == Path::Type::Directory)
			return RemoveDirectory(path) != 0;

		return false;
	}

	bool copy(const Path& src, Path& dest)
	{
		if(!src || dest)
			return false;

		if(CopyFileEx(src, dest, NULL, NULL, false, COPY_FILE_COPY_SYMLINK))
		{
			Path::checkPath(dest, false);
			return true;
		}

		return false;
	}

	bool copy(const Path& src, const Path& dest)
	{
		if(!src || dest)
			return false;

		return CopyFileEx(src, dest, NULL, NULL, false, COPY_FILE_COPY_SYMLINK) != 0;
	}

	bool move(Path& src, Path& dest)
	{
		if(!src || dest)
			return false;

		if(MoveFileEx(src, dest, MOVEFILE_WRITE_THROUGH))
		{
			Path::checkPath(src, true);
			Path::checkPath(dest, true);

			return true;
		}

		return false;
	}

	bool move(const Path& src, const Path& dest)
	{
		if(!src || dest)
			return false;

		return MoveFileEx(src, dest, MOVEFILE_WRITE_THROUGH) != 0;
	}
}

#endif
