#include "SubState.hpp"

namespace swift
{
	SubState::SubState()
	:	eventFunc({}),
		updateFunc({}),
		drawFunc({})
	{}

	SubState::SubState(const EventHandler& e, const Updater& u, const Drawer& d)
	:	eventFunc(e),
		updateFunc(u),
		drawFunc(d)
	{}

	void SubState::handleEvents(const sf::Event& e)
	{
		eventFunc(e);
	}

	void SubState::update(const sf::Time& dt)
	{
		updateFunc(dt);
	}

	void SubState::draw()
	{
		drawFunc();
	}

	void SubState::setEventFunc(const EventHandler& e)
	{
		eventFunc = e;
	}

	void SubState::setUpdateFunc(const Updater& u)
	{
		updateFunc = u;
	}

	void SubState::setDrawFunc(const Drawer& d)
	{
		drawFunc = d;
	}
}
