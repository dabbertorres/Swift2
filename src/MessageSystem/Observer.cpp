#include "Observer.hpp"

namespace swift
{
	void Observer::addSubscription(const std::string& s, Observable& o)
	{
		subscriptions.emplace(s, &o);
	}

	void Observer::removeSubscription(const std::string& s)
	{
		subscriptions.erase(s);
	}
	
	void Observer::checkMessages()
	{
		for(auto& s : subscriptions)
		{
			std::string message = s.second->getMessage();
			if(message != "")
				messages.push(message);
		}
	}
}
