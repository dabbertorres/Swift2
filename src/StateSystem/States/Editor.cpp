#include "Editor.hpp"

#include "../../ResourceManager/AssetManager.hpp"

#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"

#include "../../GUI/Widgets/Label.hpp"

namespace swift
{
	Editor::Editor(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic)
		:	State(win, am, set, dic),
			mapLoaded(false)
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
			window.draw(currentMap);
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
		return false;
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
		
	}
	
	void Editor::setupPauseGUI()
	{
		cstr::Column& mainColumn = pauseMenu.addContainer(new cstr::Column({300, 0, 200, 600}, false));
		
		mainColumn.addWidget(new cstr::Label("Swift Editor", assets.getFont("./data/fonts/segoeuisl.ttf"), 60));
		
	}
	
	void Editor::setupEditorGUI()
	{
		cstr::Column& mainColumn = editorCtrls.addContainer(new cstr::Column({0, 0, 200, static_cast<int>(toolsWindow.getSize().y)}, true));
	}
	
	void Editor::setupKeyBindings()
	{
		keyboard.newBinding("Esc", sf::Keyboard::Escape, [&]()
		{
			activeState = (activeState == &pause && mapLoaded) ? &editor : &pause;
		});
		
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
