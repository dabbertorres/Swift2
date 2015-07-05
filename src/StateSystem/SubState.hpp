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
			using EventHandler = std::function<void(const sf::Event&)>;
			using Updater = std::function<void(const sf::Time&)>;
			using Drawer = std::function<void()>;
			
			SubState() = default;
			SubState(const EventHandler& e, const Updater& u, const Drawer& d);
			virtual ~SubState() = default;

			void handleEvents(const sf::Event& e);
			void update(const sf::Time& dt);
			void draw();

			void setEventFunc(const EventHandler& e);
			void setUpdateFunc(const Updater& u);
			void setDrawFunc(const Drawer& d);

		private:
			EventHandler eventFunc;
			Updater updateFunc;
			Drawer drawFunc;
	};
}

#endif // SUBSTATE_HPP
