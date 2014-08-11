#include "Script.hpp"

#include <fstream>
#include <cassert>

#include "../ResourceManager/AssetManager.hpp"
#include "../GUI/Window.hpp"
#include "../GUI/Widgets/Button.hpp"
#include "../GUI/Widgets/Label.hpp"
#include "../GUI/Widgets/TextBox.hpp"
#include "../GUI/Widgets/Toggle.hpp"

namespace swift
{
	sf::RenderWindow* Script::window = nullptr;
	AssetManager* Script::assets = nullptr;
	sf::Clock* Script::clock = nullptr;
	Settings* Script::settings = nullptr;
	
	Script::Script()
			:	gui(nullptr),
				stateReturn(nullptr)
	{
		deleteMe = false;
		
		// We don't want to give the scripts access to os commands or file writing abilities
		luaState.OpenLib("base", luaopen_base);
		luaState.OpenLib("math", luaopen_math);
		luaState.OpenLib("string", luaopen_string);
		luaState.OpenLib("table", luaopen_table);
		
		addVariables();
		addClasses();
		addFunctions();
	}

	Script::~Script()
	{
	}

	bool Script::loadFromFile(const std::string& file)
	{
		bool r = luaState.Load(file);	// r will be false if errors, true otherwise
		
		return r;
	}
	
	void Script::start()
	{
		luaState["Start"]();
		
		if(static_cast<bool>(luaState["Done"]) == true)
		{
			deleteMe = true;
		}
	}

	void Script::run()
	{
		luaState["Update"]();
		
		if(static_cast<bool>(luaState["Done"]) == true)
		{
			deleteMe = true;
		}
	}

	bool Script::toDelete()
	{
		return deleteMe;
	}
	
	void Script::setWindow(sf::RenderWindow& win)
	{
		window = &win;
	}
	
	void Script::setAssetManager(AssetManager& am)
	{
		assets = &am;
	}
	
	void Script::setSettings(Settings& s)
	{
		settings = &s;
	}
	
	void Script::setGUI(cstr::Window& ui)
	{
		gui = &ui;
	}
	
	void Script::setKeyboard(KeyboardManager& k)
	{
		keyboard = &k;
	}
	
	void Script::setStateReturn(State::Type& t)
	{
		stateReturn = &t;
	}
	
	void Script::setClock(sf::Clock& c)
	{
		clock = &c;
	}
	
	void Script::addVariables()
	{
		luaState["states"]["MainMenu"] = 0;
		luaState["states"]["Settings"] = 1;
		luaState["states"]["Play"] = 2;
		luaState["states"]["Exit"] = 3;
	}
	
	void Script::addClasses()
	{
		luaState["Label"].SetClass<cstr::Label>("setTextSize", &cstr::Label::setCharacterSize);
		luaState["Button"].SetClass<cstr::Button>("setText", &cstr::Button::setText);
		luaState["Toggle"].SetClass<cstr::Toggle>("getState", &cstr::Toggle::getState);
		luaState["TextBox"].SetClass<cstr::TextBox>("getString", &cstr::TextBox::getString);
	}
	
	void Script::addFunctions()
	{
		// utility functions
		luaState["getWindowSize"] = [&]()
		{
			if(window)
				return std::make_tuple(window->getSize().x, window->getSize().y);
			else
				return std::make_tuple(0u, 0u);
		};
		
		luaState["getTime"] = [&]()
		{
			if(clock)
				return clock->getElapsedTime().asSeconds();
			else
				return 0.f;
		};
		
		luaState["doKeypress"] = [&](std::string k) -> void
		{
			if(keyboard)
				keyboard->call(k);
		};
		
		// gui functions
		luaState["setFont"] = [&](std::string f) -> void
		{
			if(gui)
				gui->setFont(assets->getFont(f));
		};
		
		luaState["addLabel"] = [&](int x, int y, std::string l) -> cstr::Label*
		{
			return &gui->addLabel({x, y}, l);
		};
		
		luaState["addButton"] = [&](int x, int y, int w, int h, std::string t, sel::function<void()> f) -> cstr::Button*
		{
			return &gui->addButton({x, y, w, h}, assets->getTexture(t), static_cast<std::function<void()>>(f));
		};
		
		luaState["addToggle"] = [&](int x, int y, int w, int h, std::string texOff, std::string texOn, bool s) -> cstr::Toggle*
		{
			return &gui->addToggle({x, y, w, h}, assets->getTexture(texOff), assets->getTexture(texOn), s);
		};
		
		luaState["addTextBox"] = [&](int x, int y, int w, int h, int inR, int inG, int inB, int outR, int outG, int outB) -> cstr::TextBox*
		{
			return &gui->addTextBox({x, y, w, h}, {static_cast<sf::Uint8>(inR), static_cast<sf::Uint8>(inG), static_cast<sf::Uint8>(inB)}, 
												{static_cast<sf::Uint8>(outR), static_cast<sf::Uint8>(outG), static_cast<sf::Uint8>(outB)});
		};
		
		// State functions
		luaState["setStateReturn"] = [&](unsigned s)
		{
			*stateReturn = static_cast<State::Type>(s);
		};
		
		// Settings functions
		luaState["getSettingStr"] = [&](std::string n)
		{
			std::string v;
			return std::make_tuple(settings->get(n, v), v);
		};
		
		luaState["setSettingStr"] = [&](std::string n, std::string v)
		{
			settings->set(n, v);
		};
		
		luaState["getSettingBool"] = [&](std::string n)
		{
			bool v;
			return std::make_tuple(settings->get(n, v), v);
		};
		
		luaState["setSettingBool"] = [&](std::string n, bool v)
		{
			settings->set(n, v);
		};
		
		luaState["getSettingNum"] = [&](std::string n)
		{
			int v;
			return std::make_tuple(settings->get(n, v), v);
		};
		
		luaState["setSettingNum"] = [&](std::string n, int v)
		{
			settings->set(n, v);
		};
	}
}