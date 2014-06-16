#include <sys/utsname.h>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/gl.h>

namespace swift
{
	// returns friendly name of OS
	std::string getOSName()
	{
		#ifdef __linux__
		utsname linuxInfo;
		
		if(uname(&linuxInfo) == -1)
			return "";
			
		return static_cast<std::string>(linuxInfo.sysname);
		#elif _WIN32
		// get windows info
		#elif _OSX
		// get OSX info
		#endif
	}
	
	// returns version of the OS
	std::string getOSVersion()
	{
		#ifdef __linux__
		utsname linuxInfo;
		
		if(uname(&linuxInfo) == -1)
			return "";
			
		return static_cast<std::string>(linuxInfo.release);
		#elif _WIN32
		// get windows info
		#elif _OSX
		// get OSX info
		#endif
	}
	
	// returns architecture of the OS
	std::string getOSArch()
	{
		#ifdef __linux__
		utsname linuxInfo;
		
		if(uname(&linuxInfo) == -1)
			return "";
			
		return static_cast<std::string>(linuxInfo.machine);
		#elif _WIN32
		// get windows info
		#elif _OSX
		// get OSX info
		#endif
	}
	
	// returns total RAM in kB
	std::string getTotalMem()
	{
		#ifdef __linux__
		std::ifstream fin;
		fin.open("/proc/meminfo");
		std::string totalMemStr = "";
		
		// while can't find "MemTotal" in the string
		while(totalMemStr.find("MemTotal") == std::string::npos)
			std::getline(fin, totalMemStr);
			
		fin.close();
		
		return totalMemStr.substr(totalMemStr.find_first_of("012345689"), totalMemStr.find_last_of(' '));
		#elif _WIN32
		// get windows info
		#elif _OSX
		// get OSX info
		#endif
	}
	
	// returns friendly name of CPU
	std::string getCPUModel()
	{
		#ifdef __linux__
		std::ifstream fin;
		fin.open("/proc/cpuinfo");
		std::string cpuModel = "";
		
		// while can't find "MemTotal" in the string
		while(cpuModel.find("model name") == std::string::npos)
			std::getline(fin, cpuModel);
			
		fin.close();
		
		return cpuModel.substr(cpuModel.find_first_of(':') + 2);
		#elif _WIN32
		// get windows info
		#elif _OSX
		// get OSX info
		#endif
	}
	
	// returns designer of Video Card
	std::string getVideoVendor()
	{
		return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	}
	
	// returns name of Video Card
	std::string getVideoCard()
	{
		return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	}
	
	// returns version of the driver used by video card
	std::string getVideoDriver()
	{
		return reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}
}