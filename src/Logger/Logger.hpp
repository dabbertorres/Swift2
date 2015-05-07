#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

#include <SFML/System/Err.hpp>

namespace swift
{
	class Logger
	{
		public:
			explicit Logger(const std::string& header, const std::string& logFile = "../data/swift.log");
			~Logger();

			// Make it Non Copyable
			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;

			template<typename T>
			Logger& operator<<(const T& t);

		private:
			std::ofstream fout;

			unsigned int warnings;
			unsigned int errors;
	};

	template<typename T>
	Logger& Logger::operator<<(const T& t)
	{
		fout << t;

		return *this;
	}

	extern Logger log;
}

#endif // LOGGER_HPP
