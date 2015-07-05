#include "StateMachine.hpp"

#include "State.hpp"

namespace swift
{
	StateMachine::StateMachine()
	:	pending(nullptr)
	{}
	
	StateMachine::~StateMachine()
	{
		while(!states.empty())
		{
			delete states.top();
			states.pop();
		}
	}

	void StateMachine::push(State* state, bool pend)
	{
		if(pend)
		{
			pending = state;
		}
		else
		{
			states.push(state);
		}
	}
	
	void StateMachine::pop()
	{
		delete states.top();
		states.pop();
		
		if(pending)
		{
			states.push(pending);
			pending = nullptr;
		}
	}
	
	State* StateMachine::read()
	{
		return states.top();
	}
	
	bool StateMachine::empty()
	{
		return states.empty();
	}
}
