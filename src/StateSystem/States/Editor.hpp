#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../State.hpp" // Base class: swift::State
#include "../SubState.hpp"

#include "../../GUI/Window.hpp"

#include "../../Mapping/TileMap.hpp"

#include <SFML/Graphics/View.hpp>

namespace swift
{
	class Editor : public State
	{
		public:
			Editor(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic);
			virtual ~Editor();

			virtual void setup();
			virtual void handleEvent(sf::Event& event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual bool switchFrom();
			virtual Type finish();

		private:
			void addTile(const sf::Vector2i& pos);
			void removeTile(const sf::Vector2i& pos);
			
			int mouseToTile(const sf::Vector2i& pos) const;
			
			void setupSubStateFuncs();
			
			void setupPauseGUI();
			void setupEditorGUI();
			
			void setupNewMapGUI();
			void setupSaveMapGUI();
			void setupLoadMapGUI();
			
			void setupKeyBindings();
			
			sf::RenderWindow toolsWindow;
			
			sf::View editorView;
			sf::Vector2f editorViewMove;
			
			SubState* activeState;
			SubState editor;
			SubState pause;
			
			SubState newMap;
			SubState saveMap;
			SubState loadMap;
			
			cstr::Window editorCtrls;
			cstr::Window pauseMenu;
			
			cstr::Window newMapGUI;
			cstr::Window saveMapGUI;
			cstr::Window loadMapGUI;
			
			TileMap currentMap;
			std::string mapName;
			
			bool mapLoaded;
			int tileSelected;
			
			bool done;
	};
}

#endif // EDITOR_HPP
