#include "Settings.hpp"

#include <sstream>
#include <fstream>

#include "Logger/Logger.hpp"

namespace swift
{
	Settings::Settings()
	:	changed(false)
	{}

	bool Settings::loadFile(const gfs::Path& f)
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
			value = val == "true" || val != "0";
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
	}

	bool Settings::read()
	{
		std::string fileStr = file;
		std::ifstream fin(fileStr);

		if(!fin)
		{
			log << "Error: Unable to open settings file: \"" << file << "\" for reading.\n";
			return false;
		}
		
		std::string line;
		std::string setting;
		std::string value;

		while(std::getline(fin, line))
		{
			// skip empty lines and comments (lines starting with '#')
			if(!line.empty() && line[0] != '#')
			{
				std::stringstream ss(line);
				
				std::string dump;
				
				ss >> setting;
				ss >> dump;
				ss >> value;
			}
			else if(!line.empty())
			{
				// save comments for writing later
				setting = line;
				value = "";
			}
			
			data.emplace(setting, value);
		}
		
		return true;
	}
	
	bool Settings::write() const
	{
		std::string fileStr = file;
		std::ofstream fout(fileStr);
		
		if(!fout)
		{
			log << "Error: Unable to open settings file: \"" << file << "\" for writing.\n";
			return false;
		}
		
		for(auto& sv : data)
		{
			if(sv.first[0] == '#')
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
