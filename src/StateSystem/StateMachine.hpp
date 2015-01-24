#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <queue>

namespace swift
{
	class State;

	class StateMachine
	{
		public:
			~StateMachine();
			
			void push(State* state);
			void pop();
			State* read();
			bool empty();

		private:
			std::queue<State*> states;
	};
}

#endif // STATEMACHINE_HPP
