#include "Play.hpp"

#include <functional>

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"

/* Worlds */
#include "../../World/Worlds/TestWorld.hpp"

namespace swift
{
	Play::Play(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic)
		:	State(win, am, set, dic),
		    state(SubState::Play),
			activeWorld(nullptr),
			player(nullptr)
	{
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
		for(auto& w : worlds)
			delete w;
	}

	void Play::setup()
	{
		window.setKeyRepeatEnabled(false);
		
		worlds.emplace_back(new TestWorld("testWorld", {800, 600}, assets));
		activeWorld = worlds[0];
		
		setupKeyBindings();
		
		// setup pause menu GUI
		std::string resume = "Resume";
		dictionary.get("resumeButton", resume);
		cstr::Column& pauseColumn = pauseMenu.addContainer(new cstr::Column({static_cast<int>(window.getSize().x) / 2 - 50, static_cast<int>(window.getSize().y / 2) - 50, 100, 125}, false));
		pauseColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			state = SubState::Play;
		})).setString(resume, assets.getFont("./data/fonts/segoeuisl.ttf"));
		
		pauseColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string mainMenu = "Main Menu";
		dictionary.get("mainMenuButton", mainMenu);
		pauseColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::MainMenu;
		})).setString(mainMenu, assets.getFont("./data/fonts/segoeuisl.ttf"));
		
		// setup world
		activeWorld->tilemap.loadFile("./data/maps/maze.map");
		activeWorld->tilemap.loadTexture(assets.getTexture(activeWorld->tilemap.getTextureFile()));
		
		if(!activeWorld->load())
		{
			player = activeWorld->addEntity();
			player->add<Drawable>();
			Drawable* drawable = player->get<Drawable>();
			sf::Texture& texture = assets.getTexture("./data/textures/guy.png");
			drawable->texture = "./data/textures/guy.png";
			drawable->sprite.setTexture(texture);
			drawable->sprite.setScale({16.f / texture.getSize().x, 48.f / texture.getSize().y});
			
			player->add<Name>();
			Name* name = player->get<Name>();
			name->name = "player";
			
			player->add<Physical>();
			Physical* physical = player->get<Physical>();
			physical->size = {16, 48};
			physical->position = {window.getSize().x / 2.f, 500};
			
			player->add<Movable>();
			Movable* movable = player->get<Movable>();
			movable->moveVelocity = 50;
			movable->velocity = {0, 0};
		}
		else
			player = activeWorld->getEntities()[0];
		
		activeWorld->addScript("./data/scripts/quest.lua");
		assets.getScript("./data/scripts/quest.lua").start();
	}

	void Play::handleEvent(sf::Event& event)
	{
		switch(state)
		{
			case SubState::Play:
				hud.update(event);
				break;
			case SubState::Pause:
				pauseMenu.update(event);
				break;
			default:
				break;
		}

		keyboard(event);
		mouse(event);
	}

	void Play::update(sf::Time dt)
	{
		switch(state)
		{
			case SubState::Play:
				activeWorld->update(dt.asSeconds());
				break;
			case SubState::Pause:
				break;
		}
	}

	void Play::draw(float /*e*/)
	{
		switch(state)
		{
			case SubState::Play:
				activeWorld->drawWorld(window);
				
				activeWorld->drawEntities(window);
				
				window.draw(hud);
				break;
			case SubState::Pause:
				window.draw(pauseMenu);
				break;
			default:
				break;
		}
	}

	bool Play::switchFrom()
	{
		return returnType != State::Type::Play;
	}

	State::Type Play::finish()
	{
		return returnType;
	}

	void Play::setupKeyBindings()
	{
		keyboard.newBinding("PauseMenu", sf::Keyboard::Escape, [&]()
		{
			state = (state == SubState::Pause) ? SubState::Play : SubState::Pause;
		}, false);
		
		// move up press and release
		keyboard.newBinding("moveUpStart", sf::Keyboard::Up, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, -player->get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, player->get<Movable>()->moveVelocity};
		}, false);
		
		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, player->get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, -player->get<Movable>()->moveVelocity};
		}, false);
		
		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {-player->get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {player->get<Movable>()->moveVelocity, 0};
		}, false);
		
		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {player->get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {-player->get<Movable>()->moveVelocity, 0};
		}, false);
	}
}
