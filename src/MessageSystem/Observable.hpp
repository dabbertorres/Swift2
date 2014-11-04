#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <string>
#include <queue>

namespace swift
{
	template<typename T>
	class Observable
	{
		public:
			using Message = std::pair<std::string, T>;
			using MessageQueue = std::queue<Message>;
			
			virtual ~Observable() = default;
			
			void sendMessage(const std::string& m, const T& info);
			MessageQueue getMessages();

		private:
			MessageQueue messages;
	};
	
	template<typename T>
	void Observable<T>::sendMessage(const std::string& m, const T& info)
	{
		messages.push({m, info});
	}
}

#endif // OBSERVABLE_HPP
