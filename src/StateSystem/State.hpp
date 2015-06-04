#ifndef STATE_HPP
#define STATE_HPP

#include "StateMachine.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

namespace swift
{
	class State
	{
		public:
			State();
			virtual ~State() = default;

			virtual void handleEvent(const sf::Event& event) = 0;
			virtual void update(const sf::Time& dt) = 0;
			virtual void draw() = 0;
			virtual bool isDone();

		protected:
			bool done;
	};
}

#endif // STATE_HPP
