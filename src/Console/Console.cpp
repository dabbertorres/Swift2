#include "Console.hpp"
#include <iostream>
#include <sstream>

namespace swift
{
	const int Console::FONT_SIZE = 14;
	
	Console::Console(int w, int h, const sf::Font& f, const std::string& p)
		:	background(sf::Vector2f(w, h)),
		    font(f),
		    promptStr(p),
		    activated(false)
	{
		background.setFillColor(sf::Color(0, 0, 0, 190));
		background.setOutlineThickness(5);
		background.setOutlineColor(sf::Color(60, 60, 60));
		
		prompts.emplace_front(promptStr, font, FONT_SIZE);
		prompts[0].setPosition(0, 0);
		
		command.setString(commandStr);
		command.setFont(font);
		command.setCharacterSize(FONT_SIZE);
		command.setPosition(prompts[0].getGlobalBounds().width + 2, prompts[0].getPosition().y);
	}

	Console::~Console()
	{
	}

	void Console::update(sf::Event event)
	{
		if(activated)
		{
			if(event.type == sf::Event::TextEntered)
			{
				char t = static_cast<char>(event.text.unicode);
				
				// 8 = backspace, 13 = enter/return, 27 = escape, 127 = delete
				if(!(t == 8 || t == 13 || t== 27 || t == 127))
				{
					commandStr += t;
					command.setString(commandStr);

					// wrap around
					if(command.getGlobalBounds().width + prompts[0].getGlobalBounds().width >= background.getGlobalBounds().width)
					{
						char temp = commandStr[commandStr.getSize() - 1];
						commandStr.erase(commandStr.getSize() - 1);
						commandStr += '\n';
						commandStr += temp;
						command.setString(commandStr);
					}
				}
				else if(t == 8)
				{
					if(commandStr.getSize() > 0)
						commandStr.erase(commandStr.getSize() - 1);
					command.setString(commandStr);
				}
				else if(t == 13)
				{
					if(commandStr == "")
						return;

					// get prompt + command
					lines.emplace_front(promptStr + commandStr, font, FONT_SIZE);
					lines[0].setPosition(prompts[0].getPosition());
					prompts.pop_front();	// remove to get rid of overwriting

					// output
					lines.emplace_front(handleCommand(commandStr), font, FONT_SIZE);
					lines[0].setPosition(0, command.getGlobalBounds().top + command.getGlobalBounds().height);

					// new prompt
					prompts.emplace_front(promptStr, font, FONT_SIZE);
					prompts[0].setPosition(0, lines[0].getGlobalBounds().top + lines[0].getGlobalBounds().height);

					commands.emplace_front(commandStr);
					commandStr.clear();
					command.setString(commandStr);
					command.setPosition(prompts[0].getGlobalBounds().width + 2, prompts[0].getPosition().y);

					// pop off the top if we start going out the bottom of the console
					if(prompts[0].getGlobalBounds().top + prompts[0].getGlobalBounds().height >= background.getGlobalBounds().height ||
					        lines[0].getGlobalBounds().top + lines[0].getGlobalBounds().height >= background.getGlobalBounds().height)
						lines.pop_back();

					// check for going out of the bottom, then move everything up a line while we are going out the bottom
					while(prompts[0].getGlobalBounds().top + prompts[0].getGlobalBounds().height >= background.getGlobalBounds().height ||
					        lines[0].getGlobalBounds().top + lines[0].getGlobalBounds().height >= background.getGlobalBounds().height)
					{
						// pull everything up a line
						for(auto &p : prompts)
							p.setPosition(p.getPosition().x, p.getPosition().y - (FONT_SIZE + 2));
						command.setPosition(command.getPosition().x, command.getPosition().y - (FONT_SIZE + 2));
						for(auto &l : lines)
							l.setPosition(l.getPosition().x, l.getPosition().y - (FONT_SIZE + 2));
					}
				}
				else if(t == 127)
				{
					// for the time being, we don't want it to do anything
				}
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				if(event.key.code == sf::Keyboard::Up)
				{
					if(commands.size() > 0)
					{
						commandStr = commands[0];
						command.setString(commandStr);
						commands.push_back(commands[0]);
						commands.pop_front();
					}
				}
				else if(event.key.code == sf::Keyboard::Down)
				{

				}
			}
		}
	}

	void Console::addCommand(const std::string& c, CommandFunc f)
	{
		commandList.emplace(c, f);
	}

	bool Console::isActivated() const
	{
		return activated;
	}

	void Console::activate(bool a)
	{
		activated = a;
	}

	Console& Console::operator <<(const std::string& str)
	{
		lines[0].setString(lines[0].getString() + str);

		return *this;
	}

	Console& Console::operator <<(char c)
	{
		lines[0].setString(lines[0].getString() + c);

		return *this;
	}

	std::string Console::handleCommand(const std::string& c)
	{
		std::istringstream ss(c);
		std::vector<std::string> args;

		int i = 0;
		std::string temp;
		while(ss >> temp)
		{
			args.push_back(temp);
			++i;
		}

		if(commandList.count(args[0]) != 0)
			return commandList[args[0]](args);
		else
			return "Unknown command";
	}

	void Console::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(activated)
		{
			target.draw(background, states);
			for(auto& p : prompts)
				target.draw(p, states);
			target.draw(command, states);
			for(auto& l : lines)
				target.draw(l, states);
		}
	}
}
