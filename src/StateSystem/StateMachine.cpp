#include "StateMachine.hpp"

#include "State.hpp"

namespace swift
{
	StateMachine::~StateMachine()
	{
		while(!states.empty())
		{
			delete states.front();
			states.pop();
		}
	}

	void StateMachine::push(State* state)
	{
		states.push(state);
	}
	
	void StateMachine::pop()
	{
		delete states.front();
		states.pop();
	}
	
	State* StateMachine::read()
	{
		return states.front();
	}
	
	bool StateMachine::empty()
	{
		return states.empty();
	}
}
