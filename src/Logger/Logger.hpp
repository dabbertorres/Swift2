#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

namespace swift
{
	class Logger
	{
		public:
			enum class LogType
			{
			    ERROR,
			    WARNING,
				DEBUG,
			    INFO
			};

			explicit Logger(const std::string& header, const std::string& logFile = "./data/swift.log")
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

			~Logger()
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

			// Make it Non Copyable
			Logger(const Logger &) = delete;
			Logger& operator =(const Logger &) = delete;

			Logger& operator <<(const LogType type)
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
			
			Logger& operator <<(char c)
			{
				fout << c;
				return *this;
			}

			Logger& operator <<(const std::string& text)
			{
				fout << text;
				return *this;
			}

		private:
			std::ofstream fout;

			unsigned warnings;
			unsigned errors;
	};
	
	//Logger log("Swift Alpha");
}

#endif // LOGGER_HPP
