#include "State.hpp"

namespace swift
{
	State::State()
	:	shouldReturn(false)
	{}

	bool State::switchFrom()
	{
		return shouldReturn;
	}
}
