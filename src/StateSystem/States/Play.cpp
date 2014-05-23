#include "Play.hpp"

namespace swift
{
	Play::Play(sf::RenderWindow& win, AssetManager& am)
		: State(win, am)
	{
		keyboard.newBinding("up", sf::Keyboard::W, []()
		{
			std::clog << "\'Up\' was pressed!\n";
		});
		
		keyboard.newBinding("left", sf::Keyboard::A, []()
		{
			std::clog << "\'Left\' was pressed!\n";
		});
		
		keyboard.newBinding("right", sf::Keyboard::D, []()
		{
			std::clog << "\'Right\' was pressed!\n";
		});
		
		keyboard.newBinding("down", sf::Keyboard::S, []()
		{
			std::clog << "\'Down\' was pressed!\n";
		});
	}

	Play::~Play()
	{
	}
	
	void Play::setup()
	{
		for(auto &s : activeScripts)
		{
			s->start();
		}
	}
	
	void Play::switchTo()
	{
		
	}
			
	void Play::handleEvent(sf::Event &event)
	{
		keyboard(event);
		mouse(event);
	}
	
	void Play::update(sf::Time dt)
	{
		updateScripts();
	}
	
	void Play::draw(float e)
	{
		
	}
	
	State::Type Play::switchFrom()
	{
		return State::Type::Play;
	}
	
	void Play::finish()
	{
		
	}
}
