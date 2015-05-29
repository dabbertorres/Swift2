#ifdef __linux

// implementation for Linux

#include "../gfs.hpp"

#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace gfs
{
	Path workingDir()
	{
		char buf[PATH_MAX];
		
		if(getcwd(buf, PATH_MAX) != nullptr)
			return {buf};
		
		return {};
	}
	
	Path selfPath()
	{
		char buf[PATH_MAX];
		
		std::size_t rSize = readlink("/proc/self/exe", buf, PATH_MAX);
		
		if(rSize == static_cast<std::size_t>(-1))
			return {};
		
		return {{buf, rSize}};
	}
	
	Path userHome()
	{
		char* buf = std::getenv("HOME");
		
		if(buf != nullptr)
			return {buf};
		
		return {};
	}
	
	Path readSymlink(const Path& path)
	{
		if(!path || path.type() != Path::Type::SymLink)
			return path;
		
		char buf[PATH_MAX];
		
		if(realpath(path, buf) != nullptr)
			return {buf};
		
		return path;
	}
	
	unsigned int hardLinkCount(const Path& path)
	{
		if(!path)
			return 0;
		
		struct stat st;
		
		if(!lstat(path, &st))
			return st.st_nlink;
		
		return 0;
	}
	
	PathContents contents(const Path& path, bool hidden)
	{
		if(!path || path.type() != Path::Type::Directory)
			return {};
		
		DIR* dir = nullptr;
		struct dirent* entry = nullptr;
		
		dir = opendir(path);
		
		if(!dir)
			return {};
		
		PathContents children;
		
		while((entry = readdir(dir)))
		{
			std::string fname = entry->d_name;
			
			if(fname != "." && fname != ".." && ((fname.front() != '.' && fname.back() != '~') || hidden))
				children.emplace_back(path + fname);
		}
		
		closedir(dir);
		
		return children;
	}
	
	bool makeDir(Path& path)
	{
		if(path)
			return false;
		
		if(!mkdir(path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH))	// user = rwx, group = rx, others = rx. 0755
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
		
		return !mkdir(path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}
	
	bool makeFile(Path& path)
	{
		if(path)
			return false;
		
		if(creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != -1)	// user = rw, group = r, others = r. 0644
		{
			Path::checkPath(path, true);
			
			return true;
		}
		
		return false;
	}
	
	bool makeFile(const Path& path)
	{
		if(path)
			return false;
		
		return creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != -1;
	}
	
	bool remove(Path& path)
	{
		if(!path)
			return false;
		
		if(!remove(path))
		{
			Path::checkPath(path, true);
			
			return true;
		}
		
		return false;
	}
	
	bool remove(const Path& path)
	{
		if(!path)
			return false;
		
		return !remove(path);
	}
	
//	bool copy(const Path& src, Path& dest)
//	{
//		if(!src || dest)
//			return false;
//		
//		
//	}
	
//	bool copy(const Path& src, const Path& dest)
//	{
//		
//	}

	bool move(Path& src, Path& dest)
	{
		if(!src || dest)
			return false;
		
		if(!rename(src, dest))
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
		
		return !rename(src, dest);
	}
}

#endif
