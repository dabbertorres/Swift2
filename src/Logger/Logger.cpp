#include "Logger.hpp"

#include <string>

constexpr const char* HEADER = "Swift2";

namespace swift
{
	Logger Logger::self;
	
	template<>
	Logger& Logger::operator<<(const std::string& text)
	{
		if(fout)
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
		}
		
		return *this;
	}
	
	Logger& Logger::get()
	{
		return self;
	}
	
	bool Logger::setFile(const gfs::Path& path)
	{
		self.fout.open(path);

		// Write the first lines
		if(self.fout)
		{
			self.fout << HEADER << "\n\n";
			return true;
		}
		
		return false;
	}
	
	Logger::Logger()
	{
		warnings = 0;
		errors = 0;
	}

	Logger::~Logger()
	{
		if(fout)
		{
			fout << "\n\n";

			// Report number of errors and warnings
			fout << warnings << " warnings\n";
			fout << errors << " errors\n";
		}
	}
}
