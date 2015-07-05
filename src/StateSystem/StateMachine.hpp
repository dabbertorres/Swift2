#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <stack>

namespace swift
{
	class State;

	class StateMachine
	{
		public:
			StateMachine();
			~StateMachine();
			
			void push(State* state, bool pend = true);
			void pop();
			State* read();
			bool empty();

		private:
			State* pending;
			std::stack<State*> states;
	};
}

#endif // STATEMACHINE_HPP
