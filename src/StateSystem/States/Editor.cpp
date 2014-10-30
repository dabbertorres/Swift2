#include "Editor.hpp"

#include "../../ResourceManager/AssetManager.hpp"

#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"

#include "../../GUI/Widgets/Spacer.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/TextBox.hpp"

namespace swift
{
	const float EDITOR_MOVE_SPEED = 250.f;
	
	Editor::Editor(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic)
		:	State(win, am, set, dic),
			editorView({0, 0, static_cast<float>(win.getSize().x - 200), static_cast<float>(win.getSize().y)}),
			editorViewMove({0, 0}),
			activeState(nullptr),
			currentMap(nullptr),
			mapName(""),
			mapLoaded(false),
			done(false)
	{
		editorView.setViewport({0, 0, (win.getSize().x - 200.f) / win.getSize().x, 1});
	}

	Editor::~Editor()
	{
	}
	
	void Editor::setup()
	{
		setupSubStateFuncs();
		
		setupPauseGUI();
		setupNewMapGUI();
		setupLoadMapGUI();
		
		setupKeyBindings();
		
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
		int tileNum = mouseToTile(pos);
		
		if(tileNum != -1)
			currentMap->setTileNum(tileNum, tileSelected);
	}
	
	void Editor::removeTile(const sf::Vector2i& pos)
	{
		int tileNum = mouseToTile(pos);
		
		if(tileNum != -1)
			currentMap->setTileNum(tileNum, 0);
	}
	
	int Editor::mouseToTile(const sf::Vector2i& pos) const	
	{
		sf::Vector2f worldPos = window.mapPixelToCoords(pos, editorView);
		
		sf::Vector2f worldTilePos = {std::floor(worldPos.x / currentMap->getTileSize().x), std::floor(worldPos.y / currentMap->getTileSize().y)};
		
		if(worldTilePos.x >= currentMap->getSize().x || worldTilePos.y >= currentMap->getSize().y)
			return -1;
		
		return worldTilePos.x + worldTilePos.y * currentMap->getSize().x;
	}
	
	void Editor::setupSubStateFuncs()
	{
		// SubState pause
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
		
		// SubState editor
		editor.setEventFunc([&](sf::Event& e)
		{
			if(e.type == sf::Event::MouseWheelMoved)
			{
				float zoom = 1 - e.mouseWheel.delta / 10.f;
				editorView.zoom(zoom);
			}
			
			editorCtrls.update(e);
		});
		
		editor.setUpdateFunc([&](sf::Time dt)
		{
			editorView.move(editorViewMove * dt.asSeconds());
		});
		
		editor.setDrawFunc([&](float)
		{
			window.setView(editorView);
			window.draw(*currentMap);
			window.setView(window.getDefaultView());
			
			window.draw(editorCtrls);
		});
		
		// SubState newMap
		newMap.setEventFunc([&](sf::Event& e)
		{
			newMapGUI.update(e);
		});
		
		newMap.setUpdateFunc([&](sf::Time)
		{
			// do nothing
		});
		
		newMap.setDrawFunc([&](float)
		{
			window.draw(newMapGUI);
		});
		
		// SubState loadMap
		loadMap.setEventFunc([&](sf::Event& e)
		{
			loadMapGUI.update(e);
		});
		
		loadMap.setUpdateFunc([&](sf::Time)
		{
			// do nothing
		});
		
		loadMap.setDrawFunc([&](float)
		{
			window.draw(loadMapGUI);
		});
	}
	
