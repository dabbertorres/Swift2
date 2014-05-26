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
		
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
	}
	
	void Play::setup()
	{
		activeScripts.push_back(&assets.getScript("./data/scripts/play.lua"));
		
		for(auto &s : activeScripts)
		{
			s->start();
		}
		
		struct
		{
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			std::string str = "";
		} mainMenuReturnData;
		
		assets.getScript("./data/scripts/play.lua").getVariable("mainMenuReturnX", mainMenuReturnData.x);
		assets.getScript("./data/scripts/play.lua").getVariable("mainMenuReturnY", mainMenuReturnData.y);
		assets.getScript("./data/scripts/play.lua").getVariable("mainMenuReturnW", mainMenuReturnData.w);
		assets.getScript("./data/scripts/play.lua").getVariable("mainMenuReturnH", mainMenuReturnData.h);
		assets.getScript("./data/scripts/play.lua").getVariable("mainMenuReturnStr", mainMenuReturnData.str);
		
		cstr::Button& mainMenuReturn = gui.addButton({mainMenuReturnData.x, mainMenuReturnData.y, mainMenuReturnData.w, mainMenuReturnData.h}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::MainMenu;
		});
		
		mainMenuReturn.setText(mainMenuReturnData.str);
		mainMenuReturn.setFont(assets.getFont("./data/fonts/DroidSansMono.ttf"));
	}
			
	void Play::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void Play::update(sf::Time dt)
	{
		updateScripts();
	}
	
	void Play::draw(float e)
	{
		Player player(assets.getTexture("./data/textures/wtf.png"));
		
		window.draw(player);
		window.draw(gui);
	}
	
	bool Play::switchFrom()
	{
		return returnType != State::Type::Play;
	}
	
	State::Type Play::finish()
	{
		return returnType;
	}
}
