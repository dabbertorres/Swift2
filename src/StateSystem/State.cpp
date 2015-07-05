#include "State.hpp"

namespace swift
{
	State::State()
	:	done(false)
	{}

	bool State::isDone()
	{
		return done;
	}
}
