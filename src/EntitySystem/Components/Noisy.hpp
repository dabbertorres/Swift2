#ifndef NOISY_HPP
#define NOISY_HPP

#include "../Component.hpp"

#include <string>

namespace swift
{
	class Physical;
	
	class Noisy : public Component
	{
		public:
			Noisy(unsigned int id, const Physical& p);
			
			Noisy(const Noisy& other);
			
			Noisy& operator=(Noisy&& other);
			
			const Physical& getPhysical() const;
			
			static constexpr Component::Type type();
			
			virtual std::map<std::string,std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			std::string soundFile;
			bool shouldPlay;

		private:
			const Physical& physical;
	};
	
	constexpr Component::Type Noisy::type()
	{
		return Component::Type::Noisy;
	}
}

#endif // NOISY_HPP
