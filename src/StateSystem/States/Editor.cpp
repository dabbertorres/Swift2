#include "Editor.hpp"

#include "../../ResourceManager/AssetManager.hpp"

#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"

#include "../../GUI/Widgets/Spacer.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"

namespace swift
{
	Editor::Editor(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic)
		:	State(win, am, set, dic),
			editorView({0, 0, 800, 600}),
			activeState(nullptr),
			mapName(""),
			mapLoaded(false),
			done(false)
	{
		toolsWindow.create({200, win.getSize().y, 32}, "Tools", sf::Style::Titlebar | sf::Style::Close);
		toolsWindow.setVerticalSyncEnabled(true);
	}

	Editor::~Editor()
	{
	}
	
	void Editor::setup()
	{
		setupPauseGUI();
		setupEditorGUI();
		setupKeyBindings();
		
		pause.setEventFunc([&](sf::Event& e)
		{
			pauseMenu.update(e);
		});
		
		pause.setUpdateFunc([&](sf::Time)
		{
			// do nothing
		});
		
		pause.setDrawFunc([&](float)
		{
			window.draw(pauseMenu);
		});
		
		editor.setEventFunc([&](sf::Event& e)
		{
			editorCtrls.update(e);
		});
		
		editor.setUpdateFunc([&](sf::Time)
		{
			// do nothing
		});
		
		editor.setDrawFunc([&](float)
		{
			window.setView(editorView);
			window.draw(currentMap);
			window.setView(window.getDefaultView());
		});
		
		activeState = &pause;
	}
	
	void Editor::handleEvent(sf::Event& event)
	{
		activeState->handleEvents(event);
		
		keyboard(event);
		mouse(event);
	}
	
	void Editor::update(sf::Time dt)
	{
		activeState->update(dt);
	}

	void Editor::draw(float e)
	{
		activeState->draw(e);
		
		toolsWindow.clear();
		// draw tools
		toolsWindow.display();
	}
	
	bool Editor::switchFrom()
	{
		return done;
	}
	
	State::Type Editor::finish()
	{
		return State::Type::Exit;
	}
	
	void Editor::addTile(const sf::Vector2i& pos)
	{
		unsigned tileNum = mouseToTile(pos);
		currentMap.setTileNum(tileNum, tileSelected);
	}
	
	void Editor::removeTile(const sf::Vector2i& pos)
	{
		unsigned tileNum = mouseToTile(pos);
		currentMap.setTileNum(tileNum, 0);
	}
	
	unsigned Editor::mouseToTile(const sf::Vector2i& pos) const	
	{
		sf::Vector2f worldPos = window.mapPixelToCoords(pos, editorView);
		
		return worldPos.x / currentMap.getTileSize().x + worldPos.y / currentMap.getTileSize().y * currentMap.getSize().x;
	}
	
	void Editor::setupPauseGUI()
	{
		cstr::Column& mainColumn = pauseMenu.addContainer(new cstr::Column({300, 0, 200, 600}, false));
		
		mainColumn.addWidget(new cstr::Label("Swift Editor", assets.getFont("./data/fonts/segoeuisl.ttf"), 60));
		
		mainColumn.addWidget(new cstr::Spacer({200, 100}));
		
		cstr::Column& buttonColumn = mainColumn.addWidget(new cstr::Column({50, 0, 100, 400}, false));
		
		std::string loadStr = "Load";
		dictionary.get("loadButton", loadStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			mapLoaded = true;
			activeState = &editor;
		})).setString(loadStr, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string saveStr = "Save";
		dictionary.get("saveButton", saveStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			currentMap.saveFile("./data/maps/" + mapName + ".map");
		})).setString(saveStr, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		std::string exitStr = "Exit";
		dictionary.get("exitButton", exitStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			done = true;
		})).setString(exitStr, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
	}
	
	void Editor::setupEditorGUI()
	{
		cstr::Column& mainColumn = editorCtrls.addContainer(new cstr::Column({0, 0, 200, static_cast<int>(toolsWindow.getSize().y)}, true));
	}
	
	void Editor::setupKeyBindings()
	{
		// menu toggle
		keyboard.newBinding("Esc", sf::Keyboard::Escape, [&]()
		{
			activeState = (activeState == &pause && mapLoaded) ? &editor : &pause;
		});
		
		// keyboard controls, scrolling the map
		keyboard.newBinding("up", sf::Keyboard::Up, [&]()
		{
			editorView.move({0, -static_cast<float>(currentMap.getTileSize().y)});
		});
		
		keyboard.newBinding("down", sf::Keyboard::Down, [&]()
		{
			editorView.move({0, static_cast<float>(currentMap.getTileSize().y)});
		});
		
		keyboard.newBinding("left", sf::Keyboard::Left, [&]()
		{
			editorView.move({-static_cast<float>(currentMap.getTileSize().x), 0});
		});
		
		keyboard.newBinding("right", sf::Keyboard::Right, [&]()
		{
			editorView.move({static_cast<float>(currentMap.getTileSize().x), 0});
		});
		
		// mouse controls, adding/removing tiles
		mouse.newBinding("AddTile", sf::Mouse::Left, [&](const sf::Vector2i& pos)
		{
			if(tileSelected != -1)
				addTile(pos);
		});
		
		mouse.newBinding("RemoveTile", sf::Mouse::Right, [&](const sf::Vector2i& pos)
		{
			removeTile(pos);
		});
	}
}
