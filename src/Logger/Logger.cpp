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
			fout << header << "\n\n";
		}

		sf::err().rdbuf(0);
	}

	Logger::~Logger()
	{
		if(fout.is_open())
		{
			fout << std::endl << std::endl;

			// Report number of errors and warnings
			fout << warnings << " warnings\n";
			fout << errors << " errors\n";

			fout.close();
		}
	}

	template<>
	Logger& Logger::operator<<(const std::string& text)
	{
		fout << text;
		fout.flush();

		if(text.find("[ERROR]") != std::string::npos)
		{
			errors++;
		}

		if(text.find("[WARNING]") != std::string::npos)
		{
			warnings++;
		}

		return *this;
	}

	Logger log("Swift2");
}
