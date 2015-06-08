#ifdef __linux

// implementation for Linux

#include "../gfs.hpp"

#include <fstream>

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
		
		std::string pathStr = path;
		
		if(realpath(pathStr.c_str(), buf) != nullptr)
			return {buf};
		
		return path;
	}
	
	unsigned int hardLinkCount(const Path& path)
	{
		if(!path)
			return 0;
		
		struct stat st;
		
		std::string pathStr = path;
		
		if(!lstat(pathStr.c_str(), &st))
			return st.st_nlink;
		
		return 0;
	}
	
	PathContents contents(const Path& path, bool hidden)
	{
		if(!path || path.type() != Path::Type::Directory)
			return {};
		
		DIR* dir = nullptr;
		struct dirent* entry = nullptr;
		
		std::string pathStr = path;
		
		dir = opendir(pathStr.c_str());
		
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
		if(makeDir(path))
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
		
		std::string pathStr = path;
		
		return mkdir(pathStr.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == 0;	// user = rwx, group = rx, others = rx. 0755
	}
	
	bool makeFile(Path& path)
	{
		if(makeFile(path))
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
		
		std::string pathStr = path;
		
		return creat(pathStr.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != -1;	// user = rw, group = r, others = r: 0644
	}
	
	bool erase(Path& path)
	{
		if(erase(path))
		{
			Path::checkPath(path, true);
			
			return true;
		}
		
		return false;
	}
	
	bool erase(const Path& path)
	{
		if(!path)
			return false;
			
		std::string pathStr = path;
		
		return remove(pathStr.c_str()) == 0;
	}
	
	bool copy(const Path& src, Path& dest)
	{
		if(copy(src, dest))
		{
			Path::checkPath(dest, true);
			
			return true;
		}
		
		return false;
	}
	
	bool copy(const Path& src, const Path& dest)
	{
		if(!src || dest)
			return false;
		
		std::ifstream fin(src, std::ios::binary);
		std::ofstream fout(dest, std::ios::binary);
		
		if(!fin || !fout)
			return false;
		
		// 8K: this (pretty much) ensures the buffer will fit in L1 cache,
		// keeping this fairly performant.
		constexpr int BYTES_TO_READ = 8 * 1024;
		
		char buffer[BYTES_TO_READ];
		
		while(fin.read(buffer, BYTES_TO_READ))
		{
			auto bytesToWrite = fin.gcount();
			fout.write(buffer, bytesToWrite);
		}
		
		return true;
	}

	bool move(Path& src, Path& dest)
	{
		if(move(src, dest))
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
			
		std::string srcStr = src;
		std::string destStr = dest;
		
		return rename(srcStr.c_str(), destStr.c_str()) == 0;
	}
}

#endif
