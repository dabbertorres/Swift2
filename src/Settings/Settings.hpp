#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

namespace swift
{
	class Settings
	{
		public:
			Settings();
			~Settings();

			// Accepts the file name, f
			// Returns true if file was loaded,
			// false if not
			bool loadFile(const std::string& f);

			bool saveToFile() const;

			bool isChanged() const;

			// Accepts the setting name, setting
			// and value, the variable to store the value of setting in
			// Returns true if setting was found,
			// false if not
			bool get(const std::string& setting, std::string& value) const;
			bool get(const std::string& setting, bool& value) const;
			bool get(const std::string& setting, char& value) const;
			bool get(const std::string& setting, int& value) const;
			bool get(const std::string& setting, unsigned& value) const;
			bool get(const std::string& setting, float& value) const;

			// Accepts the setting name, setting
			// and value, the variable to set the value of setting to
			bool set(const std::string& setting, std::string& value);
			bool set(const std::string& setting, bool& value);
			bool set(const std::string& setting, char& value);
			bool set(const std::string& setting, int& value);
			bool set(const std::string& setting, unsigned& value);
			bool set(const std::string& setting, float& value);

		private:
			int findIndex(const std::string& setting) const;
			bool read();
			bool write() const;

			bool changed;
			std::string file;
			std::vector< std::pair<std::string, std::string> > data;
	};
}

#endif // SETTINGS_HPP
