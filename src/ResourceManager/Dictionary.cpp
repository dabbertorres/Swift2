#include "Dictionary.hpp"

#include <fstream>

namespace swift
{
	Dictionary::Dictionary(const std::string& file)
	{
		std::ifstream fin;
		fin.open(file);
		dictionary.emplace("NotFound", "Key not found");
		
		while(fin.good())
		{
			std::string temp;
			std::getline(fin, temp);
			dictionary.emplace(temp.substr(0, temp.find_first_of(' ')), temp.substr(temp.find_first_of('\"') + 1, temp.find_last_of('\"') - temp.find_first_of('\"') - 1));
		}
		
		fin.close();
	}

	Dictionary::~Dictionary()
	{
	}
	
	const std::string& Dictionary::getString(const std::string& key)
	{
		auto value = dictionary.find(key);
		if(value == dictionary.end())
			return dictionary["NotFound"];
		return value->second;
	}
}
