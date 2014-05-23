#include "Settings.hpp"

namespace swift
{
	Settings::Settings()
	{
		changed = false;
	}

	Settings::~Settings()
	{
		saveToFile();
	}

	bool Settings::loadFile(const std::string& f)
	{
		data.clear();
		file = f;
		return read();
	}

	bool Settings::saveToFile() const
	{
		if(changed)
			return write();
		return true;
	}

	bool Settings::isChanged() const
	{
		return changed;
	}

	bool Settings::get(const std::string& setting, std::string& value) const
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			value = data[i].second;
			return true;
		}
		return false;
	}

	bool Settings::get(const std::string& setting, bool& value) const
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			std::string temp = data[i].second;

			if(temp == "true" || temp == "1" || temp == "TRUE")
				value = true;
			else
				value = false;

			return true;
		}
		return false;
	}

	bool Settings::get(const std::string& setting, char& value) const
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			value = data[i].second[0];
			return true;
		}
		return false;
	}

	bool Settings::get(const std::string& setting, int& value) const
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			value = std::stoi(data[i].second);
			return true;
		}
		return false;
	}

	bool Settings::get(const std::string& setting, unsigned& value) const
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			value = std::stoi(data[i].second);
			return true;
		}
		return false;
	}

	bool Settings::get(const std::string& setting, float& value) const
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			value = std::stof(data[i].second);
			return true;
		}
		return false;
	}

	void Settings::set(const std::string& setting, std::string& value)
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			data[i].second = value;
		}
		changed = true;
	}

	void Settings::set(const std::string& setting, bool& value)
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			data[i].second = value ? "true" : "false";
		}
		changed = true;
	}

	void Settings::set(const std::string& setting, char& value)
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			data[i].second = value;
		}
		changed = true;
	}

	void Settings::set(const std::string& setting, int& value)
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			data[i].second = std::to_string(value);
		}
		changed = true;
	}
	
	void Settings::set(const std::string& setting, unsigned& value)
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			data[i].second = std::to_string(value);
		}
		changed = true;
	}

	void Settings::set(const std::string& setting, float& value)
	{
		int i = findIndex(setting);
		if(i > -1)
		{
			data[i].second = std::to_string(value);
		}
		changed = true;
	}

	int Settings::findIndex(const std::string& setting) const
	{
		for(size_t i = 0; i < data.size(); i++)
		{
			if(data[i].first[0] == '#')
				continue;
			else if(data[i].first == setting)
			{
				return i;
			}
		}
		return -1;
	}

	bool Settings::read()
	{
		std::ifstream in(file);

		if(!in.is_open())
			return false;

		std::string line, setting, value;

		while(!in.eof())
		{
			std::getline(in, line);

			if(line.size() > 0 && line[0] != '#')
			{
				size_t j = 0;
				size_t length = line.size();

				while(line[j] != ' ')
					j++;
					
				// start of 'setting' to (one before) first space is the 'setting' value
				setting = line.substr(0, j);

				while(line[j] == ' ' || line[j] == '=')
					j++;
					
				// start of 'value' is after the equal sign and any extra spaces
				int a = j;
				
				while(j < length && (line[j] != ' ' || line[j] != '\n' || line[j] != '#'))
					j++;
					
				// end of value is the last alphanumerisymbolic* char (except for '#')
				int b = j;
				
				value = line.substr(a, b);
			}
			else
			{
				// save comments
				setting = line;
				value = "";
			}

			data.push_back(make_pair(setting, value));
		}

		in.close();

		changed = false;

		return true;
	}

	bool Settings::write() const
	{
		std::ofstream out(file);

		if(!out.is_open())
		{
			std::cerr << "Error: Unable to open settings file: \"" << file << "\" for writing." << std::endl;
			return false;
		}

		for(size_t i = 0; i < data.size(); ++i)
		{
			if(data[i].first[0] == '#' || data[i].first[0] == 0)
				out << data[i].first << std::endl;
			else
				out << data[i].first << " = " << data[i].second << std::endl;
		}

		out.close();

		return true;
	}

	// alphanumerisymbolic = something that is a letter, number, or symbol
}
