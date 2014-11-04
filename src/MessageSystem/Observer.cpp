#include "Observer.hpp"

namespace swift
{
	template<typename T>
	void Observer<T>::addSubscription(const std::string& s, Observable<T>& o)
	{
		subscriptions.emplace(s, &o);
	}
	
	template<typename T>
	void Observer<T>::removeSubscription(const std::string& s)
	{
		subscriptions.erase(s);
	}
	
	template<typename T>
	void Observer<T>::checkMessages()
	{
		for(auto& s : subscriptions)
		{
			for(auto& m : s.second->getMessages())
			{
				messages.push(m);
			}
		}
	}
}
