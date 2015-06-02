#ifdef __linux

// implementation for Linux

#include "../Path.hpp"

#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace gfs
{
	const unsigned int Path::OwnerAll = S_IRWXU;
	const unsigned int Path::OwnerRead = S_IRUSR;
	const unsigned int Path::OwnerWrite = S_IWUSR;
	const unsigned int Path::OwnerExec = S_IXUSR;
	
	const unsigned int Path::GroupAll = S_IRWXG;
	const unsigned int Path::GroupRead = S_IRGRP;
	const unsigned int Path::GroupWrite = S_IWGRP;
	const unsigned int Path::GroupExec = S_IXGRP;
	
	const unsigned int Path::OthersAll = S_IRWXO;
	const unsigned int Path::OthersRead = S_IROTH;
	const unsigned int Path::OthersWrite = S_IWOTH;
	const unsigned int Path::OthersExec = S_IXOTH;
	
	std::chrono::system_clock::time_point Path::lastAccess() const
	{
		struct stat st;
		
		if(existsVal && !lstat(pathStr.c_str(), &st))
			return std::chrono::system_clock::from_time_t(st.st_atime);
		else
			return {};
	}
	
	std::chrono::system_clock::time_point Path::lastModify() const
	{
		struct stat st;
		
		if(existsVal && !lstat(pathStr.c_str(), &st))
			return std::chrono::system_clock::from_time_t(st.st_mtime);
		else
			return {};
	}
	
	unsigned long long int Path::fileSize() const
	{
		struct stat st;
		
		if(existsVal && !lstat(pathStr.c_str(), &st))
			return st.st_size;
		else
			return 0;
	}
	
	void Path::checkPath(Path& path, bool resolveSymLink)
	{
		struct stat st;
		
		if(!lstat(path.pathStr.c_str(), &st))
		{
			switch(st.st_mode & S_IFMT)
			{
				case S_IFSOCK:
					path.typeVal = Type::Socket;
					break;
				case S_IFLNK:
					path.typeVal = Type::SymLink;
					break;
				case S_IFREG:
					path.typeVal = Type::File;
					break;
				case S_IFBLK:
					path.typeVal = Type::Block;
					break;
				case S_IFDIR:
					path.typeVal = Type::Directory;
					break;
				case S_IFCHR:
					path.typeVal = Type::Character;
					break;
				case S_IFIFO:
					path.typeVal = Type::Pipe;
					break;
				default:
					path.typeVal = Type::Unknown;
					break;
			}

			if(!path.permissionsVal)
				path.permissionsVal += st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
			
			if(path.typeVal != Type::SymLink || resolveSymLink)
			{
				// get absolute path
				char buf[PATH_MAX];
				
				if(realpath(path.pathStr.c_str(), buf) != nullptr)
					path.pathStr = buf;
			}
			
			if(path.typeVal == Type::Directory)
				path.pathStr += "/";
	
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
