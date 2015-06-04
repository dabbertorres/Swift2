#include "Settings.hpp"

#include <sstream>
#include <fstream>

#include "Logger/Logger.hpp"

namespace swift
{
	Settings::Settings()
	:	changed(false)
	{}

	bool Settings::loadFromFile(const gfs::Path& f)
	{
		data.clear();
		file = f;
		
		return read();
	}

	bool Settings::saveToFile() const
	{
		if(changed)
		{
			return write();
		}
		
		return true;
	}

	bool Settings::isChanged() const
	{
		return changed;
	}
	
	template<>
	bool Settings::get(const std::string& setting, std::string& value) const
	{
		if(data.find(setting) != data.end())
		{
			value = data.at(setting);
			return true;
		}
		
		return false;
	}

	template<>
	bool Settings::get(const std::string& setting, bool& value) const
	{
		if(data.find(setting) != data.end())
		{
			std::string val = data.at(setting);
			value = (val == "true" || val == "1");
			return true;
		}
		
		return false;
	}

	template<>
	bool Settings::get(const std::string& setting, int& value) const
	{
		if(data.find(setting) != data.end())
		{
			value = std::stoi(data.at(setting));
			return true;
		}
		
		return false;
	}

	template<>
	bool Settings::get(const std::string& setting, unsigned int& value) const
	{
		if(data.find(setting) != data.end())
		{
			value = std::stoi(data.at(setting));
			return true;
		}
		
		return false;
	}

	template<>
	bool Settings::get(const std::string& setting, float& value) const
	{
		if(data.find(setting) != data.end())
		{
			value = std::stof(data.at(setting));
			return true;
		}
		
		return false;
	}

	template<>
	void Settings::set(const std::string& setting, const std::string& value)
	{
		if(data.find(setting) != data.end())
		{
			data[setting] = value;
		}
		else
		{
			data.emplace(setting, value);
		}
		
		changed = true;
	}

	template<>
	void Settings::set(const std::string& setting, const bool& value)
	{
		if(data.find(setting) != data.end())
		{
			data[setting] = value ? "true" : "false";
		}
		else
		{
			data.emplace(setting, value ? "true" : "false");
		}
		
		changed = true;
	}

	template<>
	void Settings::set(const std::string& setting, const int& value)
	{
		if(data.find(setting) != data.end())
		{
			data[setting] = std::to_string(value);
		}
		else
		{
			data.emplace(setting, std::to_string(value));
		}
		
		changed = true;
	}

	template<>
	void Settings::set(const std::string& setting, const unsigned int& value)
	{
		if(data.find(setting) != data.end())
		{
			data[setting] = std::to_string(value);
		}
		else
		{
			data.emplace(setting, std::to_string(value));
		}
		
		changed = true;
	}

	template<>
	void Settings::set(const std::string& setting, const float& value)
	{
		if(data.find(setting) != data.end())
		{
			data[setting] = std::to_string(value);
		}
		else
		{
			data.emplace(setting, std::to_string(value));
		}
		
		changed = true;
	}

	bool Settings::read()
	{
		std::ifstream fin(file);

		if(!fin)
		{
			Logger::get() << "[ERROR]: Unable to open settings file: \"" << file << "\" for reading.\n";
			return false;
		}
		
		std::string line = "";
		std::string setting = "";
		std::string value = "";
		
		while(std::getline(fin, line))
		{
			// skip empty lines and comments (lines starting with '#')
			if(!line.empty() && line[0] != '#')
			{
				std::stringstream ss(line);
				
				std::string dump;
				
				ss >> setting >> dump;
				
				std::string temp = "";
				std::getline(ss, temp);	// get rest of line
				
				// add characters until we reach a newline or a comment
				std::size_t i = 0;
				while(i < temp.size() && temp[i] != '\n' && temp[i] != '#')
				{
					value += temp[i];
					++i;
				}
				
				// strip leading and trailing spaces
				while(value.front() == ' ')
					value.erase(value.begin());
				
				while(value.back() == ' ')
					value.erase(value.end() - 1);
			}
			else	// save comments and empty lines for writing later
			{
				setting = line;
			}
			
			data.emplace(setting, value);
			
			// empty the strings
			setting.clear();
			value.clear();
		}
		
		return true;
	}
	
	bool Settings::write() const
	{
		std::ofstream fout(file);
		
		if(!fout)
		{
			Logger::get() << "[ERROR]: Unable to open settings file: \"" << file << "\" for writing.\n";
			return false;
		}
		
		for(auto& sv : data)
		{
			if(sv.first.empty() || sv.first[0] == '#')
			{
				fout << sv.first << '\n';
			}
			else
			{
				fout << sv.first << " = " << sv.second << '\n';
			}
		}
		
		return true;
	}
}
