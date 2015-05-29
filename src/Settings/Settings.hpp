#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "MessageSystem/Observable.hpp"

#include "FileSystem/gfs.hpp"

#include <string>
#include <unordered_map>

namespace swift
{
	class Settings : public Observable<std::string>
	{
		public:
			Settings();
			~Settings() = default;

			// Accepts the file name, f
			// Returns true if file was loaded,
			// false if not
			bool loadFile(const gfs::Path& f);
			
			// returns true for sucessful writing
			bool saveToFile() const;
			
			// returns true if the data has been changed
			bool isChanged() const;

			// Accepts the setting name, setting
			// and value, the variable to store the value of setting in
			// Returns true if setting was found,
			// false if not
			template<typename T>
			bool get(const std::string& setting, T& value) const;

			// Accepts the setting name, setting
			// and value, the variable to set the value of setting to
			// if the setting does not exist already, it is created
			template<typename T>
			void set(const std::string& setting, const T& value);

		private:
			bool read();
			bool write() const;

			bool changed;
			gfs::Path file;
			std::unordered_map<std::string, std::string> data;
	};
}

#endif // SETTINGS_HPP
