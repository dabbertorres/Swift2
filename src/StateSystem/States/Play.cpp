#include "Play.hpp"

namespace swift
{
	const float PLAYER_MOVE_FORCE = 2000;
	
	Play::Play(sf::RenderWindow& win, AssetManager& am)
		:	State(win, am)
	{		
		returnType = State::Type::Play;
		
		playerFactory.setConstruction([&](Player& p)
		{
			p.setTexture(assets.getTexture("./data/textures/ship.png"));
			p.setMass(1);
		});
		
		Player& player = playerFactory.create();
		player.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f});
		
		keyboard.newBinding("UpStart", sf::Keyboard::Up, [&]()
		{
			player.addForce({0, -PLAYER_MOVE_FORCE});
		}, true);
		
		keyboard.newBinding("LeftStart", sf::Keyboard::Left, [&]()
		{
			player.addForce({-PLAYER_MOVE_FORCE, 0});
		}, true);
		
		keyboard.newBinding("DownStart", sf::Keyboard::Down, [&]()
		{
			player.addForce({0, PLAYER_MOVE_FORCE});
		}, true);
		
		keyboard.newBinding("RightStart", sf::Keyboard::Right, [&]()
		{
			player.addForce({PLAYER_MOVE_FORCE, 0});
		}, true);
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
		
		setupButtons();
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
		
		for(auto p : playerFactory.getEntities())
		{
			p->update(dt.asSeconds());
		}
	}
	
	void Play::draw(float /*e*/)
	{
		for(auto p : playerFactory.getEntities())
		{
			window.draw(*p);
		}
		
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
	
	void Play::setupButtons()
	{
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
	
	void Play::setupKeyBindings()
	{
		
	}
}
