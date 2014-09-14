#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

#include "../Component.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <functional>

namespace swift
{
	class Controllable : public Component
	{
		public:
			Controllable();
			~Controllable();
			
			struct Action
			{
				std::function<void(float dt)> callback;
				bool state;
			};

			void addAction(sf::Keyboard::Key k, const std::function<void(float dt)>& c);
			void pressed(sf::Keyboard::Key k);
			void released(sf::Keyboard::Key k);
			void update(float dt);

			static std::string getType();

		private:
			std::map<sf::Keyboard::Key, Action> actions;
	};
}

#endif // CONTROLLABLE_HPP
