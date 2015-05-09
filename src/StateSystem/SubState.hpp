#ifndef SUBSTATE_HPP
#define SUBSTATE_HPP

#include <functional>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace swift
{
	class SubState
	{
		public:
			SubState();
			SubState(const std::function<void(sf::Event&)>& e, const std::function<void(sf::Time)>& u, const std::function<void(float e)>& d);
			virtual ~SubState() = default;

			void handleEvents(sf::Event& e);
			void update(sf::Time dt);
			void draw(float e);

			void setEventFunc(const std::function<void(sf::Event&)>& e);
			void setUpdateFunc(const std::function<void(sf::Time)>& u);
			void setDrawFunc(const std::function<void(float e)>& d);

		private:
			std::function<void(sf::Event& e)> eventFunc;
			std::function<void(sf::Time dt)> updateFunc;
			std::function<void(float e)> drawFunc;
	};
}

#endif // SUBSTATE_HPP
