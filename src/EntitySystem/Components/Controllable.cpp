#include "Controllable.hpp"

namespace swift
{
	Controllable::Controllable()
	{
	}

	Controllable::~Controllable()
	{
	}
	
	void Controllable::addAction(sf::Keyboard::Key k, const std::function<void(float dt)>& c)
	{
		if(actions.find(k) == actions.end())
		{
			Action a;
			a.callback = c;
			a.state = false;
			actions.insert({k, std::move(a)});
		}
	}
	
	void Controllable::pressed(sf::Keyboard::Key k)
	{
		if(actions.find(k) != actions.end())
		{
			actions[k].state = true;
		}
	}
	
	void Controllable::released(sf::Keyboard::Key k)
	{
		if(actions.find(k) != actions.end())
		{
			actions[k].state = false;
		}
	}
	
	void Controllable::update(float dt)
	{
		for(auto& a : actions)
		{
			if(a.second.state)
			{
				a.second.callback(dt);
			}
		}
	}
	
	std::string Controllable::getType()
	{
		return "controllable";
	}
}