	void Editor::setupPauseGUI()
	{
		cstr::Column& mainColumn = pauseMenu.addContainer(new cstr::Column({300, 0, 200, 600}, false));
		
		mainColumn.addWidget(new cstr::Label("Swift Editor", assets.getFont("./data/fonts/segoeuisl.ttf"), 60));
		
		mainColumn.addWidget(new cstr::Spacer({200, 100}));
		
		cstr::Column& buttonColumn = mainColumn.addWidget(new cstr::Column({50, 0, 100, 400}, false));
		
		std::string newStr = "New";
		dictionary.get("newButton", newStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			activeState = &newMap;
		})).setString(newStr, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string loadStr = "Load";
		dictionary.get("loadButton", loadStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			activeState = &loadMap;
		})).setString(loadStr, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string saveStr = "Save";
		dictionary.get("saveButton", saveStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			if(mapName != "")
				currentMap->saveFile("./data/maps/" + mapName + ".map");
		})).setString(saveStr, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string exitStr = "Exit";
		dictionary.get("exitButton", exitStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			done = true;
		})).setString(exitStr, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
	}
	
	void Editor::setupEditorGUI()
	{
		editorCtrls.clear();
		
		// tools window, not main window
		cstr::Column& mainColumn = editorCtrls.addContainer(new cstr::Column({static_cast<int>(window.getSize().x) - 200, 0, 200, static_cast<int>(window.getSize().y)}, true));
		
		// number of rows
		unsigned numTileTypes = currentMap->getNumOfTileTypes();
		sf::Vector2u tileSize = currentMap->getTileSize();
		sf::Vector2u textureSize = assets.getTexture(currentMap->getTextureFile()).getSize();
		
		// 4 for rows of 4.
		for(unsigned i = 0; i < numTileTypes / 4 + numTileTypes % 4; i++)
		{
			cstr::Row& newRow = mainColumn.addWidget(new cstr::Row({static_cast<int>(mainColumn.getGlobalBounds().width), 50}, false));
			
			for(unsigned j = 0; j < 4; j++)
			{
				sf::Vector2u texturePos = {(i * 4 + j) % (textureSize.x / tileSize.x) * tileSize.x, (i * 4 + j) / (textureSize.x / tileSize.x) * tileSize.y};
				
				newRow.addWidget(new cstr::Button({50, 50}, assets.getTexture(currentMap->getTextureFile()), [&, i, j]()
				{
					tileSelected = i * 4 + j;
				})).setTextureRect({static_cast<int>(texturePos.x), static_cast<int>(texturePos.y), static_cast<int>(tileSize.x), static_cast<int>(tileSize.y)}, {50, 50});
			}
		}
	}
	
	void Editor::setupNewMapGUI()
	{
		cstr::Column& mainColumn = newMapGUI.addContainer(new cstr::Column({200, 0, 400, 600}, false));
		
		mainColumn.addWidget(new cstr::Spacer({400, 200}));
		
		cstr::Row& nameRow = mainColumn.addWidget(new cstr::Row({400, 30}, false));
		
		// map name
		std::string name = "Name:";
		dictionary.get("mapNameLabel", name);
		nameRow.addWidget(new cstr::Label(name, assets.getFont("./data/fonts/segoeuisl.ttf"), 25));
		nameRow.addWidget(new cstr::Spacer({20, 30}));
		cstr::TextBox& mapNameText = nameRow.addWidget(new cstr::TextBox({280, 30}, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		mainColumn.addWidget(new cstr::Spacer({400, 20}));
		
		cstr::Row& textureRow = mainColumn.addWidget(new cstr::Row({400, 30}, false));
		
		// texture
		std::string texture = "Texture:";
		dictionary.get("textureLabel", texture);
		textureRow.addWidget(new cstr::Label(texture, assets.getFont("./data/fonts/segoeuisl.ttf"), 25));
		textureRow.addWidget(new cstr::Spacer({10, 30}));
		cstr::TextBox& textureText = textureRow.addWidget(new cstr::TextBox({280, 30}, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		mainColumn.addWidget(new cstr::Spacer({400, 20}));
		
		cstr::Row& xSizeRow = mainColumn.addWidget(new cstr::Row({400, 30}, false));
		
		// x size
		std::string xSize = "X Size:";
		dictionary.get("xSizeLabel", xSize);
		xSizeRow.addWidget(new cstr::Label(xSize, assets.getFont("./data/fonts/segoeuisl.ttf"), 25));
		xSizeRow.addWidget(new cstr::Spacer({10, 30}));
		cstr::TextBox& xSizeText = xSizeRow.addWidget(new cstr::TextBox({280, 30}, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		mainColumn.addWidget(new cstr::Spacer({400, 20}));
		
		cstr::Row& ySizeRow = mainColumn.addWidget(new cstr::Row({400, 30}, false));
		
		// y size
		std::string ySize = "Y Size:";
		dictionary.get("ySizeLabel", ySize);
		ySizeRow.addWidget(new cstr::Label(ySize, assets.getFont("./data/fonts/segoeuisl.ttf"), 25));
		ySizeRow.addWidget(new cstr::Spacer({10, 30}));
		cstr::TextBox& ySizeText = ySizeRow.addWidget(new cstr::TextBox({280, 30}, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		mainColumn.addWidget(new cstr::Spacer({400, 20}));
		
		cstr::Row& xTileSizeRow = mainColumn.addWidget(new cstr::Row({400, 30}, false));
		
		// x tile size
		std::string xTileSize = "Tile Size X:";
		dictionary.get("tileSizeXLabel", xTileSize);
		xTileSizeRow.addWidget(new cstr::Label(xTileSize, assets.getFont("./data/fonts/segoeuisl.ttf"), 25));
		xTileSizeRow.addWidget(new cstr::Spacer({2, 30}));
		cstr::TextBox& xTileSizeText = xTileSizeRow.addWidget(new cstr::TextBox({280, 30}, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		mainColumn.addWidget(new cstr::Spacer({400, 20}));
		
		cstr::Row& yTileSizeRow = mainColumn.addWidget(new cstr::Row({400, 30}, false));
		
		// y tile size
		std::string yTileSize = "Tile Size Y:";
		dictionary.get("tileSizeYLabel", yTileSize);
		yTileSizeRow.addWidget(new cstr::Label(yTileSize, assets.getFont("./data/fonts/segoeuisl.ttf"), 25));
		yTileSizeRow.addWidget(new cstr::Spacer({2, 30}));
		cstr::TextBox& yTileSizeText = yTileSizeRow.addWidget(new cstr::TextBox({280, 30}, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		mainColumn.addWidget(new cstr::Spacer({400, 20}));
		
		cstr::Row& startCancelRow = mainColumn.addWidget(new cstr::Row({400, 50}, false));
		
		// start and cancel buttons
		std::string cancel = "Cancel";
		dictionary.get("cancelButton", cancel);
		startCancelRow.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			mapLoaded = false;
			activeState = &pause;
			
			// reset text boxes
			mapNameText.clear();
			textureText.clear();
			xSizeText.clear();
			ySizeText.clear();
		})).setString(cancel, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		startCancelRow.addWidget(new cstr::Spacer({200, 50}));
		
		std::string start = "Start";
		dictionary.get("startButton", start);
		startCancelRow.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			if(mapNameText.getString() != "" && textureText.getString() != "" && xSizeText.getString() != "" && ySizeText.getString() != "")
			{
				mapLoaded = true;
				activeState = &editor;
				mapName = mapNameText.getString();
				
				if(currentMap)
					delete currentMap;
				
				currentMap = new TileMap();
				
				// set the texture of the map
				currentMap->setTextureFile("./data/textures/" + textureText.getString());
				currentMap->loadTexture(assets.getTexture("./data/textures/" + textureText.getString()));
				currentMap->setSize({static_cast<unsigned>(std::stoi(xSizeText.getString())), static_cast<unsigned>(std::stoi(ySizeText.getString()))});
				currentMap->setTileSize({static_cast<unsigned>(std::stoi(xTileSizeText.getString())), static_cast<unsigned>(std::stoi(yTileSizeText.getString()))});
				
				if(!currentMap->init())
					return;
				
				setupEditorGUI();
				
				// reset text boxes
				mapNameText.clear();
				textureText.clear();
				xSizeText.clear();
				ySizeText.clear();
				xTileSizeText.clear();
				yTileSizeText.clear();
			}
		})).setString(start, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
	}
	
	void Editor::setupLoadMapGUI()
	{
		cstr::Column& mainColumn = loadMapGUI.addContainer(new cstr::Column({200, 200, 400, 600}, false));
		
		cstr::Row& mapNameRow = mainColumn.addWidget(new cstr::Row({300, 30}, false));
		
		std::string name = "Name:";
		dictionary.get("loadMapLabel", name);
		mapNameRow.addWidget(new cstr::Label(name, assets.getFont("./data/fonts/segoeuisl.ttf"), 25));
		mapNameRow.addWidget(new cstr::Spacer({10, 30}));
		cstr::TextBox& loadMapText = mapNameRow.addWidget(new cstr::TextBox({200, 30}, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		mainColumn.addWidget(new cstr::Spacer({400, 20}));
		
		cstr::Row& loadCancelRow = mainColumn.addWidget(new cstr::Row({400, 50}, false));
		
		// load and cancel buttons
		std::string cancel = "Cancel";
		dictionary.get("cancelButton", cancel);
		loadCancelRow.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			mapLoaded = false;
			activeState = &pause;
			
			// reset text boxes
			loadMapText.clear();
		})).setString(cancel, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		loadCancelRow.addWidget(new cstr::Spacer({200, 50}));
		
		std::string load = "Load";
		dictionary.get("loadButton", load);
		loadCancelRow.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			mapLoaded = true;
			activeState = &editor;
			
			mapName = loadMapText.getString();
			
			if(currentMap)
				delete currentMap;
			
			currentMap = new TileMap();
			
			loadMapText.clear();
			
			// set the texture of the map
			currentMap->loadFile("./data/maps/" + mapName + ".map");
			currentMap->loadTexture(assets.getTexture(currentMap->getTextureFile()));
			
			setupEditorGUI();
		})).setString(load, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
	}
	
	void Editor::setupKeyBindings()
	{
		// menu toggle
		keyboard.newBinding("Esc", sf::Keyboard::Escape, [&]()
		{
			activeState = (activeState == &pause && mapLoaded) ? &editor : &pause;
			editorViewMove = {0, 0};
		});
		
		// keyboard controls, scrolling the map
		keyboard.newBinding("upStart", sf::Keyboard::Up, [&]()
		{
			if(activeState == &editor)
				editorViewMove.y -= EDITOR_MOVE_SPEED;
		}, true);
		
		keyboard.newBinding("downStart", sf::Keyboard::Down, [&]()
		{
			if(activeState == &editor)
				editorViewMove.y += EDITOR_MOVE_SPEED;
		}, true);
		
		keyboard.newBinding("leftStart", sf::Keyboard::Left, [&]()
		{
			if(activeState == &editor)
				editorViewMove.x -= EDITOR_MOVE_SPEED;
		}, true);
		
		keyboard.newBinding("rightStart", sf::Keyboard::Right, [&]()
		{
			if(activeState == &editor)
				editorViewMove.x += EDITOR_MOVE_SPEED;
		}, true);
		
		keyboard.newBinding("upEnd", sf::Keyboard::Up, [&]()
		{
			if(activeState == &editor)
				editorViewMove.y += EDITOR_MOVE_SPEED;
		});
		
		keyboard.newBinding("downEnd", sf::Keyboard::Down, [&]()
		{
			if(activeState == &editor)
				editorViewMove.y -= EDITOR_MOVE_SPEED;
		});
		
		keyboard.newBinding("leftEnd", sf::Keyboard::Left, [&]()
		{
			if(activeState == &editor)
				editorViewMove.x += EDITOR_MOVE_SPEED;
		});
		
		keyboard.newBinding("rightEnd", sf::Keyboard::Right, [&]()
		{
			if(activeState == &editor)
				editorViewMove.x -= EDITOR_MOVE_SPEED;
		});
		
		// mouse controls, adding/removing tiles
		mouse.newBinding("AddTile", sf::Mouse::Left, [&](const sf::Vector2i& pos)
		{
			if(activeState == &editor)
				if(tileSelected != -1)
					addTile(pos);
		});
		
		mouse.newBinding("RemoveTile", sf::Mouse::Right, [&](const sf::Vector2i& pos)
		{
			if(activeState == &editor)
				removeTile(pos);
		});
	}
}
