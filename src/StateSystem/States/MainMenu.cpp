#include "MainMenu.hpp"

namespace swift
{
	MainMenu::MainMenu(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic)
		:	State(win, am, sp, mp, set, dic)
	{		
		returnType = State::Type::MainMenu;
	}

	MainMenu::~MainMenu()
	{
	}
	
	bool MainMenu::switchFrom()
	{
		return returnType != State::Type::MainMenu;
	}
	
	State::Type MainMenu::finish()
	{
		return returnType;
	}
}
