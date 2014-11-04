#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Observable.hpp"

#include <queue>
#include <string>
#include <map>

namespace swift
{
	template<typename T>
	class Observer
	{
		public:
			
			void addSubscription(const std::string& s, Observable<T>& o);

			void removeSubscription(const std::string& s);

			void checkMessages();
			
			// reads the 'messages' queue and implements behavior based off of messages
			virtual void readMessages() = 0;

		protected:
			typename Observable<T>::MessageQueue messages;

		private:
			std::map<std::string, Observable<T>*> subscriptions;
	};
}

#endif // OBSERVER_HPP
