#ifndef NOISY_HPP
#define NOISY_HPP

#include "../Component.hpp" // Base class: swift::Component

#include <string>

namespace swift
{
	class Noisy : public Component
	{
		public:
			static std::string getType();
			
			virtual std::map<std::string,std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			std::string soundFile;
			bool shouldPlay;
			bool isPlaying;
	};
}

#endif // NOISY_HPP
