#include "SubState.hpp"

namespace swift
{
	SubState::SubState(const EventHandler& e, const Updater& u, const Drawer& d)
	:	eventFunc(e),
		updateFunc(u),
		drawFunc(d)
	{}

	void SubState::handleEvents(const sf::Event& e)
	{
		try
		{
			eventFunc(e);
		}
		catch(...)
		{
			
		}
	}

	void SubState::update(const sf::Time& dt)
	{
		try
		{
			updateFunc(dt);
		}
		catch(...)
		{
			
		}
	}

	void SubState::draw()
	{
		try
		{
			drawFunc();
		}
		catch(...)
		{
			
		}
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
