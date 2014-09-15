#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <string>

namespace swift
{
	class Observable
	{
		public:
			void sendMessage(const std::string& m);
			std::string getMessage();

		private:
			std::string message;
	};
}

#endif // OBSERVABLE_HPP
