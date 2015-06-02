#ifndef GFS_HPP
#define GFS_HPP

#include "Path.hpp"

#include <vector>

namespace gfs
{
	using PathContents = std::vector<Path>;
	
	// returns a Path to the current working directory
	Path workingDir();
	
	// returns a Path to the running executable
	Path selfPath();
	
	// returns a Path to the current user's home directory
	Path userHome();
	
	// given a Path that is a symlink, returns the target of the symlink
	// if the file does not exist, or is not a symlink, returns the given path
	Path readSymlink(const Path& path);
	
	// returns the number of hard links to the given path's inode
	unsigned int hardLinkCount(const Path& path);
	
	// returns a PathContents (std::vector<Path>)
	// if the given Path is a directory, the vector is filled with it's children
	// otherwise, returns an empty vector
	PathContents contents(const Path& path, bool hidden = false);
	
	// returns a bool on success of creating a directory at the given Path
	// first case modifies the given Path on success
	bool makeDir(Path& path);
	bool makeDir(const Path& path);
	
	// returns a bool on success of creating a file at the given Path
	// first case modifies the given Path on success
	bool makeFile(Path& path);
	bool makeFile(const Path& path);
	
	// returns a bool on success of deleting the file at the given Path
	// first case modifies the given Path on success
	bool remove(Path& path);
	bool remove(const Path& path);
	
	// returns a bool on success of copying the src Path to the dest Path
	// first case modifies the dest Path on success
	bool copy(const Path& src, Path& dest);
	bool copy(const Path& src, const Path& dest);
	
	// returns a bool on success of moving the src Path to the dest Path
	// first case modifies the given Paths on success
	bool move(Path& src, Path& dest);
	bool move(const Path& src, const Path& dest);
}

#endif	// GFS_HPP
