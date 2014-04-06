#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <utility>
#include <functional>
#include <map>
#include <deque>

#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

namespace swift
{
	typedef std::vector<std::string> ArgVec;
	typedef std::function<std::string(ArgVec args)> CommandFunc;
	
	class Console : public sf::Drawable
	{
		public:
			Console(int w, int h, const sf::Font& f, const std::string& p = "[swift]:");
			~Console();
			
			void update(sf::Event event);

			void addCommand(const std::string& c, CommandFunc f);

			bool isActivated() const;
			void activate(bool a);
			
			Console& operator <<(const std::string& str);
			Console& operator <<(char c);

		private:
			// returns a string of output from the command
			std::string handleCommand(const std::string& c);
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::RectangleShape background;

			const sf::Font& font;

			const sf::String promptStr;
			std::deque<sf::Text> prompts;

			sf::String commandStr;
			sf::Text command;
			std::deque<sf::String> commands;

			std::deque<sf::Text> lines;

			std::map<std::string, CommandFunc> commandList;

			bool activated;
			
			static const int FONT_SIZE;
	};
}

#endif // CONSOLE_HPP
