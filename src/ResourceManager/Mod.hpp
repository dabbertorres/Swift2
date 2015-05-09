#ifndef MOD_HPP
#define MOD_HPP

/*
 * Mod objects should not hold actual data. They should only hold strings of filenames
 * and the mod's info.txt
 */

#include <string>
#include <vector>

namespace swift
{
	class Mod
	{
		public:
			Mod() = default;
			Mod(const std::string& n, const std::string& v, const std::string& a, const std::string& d);
			~Mod() = default;

			void addFile(const std::string& f);

			const std::string& getName() const;
			const std::string& getVersion() const;
			const std::string& getAuthor() const;
			const std::string& getDescription() const;
			const std::vector<std::string>& getFiles() const;
			
			bool isActive() const;

			void setName(const std::string& n);
			void setVersion(const std::string& v);
			void setAuthor(const std::string& a);
			void setDescription(const std::string& d);
			
			void setActive(bool a);

			friend bool operator ==(const Mod& lhs, const Mod& rhs);
			friend bool operator !=(const Mod& lhs, const Mod& rhs);

		private:
			std::string name;
			std::string version;
			std::string author;
			std::string description;

			std::vector<std::string> files;
			
			bool active;
	};
}

#endif // MOD_HPP
