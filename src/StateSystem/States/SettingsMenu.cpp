#include "SettingsMenu.hpp"

namespace swift
{
	SettingsMenu::SettingsMenu(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic)
		:	State(win, am, sp, mp, set, dic)
	{
		returnType = State::Type::SettingsMenu;
	}

	SettingsMenu::~SettingsMenu()
	{
	}
	
	bool SettingsMenu::switchFrom()
	{
		return returnType != State::Type::SettingsMenu;
	}
	
	State::Type SettingsMenu::finish()
	{
		return returnType;
	}
}
