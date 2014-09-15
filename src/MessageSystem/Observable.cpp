#include "Observable.hpp"

namespace swift
{
	void Observable::sendMessage(const std::string& m)
	{
		message = m;
	}
	
	std::string Observable::getMessage()
	{
		std::string temp = message;
		message = "";
		return temp;
	}
}
