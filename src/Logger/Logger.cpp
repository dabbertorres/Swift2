#include "Logger.hpp"

namespace swift
{
	Logger::Logger(const std::string& header, const std::string& logFile)
	{
		warnings = 0;
		errors = 0;

		fout.open(logFile);

		// Write the first lines
		if(fout.is_open())
		{
			fout << header << std::endl << std::endl;
		}
	}

	Logger::~Logger()
	{
		if(fout.is_open())
		{
			fout << std::endl << std::endl;

			// Report number of errors and warnings
			fout << warnings << " warnings" << std::endl;
			fout << errors << " errors" << std::endl;

			fout.close();
		}
	}

	Logger& Logger::operator<<(const LogType type)
	{
		switch(type)
		{
			case LogType::ERROR:
				fout << "[ERROR]: ";
				errors++;
				break;

			case LogType::WARNING:
				fout << "[WARNING]: ";
				warnings++;
				break;

			case LogType::DEBUG:
				fout << "[DEBUG]: ";
				break;

			default:
				fout << "[INFO]: ";
				break;
		}

		return *this;
	}

	Logger& Logger::operator<<(const std::string& text)
	{
		fout << text;
		return *this;
	}
	
	Logger& Logger::operator<<(double text)
	{
		fout << text;
		return *this;
	}
	
	Logger& Logger::operator<<(float text)
	{
		fout << text;
		return *this;
	}
	
	Logger& Logger::operator<<(int text)
	{
		fout << text;
		return *this;
	}
	
	Logger& Logger::operator<<(std::size_t text)
	{
		fout << text;
		return *this;
	}
	
	Logger& Logger::operator<<(unsigned text)
	{
		fout << text;
		return *this;
	}
	
	Logger& Logger::operator<<(char text)
	{
		fout << text;
		return *this;
	}
	
	//Logger log("Swift Alpha");
}
