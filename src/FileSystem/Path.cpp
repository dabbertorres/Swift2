#include "Path.hpp"

#include <regex>

// implementation file for non-OS specific functions

namespace gfs
{
	Path userHome();	// forward declaration
}

std::string normalizePath(const std::string& path)
{
	const std::regex slashes("([\\/\\\\]{2,})");	// shortens to: ([\/\\]{2,})
	
	return std::regex_replace(path, slashes, "/");
}

void fixUserHome(std::string& path)
{
	if(path.front() == '~')
		path.replace(0, 1, static_cast<const char*>(gfs::userHome()));
}

namespace gfs
{
	Path::Path()
	:	pathStr(""),
		typeVal(Type::Unknown),
		existsVal(false),
		permissionsVal(0)
	{}

	Path::Path(const std::string& path, bool resolveSymLink)
	:	pathStr(normalizePath(path)),
		typeVal(Type::Unknown),
		existsVal(false),
		permissionsVal(0)
	{
		fixUserHome(pathStr);
		checkPath(*this, resolveSymLink);
	}

	Path::Path(const char* path, bool resolveSymLink)
	:	pathStr(normalizePath(path)),
		typeVal(Type::Unknown),
		existsVal(false),
		permissionsVal(0)
	{
		fixUserHome(pathStr);
		checkPath(*this, resolveSymLink);
	}

	bool Path::exists()
	{
		checkPath(*this, true);
		return existsVal;
	}

	bool Path::exists() const
	{
		return existsVal;
	}

	Path::Type Path::type() const
	{
		return typeVal;
	}
	
	unsigned int Path::permissions() const
	{
		return permissionsVal;
	}
	
	Path Path::parent() const
	{
		if(pathStr.empty())
			return {};
			
		char last = pathStr.back();
		
		std::size_t lastDirDiv;
		
		if(last != '/' && last != '\\')
			lastDirDiv = pathStr.find_last_of("/\\");
		else
			lastDirDiv = pathStr.find_last_of("/\\", pathStr.size() - 2);
		
		if(pathStr.front() != '.')
		{
			if(lastDirDiv != std::string::npos)
				return {pathStr.substr(0, lastDirDiv + 1)};
		}
		else
		{
			if(lastDirDiv != std::string::npos)
				return {pathStr.substr(0, lastDirDiv + 1) + "../"};
		}
		
		return *this;
	}
	
	std::string Path::filename() const
	{
		if(pathStr.empty())
			return "";
		
		char last = pathStr.back();
		
		std::size_t lastDirDiv;
		
		if(last != '/' && last != '\\')
			lastDirDiv = pathStr.find_last_of("/\\");
		else
			lastDirDiv = pathStr.find_last_of("/\\", pathStr.size() - 2);
			
		if(lastDirDiv != std::string::npos)
			return pathStr.substr(lastDirDiv + 1);
		
		return pathStr;
	}
	
	std::string Path::name() const
	{
		if(pathStr.empty())
			return "";
		
		char last = pathStr.back();
		
		std::size_t lastDirDiv;
		
		if(last != '/' && last != '\\')
			lastDirDiv = pathStr.find_last_of("/\\");
		else
			lastDirDiv = pathStr.find_last_of("/\\", pathStr.size() - 2);
		
		std::size_t extDot = pathStr.find_last_of('.');
		
		if(lastDirDiv != std::string::npos && extDot != std::string::npos)
			return pathStr.substr(lastDirDiv + 1, extDot - lastDirDiv - 1);
		else if(lastDirDiv != std::string::npos)
			return pathStr.substr(lastDirDiv + 1);
		
		return pathStr;
	}
	
	std::string Path::extension() const
	{
		if(pathStr.empty())
			return "";
		
		std::size_t lastDirDiv = pathStr.find_last_of("/\\");
		std::size_t extDot = pathStr.find_last_of('.');
		
		if(lastDirDiv > extDot)
			return "";
		
		if(extDot != std::string::npos)
			return pathStr.substr(extDot + 1);
		
		return "";
	}
	
	Path::operator std::string() const
	{
		return pathStr;
	}

	Path::operator const char*() const
	{
		return pathStr.c_str();
	}
	
	Path::operator bool() const
	{
		return existsVal;
	}
	
	Path& Path::operator=(const Path& other)
	{
		this->pathStr = other.pathStr;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator=(const std::string& other)
	{
		this->pathStr = other;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator=(const char* other)
	{
		this->pathStr = other;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator+=(const Path& other)
	{
		this->pathStr += other.pathStr;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator+=(const std::string& other)
	{
		this->pathStr += other;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator+=(const char* other)
	{
		this->pathStr += other;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator/=(const Path& other)
	{
		this->pathStr += '/' + other.pathStr;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator/=(const std::string& other)
	{
		this->pathStr += '/' + other;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path& Path::operator/=(const char* other)
	{
		this->pathStr += '/' + other;
		checkPath(*this, true);
		
		return *this;
	}
	
	Path operator+(const Path& lhs, const Path& rhs)
	{
		return {lhs.pathStr + rhs.pathStr};
	}
	
	Path operator+(const std::string& lhs, const Path& rhs)
	{
		return {lhs + rhs.pathStr};
	}
	
	Path operator+(const Path& lhs, const std::string& rhs)
	{
		return {lhs.pathStr + rhs};
	}
	
	Path operator+(const char* lhs, const Path& rhs)
	{
		return {lhs + rhs.pathStr};
	}
	
	Path operator+(const Path& lhs, const char* rhs)
	{
		return {lhs.pathStr + rhs};
	}
	
	Path operator/(const Path& lhs, const Path& rhs)
	{
		return {lhs.pathStr + '/' + rhs.pathStr};
	}
	
	Path operator/(const std::string& lhs, const Path& rhs)
	{
		return {lhs + '/' + rhs.pathStr};
	}
	
	Path operator/(const Path& lhs, const std::string& rhs)
	{
		return {lhs.pathStr + '/' + rhs};
	}
	
	Path operator/(const char* lhs, const Path& rhs)
	{
		return {lhs + '/' + rhs.pathStr};
	}
	
	Path operator/(const Path& lhs, const char* rhs)
	{
		return {lhs.pathStr + '/' + rhs};
	}
	
	bool operator==(const Path& lhs, const Path& rhs)
	{
		return lhs.pathStr == rhs.pathStr;
	}
	
	bool operator!=(const Path& lhs, const Path& rhs)
	{
		return !(lhs.pathStr == rhs.pathStr);
	}
	
	std::ostream& operator<<(std::ostream& os, const Path& path)
	{
		os << path.pathStr;
		
		return os;
	}
}
