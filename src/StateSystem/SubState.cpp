#include "SubState.hpp"

namespace swift
{
	SubState::SubState()
	:	eventFunc([](sf::Event&) {}),
		updateFunc([](sf::Time) {}),
		drawFunc([](float) {})
	{
	}

	SubState::SubState(const std::function<void(sf::Event&)>& e, const std::function<void(sf::Time)>& u, const std::function<void(float e)>& d)
	:	eventFunc(e),
		updateFunc(u),
		drawFunc(d)
	{
	}

	void SubState::handleEvents(sf::Event& e)
	{
		eventFunc(e);
	}

	void SubState::update(sf::Time dt)
	{
		updateFunc(dt);
	}

	void SubState::draw(float e)
	{
		drawFunc(e);
	}

	void SubState::setEventFunc(const std::function<void(sf::Event&)>& e)
	{
		eventFunc = e;
	}

	void SubState::setUpdateFunc(const std::function<void(sf::Time)>& u)
	{
		updateFunc = u;
	}

	void SubState::setDrawFunc(const std::function<void(float e)>& d)
	{
		drawFunc = d;
	}
}
