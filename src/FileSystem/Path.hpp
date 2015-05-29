#ifndef GFS_PATH_HPP
#define GFS_PATH_HPP

#include <chrono>
#include <string>

namespace gfs
{
	class Path
	{
		friend bool makeDir(Path& path);
		friend bool makeFile(Path& path);
		friend bool remove(Path& path);
//		friend bool copy(const Path& src, Path& dest);
		friend bool move(Path& src, Path& dest);
		
		public:
			enum class Type
			{
				File,
				Directory,
				Character,
				Block,
				Pipe,
				SymLink,
				Socket,
				Unknown,
			};
			
			/* permissions */
			// implementation required
			static const unsigned int OwnerAll;
			static const unsigned int OwnerRead;
			static const unsigned int OwnerWrite;
			static const unsigned int OwnerExec;
			
			static const unsigned int GroupAll;
			static const unsigned int GroupRead;
			static const unsigned int GroupWrite;
			static const unsigned int GroupExec;
			
			static const unsigned int OthersAll;
			static const unsigned int OthersRead;
			static const unsigned int OthersWrite;
			static const unsigned int OthersExec;
			
			Path();
			Path(const std::string& path, bool resolveSymLink = true);
			Path(const char* path, bool resolveSymLink = true);
			
			/* queries */
			bool exists();
			bool exists() const;
			Type type() const;
			unsigned int permissions() const;
			
			std::chrono::system_clock::time_point lastAccess() const;	// implementation required
			std::chrono::system_clock::time_point lastModify() const;	// implementation required
			
			unsigned long int fileSize() const;							// implementation required
			
			Path parent() const;
			std::string filename() const;
			std::string name() const;
			std::string extension() const;
			
			/* casts */
			operator std::string() const;
			operator const char*() const;
			
			// returns true if the Path exists
			operator bool() const;
			
			/* operations */
			Path& operator=(const Path& other);
			Path& operator=(const std::string& other);
			Path& operator=(const char* other);
			
			Path& operator+=(const Path& other);
			Path& operator+=(const std::string& other);
			Path& operator+=(const char* other);
			
			Path& operator/=(const Path& other);
			Path& operator/=(const std::string& other);
			Path& operator/=(const char* other);
			
			friend Path operator+(const Path& lhs, const Path& rhs);
			friend Path operator+(const std::string& lhs, const Path& rhs);
			friend Path operator+(const Path& lhs, const std::string& rhs);
			friend Path operator+(const char* lhs, const Path& rhs);
			friend Path operator+(const Path& lhs, const char* rhs);
			
			friend Path operator/(const Path& lhs, const Path& rhs);
			friend Path operator/(const std::string& lhs, const Path& rhs);
			friend Path operator/(const Path& lhs, const std::string& rhs);
			friend Path operator/(const char* lhs, const Path& rhs);
			friend Path operator/(const Path& lhs, const char* rhs);
			
			/* comparisons */
			friend bool operator==(const Path& lhs, const Path& rhs);
			friend bool operator!=(const Path& lhs, const Path& rhs);
			
			/* output */
			friend std::ostream& operator<<(std::ostream& os, const Path& path);

		private:
			static void checkPath(Path& path, bool resolveSymLink);	// implementation required
		
			std::string pathStr;
			Type typeVal;
			bool existsVal;
			unsigned int permissionsVal;
	};
}

#endif // GFS_PATH_HPP
