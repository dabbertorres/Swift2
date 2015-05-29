#ifndef SWIFT_MOD_HPP
#define SWIFT_MOD_HPP

/*
 * Mod objects do not hold actual data. They only hold information and their path
 */

#include <string>

#include "FileSystem/gfs.hpp"

namespace swift
{
	class Mod
	{
		public:
			Mod(const gfs::Path& p);
			Mod(const gfs::Path& p, const std::string& n, const std::string& v, const std::string& a, const std::string& d);
			~Mod() = default;

			void addFile(const gfs::Path& f);

			const std::string& getName() const;
			const std::string& getVersion() const;
			const std::string& getAuthor() const;
			const std::string& getDescription() const;
			const gfs::Path& getFolder() const;
			
			bool isActive() const;

			void setName(const std::string& n);
			void setVersion(const std::string& v);
			void setAuthor(const std::string& a);
			void setDescription(const std::string& d);
			
			void setActive(bool a);

			friend bool operator==(const Mod& lhs, const Mod& rhs);
			friend bool operator!=(const Mod& lhs, const Mod& rhs);

		private:
			gfs::Path folder;
			
			std::string name;
			std::string version;
			std::string author;
			std::string description;
			
			bool active;
	};
}

#endif // SWIFT_MOD_HPP
