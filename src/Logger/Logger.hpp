#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>

#include "FileSystem/gfs.hpp"

namespace swift
{
	class Logger
	{
		public:
			template<typename T>
			Logger& operator<<(const T& t);
			
			static Logger& get();
			
			static bool setFile(const gfs::Path& path);

		private:
			Logger();
			~Logger();

			// Make it Non Copyable
			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;
			
			static Logger self;
			
			std::ofstream fout;

			unsigned int warnings;
			unsigned int errors;
	};

	template<typename T>
	Logger& Logger::operator<<(const T& t)
	{
		if(fout)
		{
			fout << t;
		}
		
		return *this;
	}
}

#endif // LOGGER_HPP
