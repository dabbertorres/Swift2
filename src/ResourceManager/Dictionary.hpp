#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <map>

namespace swift
{
	class Dictionary
	{
		public:
			Dictionary(const std::string& file);
			~Dictionary();
			
			const std::string& getString(const std::string& key);

		private:
			std::map<std::string, std::string> dictionary;
	};
}

#endif // DICTIONARY_HPP
