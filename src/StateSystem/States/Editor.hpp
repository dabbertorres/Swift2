#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../State.hpp" // Base class: swift::State
#include "../SubState.hpp"

#include "../../GUI/Window.hpp"

#include "../../Mapping/TileMap.hpp"

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
			
			unsigned mouseToTile(const sf::Vector2i& pos) const;
			
			void setupPauseGUI();
			void setupEditorGUI();
			void setupKeyBindings();
			
			sf::RenderWindow toolsWindow;
			
			SubState* activeState;
			SubState editor;
			SubState pause;
			
			cstr::Window editorCtrls;
			cstr::Window pauseMenu;
			
			TileMap currentMap;
			
			bool mapLoaded;
			int tileSelected;
	};
}

#endif // EDITOR_HPP
