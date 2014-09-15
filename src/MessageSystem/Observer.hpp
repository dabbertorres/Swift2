#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Observable.hpp"

#include <string>
#include <queue>
#include <map>

namespace swift
{
	class Observer
	{
		public:
			void addSubscription(const std::string& s, Observable& o);

			void removeSubscription(const std::string& s);

			void checkMessages();
			
			// reads the 'messages' queue and implements behavior based off of messages
			virtual void readMessages() = 0;

		protected:
			std::queue<std::string> messages;

		private:
			std::map<std::string, Observable*> subscriptions;
	};
}

#endif // OBSERVER_HPP
